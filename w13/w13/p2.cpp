#include <iostream>
#include <vector>
using namespace std;

//角菩 

struct vertex {
	int id;
	vertex* prev;
	vertex* next;

	vertex() {
		id = -1;
		prev = next = NULL;
	}

	vertex(int i) {
		id = i;
		prev = next = NULL;
	}
};

struct edge {
	int valid;
	vertex* src;
	vertex* dst;
	edge* next;
	edge* prev;

	edge() {
		valid = 1;
		src = dst = NULL;
	}

	edge(vertex* src, vertex* dst, int v) {
		this->src = src;
		this->dst = dst;
		valid = v;
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

	void insert_back() {
		vertex* new_v = new vertex();
		new_v->next = trailer;
		new_v->prev = trailer->prev;
		new_v->id = trailer->prev->id + 1;
		trailer->prev->next = new_v;
		trailer->prev = new_v;
	}

	vertex* find(int i) {
		for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
			if (cur->id == i) return cur;
		}
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
};

class Graph {
private:
	vertexList vL;
	edgeList eL;
	edge*** eM;
	int size;

public:
	Graph() {
		eM = NULL;
		size = 0;
	}

	void insert_vertex() {
		vL.insert_back();

		edge*** new_m = new edge * *[size + 1];
		for (int i = 0; i < size + 1; i++) {
			new_m[i] = new edge * [size + 1];
		}
		
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				new_m[i][j] = eM[i][j];
			}
		}

		for (int i = 0; i < size + 1; i++) {
			new_m[i][size] = new_m[size][i] = NULL;
		}

		eM = new_m;

		size++;
	}

	void insert_edge(int src_id, int dst_id, int f) {
		vertex* src = vL.find(src_id);
		vertex* dst = vL.find(dst_id);

		edge* new_e = new edge(src, dst, f);

		eM[src_id][dst_id] = eM[dst_id][src_id] = new_e;

	}

	void r(int K, int F) {
		vertex* me = vL.find(K - 1);
		vector<int> v;

		if (F == 0) { // 模备狼 模备
			for (int i = 0; i < size; i++) {
				if (eM[K-1][i]->valid == 1) {
					for (int j = 0; j < size; j++) {
						if (eM[i][j]->valid == 1) {
							v.push_back(j + 1);
						}
					}
				}
			}
			
			if (v.empty()) cout << "0" << endl;
			else {
				for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
					cout << *iter << ' ';
				}
				cout << endl;
			}
		}
		else if (F == 1) { // 模备狼 悼丰
			for (int i = 0; i < size; i++) {
				if (eM[K - 1][i]->valid == 1) {
					for (int j = 0; j < size; j++) {
						if (eM[i][j]->valid == 2) {
							v.push_back(j + 1);
						}
					}
				}
			}

			if (v.empty()) cout << "0" << endl;
			else {
				for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
					cout << *iter << ' ';
				}
				cout << endl;
			}
		}
	}
};

int main() {
	int N, M, K, F;

	Graph* G = new Graph();
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		G->insert_vertex();
	}

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cin >> F;
			G->insert_edge(i, j, F);
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> K >> F;
		G->r(K, F);
	}
}