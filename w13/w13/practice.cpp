#include <iostream>
using namespace std;

struct vertex {
	int vertex_id;
	int matrix_id;
	vertex* prev;
	vertex* next;

	vertex() {
		vertex_id = matrix_id = -1;
		prev = next = NULL;
	}

	vertex(int vertex_id) {
		this->vertex_id = vertex_id;
		matrix_id = -1;
		prev = next = NULL;
	}
};

struct edge {
	vertex* src;
	vertex* dst;
	edge* prev;
	edge* next;

	edge() {
		src = dst = NULL;
		prev = next = NULL;
	}

	edge(vertex* src, vertex* dst) {
		this->src = src;
		this->dst = dst;
		prev = next = NULL;
	}
};

class VertexList {
private:
	vertex* header;
	vertex* trailer;

public:
	VertexList() {
		header = new vertex();
		trailer = new vertex();
		header->next = trailer;
		trailer->prev = header;
	}

	void insert_back(vertex* new_vertex) {
		new_vertex->prev = trailer->prev;
		new_vertex->next = trailer;
		new_vertex->matrix_id = new_vertex->prev->matrix_id + 1;
		trailer->prev->next = new_vertex;
		trailer->prev = new_vertex;
	}

	void remove(vertex* del_vertex) {
		for (vertex* cur = del_vertex->next; cur != trailer; cur = cur->next) {
			cur->matrix_id--;
		}

		del_vertex->next->prev = del_vertex->prev;
		del_vertex->prev->next = del_vertex->next;
		delete del_vertex;

	}

	vertex* find_vertex(int vertex_id) {
		for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
			if (cur->vertex_id = vertex_id) return cur;
		}
	}

};

class EdgeList {
private:
	edge* header;
	edge* trailer;
	
public:
	EdgeList() {
		header = new edge();
		trailer = new edge();
		header->next = trailer;
		trailer->prev = header;
	}

	void insert_back(edge* new_edge) {
		new_edge->prev = trailer->prev;
		new_edge->next = trailer;
		trailer->prev->next = new_edge;
		trailer->prev = new_edge;
	}

	void remove(edge* del_edge) {
		del_edge->prev->next = del_edge->next;
		del_edge->next->prev = del_edge->prev;
		delete del_edge;
	}
};

class graph {
	edge*** edge_matrix;
	VertexList vertex_list;
	EdgeList edge_list;
	int vertex_size;

public:
	graph() {
		vertex_size = 0;
		edge_matrix = NULL;
	}

	void insert_vertex(int vertex_id) {
		if (vertex_list.find_vertex(vertex_id) != NULL) return;

		vertex* new_vertex = new vertex(vertex_id);

		edge*** new_matrix = new edge * *[vertex_size + 1];
		for (int i = 0; i < vertex_size + 1; i++) new_matrix[i] = new edge * [vertex_size + 1];

		for (int i = 0; i < vertex_size; i++) {
			for (int j = 0; j < vertex_size; j++) {
				new_matrix[i][j] = edge_matrix[i][j];
			}
		}

		for (int i = 0; i < vertex_size + 1; i++) {
			new_matrix[i][vertex_size] = new_matrix[vertex_size][i] = NULL;
		}

		edge_matrix = new_matrix;
		vertex_list.insert_back(new_vertex);
		vertex_size++;

	}

	void erase_vertex(int vertex_id) {
		vertex* del_vertex = vertex_list.find_vertex(vertex_id);
		if (del_vertex == NULL) return;

		int del_idx = del_vertex->matrix_id;

		edge*** new_matrix = new edge * *[vertex_size - 1];
		for (int i = 0; i < vertex_size - 1; i++) new_matrix[i] = new edge * [vertex_size - 1];

		for (int i = 0; i < vertex_size - 1; i++) {
			for (int j = 0; j < vertex_size - 1; j++) {
				if (i < del_idx && j < del_idx) new_matrix[i][j] = edge_matrix[i][j];
				else if (i < del_idx) new_matrix[i][j] = edge_matrix[i][j + 1];
				else if (j < del_idx) new_matrix[i][j] = edge_matrix[i + 1][j];
				else new_matrix[i][j] = edge_matrix[i + 1][j + 1];
			}
		}

		for (int i = 0; i < vertex_size; i++) {
			if (edge_matrix[del_idx][i] != NULL) edge_list.remove(edge_matrix[del_idx][i]);
		}

		edge_matrix = new_matrix;
		vertex_list.remove(del_vertex);
		vertex_size--;
	}

	void insert_edge(int src_vertex_id, int dst_vertex_id) {
		vertex* src_vertex = vertex_list.find_vertex(src_vertex_id);
		vertex* dst_vertex = vertex_list.find_vertex(dst_vertex_id);
		if (src_vertex == NULL || dst_vertex == NULL) return;

		int src_id = src_vertex->matrix_id;
		int dst_id = dst_vertex->matrix_id;

		if (edge_matrix[src_id][dst_id] != NULL || edge_matrix[dst_id][src_id] != NULL) return;

		edge* new_edge = new edge(src_vertex, dst_vertex);
		edge_list.insert_back(new_edge);
		edge_matrix[src_id][dst_id] = edge_matrix[dst_id][src_id] = new_edge;
	}

	void erase_edge(int src_vertex_id, int dst_vertex_id) {
		vertex* src_vertex = vertex_list.find_vertex(src_vertex_id);
		vertex* dst_vertex = vertex_list.find_vertex(dst_vertex_id);
		if (src_vertex == NULL || dst_vertex == NULL) return;

		int src_id = src_vertex->matrix_id;
		int dst_id = dst_vertex->matrix_id;

		if (edge_matrix[src_id][dst_id] == NULL || edge_matrix[dst_id][src_id] == NULL) return;

		edge_list.remove(edge_matrix[src_id][dst_id]);
		edge_matrix[src_id][dst_id] = edge_matrix[dst_id][src_id] = NULL;
	}
};