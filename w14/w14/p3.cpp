#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct vertex;
struct edge;
struct edgeNode;
class vertexList {
public:
	vertex* header;
	vertex* trailer;
	vertexList();
	vertex* findVertex(int);
	void insertVertex(vertex*);
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
	vertex* next;
	vertex* prev;
	edgeList IncidentNode;

	vertex() {
		visit = false;
		vertexId = -1;
		next = prev = NULL;
	}

	vertex(int v_i) {
		visit = false;
		vertexId = v_i;
		next = prev = NULL;
	}
};

struct edge {
	vertex* src;
	vertex* dst;
	edgeNode* srcIncidentNode;
	edgeNode* dstIncidentNode;
	edgeNode* totalNode;
	
	edge() {
		src = dst = NULL;
	}

	edge(vertex* s, vertex* d) {
		src = s; dst = d;
	}
};

struct edgeNode {
	edge* edgeInfo;
	edgeNode* next;
	edgeNode* prev;
	
	edgeNode() {
		next = prev = NULL;
	}

	edgeNode(edge* e) {
		edgeInfo = e;
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
	eN->next = trailer;
	eN->prev = trailer->prev;
	trailer->prev->next = eN;
	trailer->prev = eN;
}

class graph {
public:
	vertexList vL;
	edgeList eL;

	void insertVertex(int id) {
		vertex* v = new vertex(id);
		vL.insertVertex(v);
	}

	void insertEdge(int src_id, int dst_id) {
		vertex* src = vL.findVertex(src_id);
		vertex* dst = vL.findVertex(dst_id);

		edge* e = new edge(src, dst);
		eL.insertEdge(e);
		src->IncidentNode.insertEdge(e);
		dst->IncidentNode.insertEdge(e);
		e->srcIncidentNode = src->IncidentNode.trailer->prev;
		e->dstIncidentNode = dst->IncidentNode.trailer->prev;
		e->totalNode = eL.trailer->prev;
	}

	void BFS(vertex* cur, vector<int> &vec) {
		queue<vertex*> que;
		que.push(cur);
		cur->visit = true;
		vec.push_back(cur->vertexId);
		while (!que.empty()) {
			vertex* v = que.front();
			que.pop();
			for (edgeNode* e = v->IncidentNode.header->next; e != v->IncidentNode.trailer; e = e->next) {
				if (v == e->edgeInfo->src) {
					if (e->edgeInfo->dst->visit != true) {
						que.push(e->edgeInfo->dst);
						e->edgeInfo->dst->visit = true;
						vec.push_back(e->edgeInfo->dst->vertexId);
					}
				}
				else {
					if (e->edgeInfo->src->visit != true) {
						que.push(e->edgeInfo->src);
						e->edgeInfo->src->visit = true;
						vec.push_back(e->edgeInfo->src->vertexId);
					}
				}
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

		g->BFS(g->vL.findVertex(1), v);

		for (int j = 0; j < v.size(); j++) {
			if (j % 2 == 0) cout << v[j] << ' ';
		}

		cout << endl;
	}
}