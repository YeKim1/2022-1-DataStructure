#include <iostream>
using namespace std;

struct vertex {
	int vertex_id;
	int matrix_id;
	vertex* next;
	vertex* prev;
	
	vertex() {
		vertex_id = matrix_id = -1;
		next = prev = NULL;
	}

	vertex(int v_id) {
		vertex_id = v_id;
		matrix_id = -1;
		next = prev = NULL;
	}
};

struct edge {
	vertex* src;
	vertex* dst;
	edge* next;
	edge* prev;

	edge() {
		src = dst = NULL;
		next = prev = NULL;
	}

	edge(vertex* s, vertex* d) {
		src = s;
		dst = d;
		next = prev = NULL;
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

	vertex* find_vertex(int v_I) {
		for (vertex* cur = header->next; cur != trailer; cur= cur->next) {
			if (cur->vertex_id == v_I) return cur;
		}
		return NULL;
	}

	void insert_back(vertex* new_V) {
		new_V->next = trailer;
		new_V->prev = trailer->prev;
		new_V->matrix_id = new_V->prev->matrix_id + 1;
		trailer->prev->next = new_V;
		trailer->prev = new_V;
	}

	vertex* find_matrix_id(int m_i) {
		for (vertex* cur = header->next; cur != trailer; cur= cur->next) {
			if (cur->matrix_id == m_i) return cur;
		}
		return NULL;
	}
};

class edgeList {
private:
	edge* header;
	edge* trailer;

public:
	edgeList() {
		header = new edge();
		trailer = new edge();
		header->next = trailer;
		trailer->prev = header;
	}

	void insert_back(edge* new_e) {
		new_e->next = trailer;
		new_e->prev = trailer->prev;
		trailer->prev->next = new_e;
		trailer->prev = new_e;
	}

	void erase(edge* del_e) {
		del_e->prev->next = del_e->next;
		del_e->next->prev = del_e->prev;
	}

};

class Graph {
private:
	vertexList vL;
	edgeList eL;
	edge*** eM;
	int v_size;

public:
	Graph() {
		v_size = NULL;
		eM = NULL;
	}

	void insert_vertex(int v_i) {
		if (vL.find_vertex(v_i) != NULL) return;

		vertex* new_v = new vertex(v_i);
		
		edge*** new_m = new edge * *[v_size + 1];
		for (int i = 0; i < v_size + 1; i++) new_m[i] = new edge * [v_size + 1];

		for (int i = 0; i < v_size; i++) {
			for (int j = 0; j < v_size; j++) {
				new_m[i][j] = eM[i][j];
			}
		}

		for (int i = 0; i < v_size + 1; i++) {
			new_m[i][v_size] = new_m[v_size][i] = NULL;
		}

		eM = new_m;
		vL.insert_back(new_v);
		v_size++;
	}

	void insert_edge(int src_v_i, int dst_v_i) {
		vertex* src = vL.find_vertex(src_v_i);
		vertex* dst = vL.find_vertex(dst_v_i);

		int src_m = src->matrix_id;
		int dst_m = dst->matrix_id;

		if (eM[src_m][dst_m] != NULL || eM[dst_m][src_m] != NULL) {
			cout << "Exist" << endl;
			return;
		}

		edge* new_e = new edge(src, dst);

		eM[src_m][dst_m] = eM[dst_m][src_m] = new_e;

		eL.insert_back(new_e);

	}

	void erase_edge(int src_v_i, int dst_v_i) {
		vertex* src = vL.find_vertex(src_v_i);
		vertex* dst = vL.find_vertex(dst_v_i);

		int src_m = src->matrix_id;
		int dst_m = dst->matrix_id;

		if (eM[src_m][dst_m] == NULL || eM[dst_m][src_m] == NULL) {
			cout << "None" << endl;
			return;
		}

		eL.erase(eM[src_m][dst_m]);

		eM[src_m][dst_m] = eM[dst_m][src_m] = NULL;

	}

	void MaxAdjacentNode(int v_i) {
		vertex* v = vL.find_vertex(v_i);

		int max = 0;

		for (int i = 0; i < v_size; i++) {
			if (eM[i][v->matrix_id] != NULL) {
				if (max < vL.find_matrix_id(i)->vertex_id) max = vL.find_matrix_id(i)->vertex_id;
			}
		}

		if (max == 0) {
			cout << "None" << endl;
			return;
		}
		else cout << max << endl;
	}
};

int main() {
	int T, N, S, D;
	string s;
	cin >> T >> N;

	Graph* g = new Graph();
	
	for (int i = 0; i < N; i++) {
		cin >> S;
		g->insert_vertex(S);
	}

	for (int i = 0; i < T; i++) {
		cin >> s;

		if (s == "insertEdge") {
			cin >> S >> D;
			g->insert_edge(S, D);
		}
		else if (s == "eraseEdge") {
			cin >> S >> D;
			g->erase_edge(S, D);
		}
		else if (s == "MaxAdjacentNode") {
			cin >> S;
			g->MaxAdjacentNode(S);
		}
	}

}