#include <iostream>
#include <vector>
using namespace std;

struct vertex;
struct edge;
struct edgeNode;
class vertexList {
public:
	vertex* header;
	vertex* trailer;
	vertexList();
	void insertVertex(vertex*);
	vertex* findVertex(int v_i);
};
class edgeList {
public:
	edgeNode* header;
	edgeNode* trailer;
	edgeList();
	void insertEdge(edge*);
};

struct vertex {
	bool visit;
	int vertexId;
	int degree;
	edgeList IncidentEdgeNode;
	vertex* next;
	vertex* prev;

	vertex() {
		vertexId = -1;
		degree = 0;
		next = prev = NULL;
		visit = false;
	}

	vertex(int vi) {
		this->vertexId = vi;
		degree = 0;
		next = prev = NULL;
		visit = false;
	}
};

struct edge {
	vertex* src;
	vertex* dst;
	edgeNode* srcIncidentNode;
	edgeNode* dstIncidentNode;
	edgeNode* totalIncidentNode;

	edge() {
		src = dst = NULL;
	}
	
	edge(vertex* s, vertex* d) {
		src = s;
		dst = d;
	}
};

struct edgeNode {
	edge* edgeInfo;
	edgeNode* next;
	edgeNode* prev;
	
	edgeNode() {
		edgeInfo = NULL;
		next = prev = NULL;
	}

	edgeNode(edge* e) {
		this->edgeInfo = e;
		next = prev = NULL;
	}
};

vertexList::vertexList() {
	header = new vertex();
	trailer = new vertex();
	header->next = trailer;
	trailer->prev = header;
}

vertex* vertexList::findVertex(int v_i) {
	for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
		if (cur->vertexId == v_i) return cur;
	}
	return NULL;
}

void vertexList::insertVertex(vertex* v) {
	v->next = trailer;
	v->prev = trailer->prev;
	trailer->prev->next = v;
	trailer->prev = v;
}

edgeList::edgeList() {
	header = new edgeNode();
	trailer = new edgeNode();
	header->next = trailer;
	trailer->prev = header;
}

void edgeList::insertEdge(edge* e) {
	edgeNode* eN = new edgeNode(e);
	eN->prev = trailer->prev;
	eN->next = trailer;
	trailer->prev->next = eN;
	trailer->prev = eN;
}

class graph {
public:
	vertexList vL;
	edgeList eL;

	void insertVertex(int v_i) {
		vertex* v = new vertex(v_i);
		vL.insertVertex(v);
	}

	void insertEdge(int src_vi, int dst_vi) {
		vertex* src = vL.findVertex(src_vi);
		vertex* dst = vL.findVertex(dst_vi);

		if (src == NULL || dst == NULL) {
			cout << "¾ø¾î" << endl;
			return;
		}

		edge* e = new edge(src, dst);
		eL.insertEdge(e);
		src->IncidentEdgeNode.insertEdge(e);
		dst->IncidentEdgeNode.insertEdge(e);
		e->dstIncidentNode = dst->IncidentEdgeNode.trailer->prev;
		e->srcIncidentNode = src->IncidentEdgeNode.trailer->prev;
		e->totalIncidentNode = eL.trailer->prev;

		src->degree++;
		dst->degree++;
	}

	void DFS(vertex* cur, vector<int>& v) {
		cur->visit = true;
		v.push_back(cur->vertexId);

		for (edgeNode* e = cur->IncidentEdgeNode.header->next; e != cur->IncidentEdgeNode.trailer; e = e->next) {
			if (cur == e->edgeInfo->src) {
				if (e->edgeInfo->dst->visit != true) DFS(e->edgeInfo->dst, v);
			}
			else {
				if (e->edgeInfo->src->visit != true) DFS(e->edgeInfo->src, v);
			}
		}

	}
};

int main() {
	int T, N, M, a, b;
	cin >> T;

	for (int i = 0; i < T; i++) {
		graph* g = new graph;
		cin >> N >> M;

		for (int j = 1; j <= N; j++) {
			g->insertVertex(j);
		}

		for (int j = 0; j < M; j++) {
			cin >> a >> b;
			g->insertEdge(a, b);
		}
		vector<int> v;
		g->DFS(g->vL.findVertex(1), v);

		for (int j = 0;j<v.size();j++) {
			if (j % 2 == 0) cout << v[j] << ' ';
		}
		cout << endl;
	}
}