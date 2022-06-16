#include <iostream>
using namespace std;

struct vertex {
	int vertex_id;
	int degree;
	vertex* next;
	vertex* prev;
	edgeList incidentEdge;
	bool visit;

	vertex() {
		vertex_id = -1;
		degree = 0;
		next = prev = NULL;
		visit = false;
	}

	vertex(int v) {
		vertex_id = v;
		degree = 0;
		next = prev = NULL;
		visit = false;
	}
};

struct edge {
	vertex* srcVertex;
	vertex* dstVertex;
	edgeNode* srcIncidentEdgeNode;
	edgeNode* dstIncidentEdgeNode;
	edgeNode* totalEdgeNode;

	edge() {
		srcVertex = dstVertex = NULL;
	}
	edge(vertex* src, vertex* dst) {
		srcVertex = src;
		dstVertex = dst;
	}
};

struct edgeNode {
	edge* edgeInfo;
	edgeNode* prev;
	edgeNode* next;
	edgeNode() {
		edgeInfo = NULL;
		prev = next = NULL;
	}
	edgeNode(edge* edgeInfo) {
		this->edgeInfo = edgeInfo;
		prev = next = NULL;
	}
};

class vertexList {
private:
	vertex* header;
	vertex* trailer;

public:
	vertexList() {
		header = new vertex();
		trailer = new vertex();
		header->next = trailer;
		trailer->prev = header;
	}

	void insertVertex(vertex* newV) {
		newV->next = trailer;
		newV->prev = trailer->prev;
		trailer->prev->next = newV;
		trailer->prev = newV;
	}

	void eraseVertex(vertex* delV) {
		delV->prev->next = delV->next;
		delV->next->prev = delV->prev;
	}

	vertex* findVertex(int i) {
		for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
			if (cur->vertex_id == i) return cur;
		}

		return NULL;
	}

};

class edgeList {
public:
	edgeNode* header;
	edgeNode* trailer;
	edgeList() {
		header = new edgeNode();
		trailer = new edgeNode();
		header->next = trailer;
		trailer->prev = header;
	}

	void insertEdge(edge* newE) {
		edgeNode* newEdge = new edgeNode(newE);
		newEdge->prev = trailer->prev;
		newEdge->next = trailer;
		trailer->prev->next = newEdge;
		trailer->prev = newEdge;
	}

	void eraseEdge(edgeNode* delE) {
		delE->prev->next = delE->next;
		delE->next->prev = delE->prev;
	}
};

class graph {
private:
	vertexList vL;
	edgeList eL;

public:
	edge* findEdge(vertex* src, vertex* dst) {
		if (src->degree < dst->degree) {
			for (edgeNode* cur = src->incidentEdge.header->next; cur != src->incidentEdge.trailer; cur = cur->next) {
				if (cur->edgeInfo->dstVertex == dst) return cur->edgeInfo;
			}
		}
		else {
			for (edgeNode* cur = dst->incidentEdge.header->next; cur != dst->incidentEdge.trailer; cur = cur->next) {
				if (cur->edgeInfo->dstVertex == src) return cur->edgeInfo;
			}
		}
		return NULL;
	}

	void insertVertex(int vi) {
		if (vL.findVertex(vi) != NULL) return;
		vertex* newVertex = new vertex(vi);
		vL.insertVertex(newVertex);
	}

	void eraseVertex(int vi) {
		vertex* delV = vL.findVertex(vi);
		if (delV == NULL) return;

		for (edgeNode* cur = delV->incidentEdge.header->next; cur != delV->incidentEdge.trailer; cur = cur->next) {
			eL.eraseEdge(cur->edgeInfo->totalEdgeNode);
			if (cur == cur->edgeInfo->srcIncidentEdgeNode) {
				cur->edgeInfo->dstVertex->incidentEdge.eraseEdge(cur->edgeInfo->dstIncidentEdgeNode);
			}
			else {
				cur->edgeInfo->srcVertex->incidentEdge.eraseEdge(cur->edgeInfo->srcIncidentEdgeNode);
			}
		}

		vL.eraseVertex(delV);
	}

	void insertEdge(int src_vi, int dst_vi) {
		vertex* src = vL.findVertex(src_vi);
		vertex* dst = vL.findVertex(dst_vi);
		if (src == NULL || dst == NULL) return;
		if (findEdge(src, dst) != NULL) return;

		edge* newE = new edge(src, dst);

		src->incidentEdge.insertEdge(newE);
		dst->incidentEdge.insertEdge(newE);
		eL.insertEdge(newE);
		newE->srcIncidentEdgeNode = src->incidentEdge.trailer->prev;
		newE->dstIncidentEdgeNode = dst->incidentEdge.trailer->prev;
		newE->totalEdgeNode = eL.trailer->prev;
		src->degree++;
		dst->degree++;
	}
};