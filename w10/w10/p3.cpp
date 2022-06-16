#include <iostream>
#include <vector>
using namespace std;

enum Direction { MIN = 1, MAX = -1 };

class Heap {
private:
	vector<int> v;
	int heap_size;
	int root_idx;
	int direction;

public:
	Heap(int d) {
		v.push_back(-1);
		heap_size = 0;
		root_idx = 1;
		direction = d;
	}

	bool isEmpty() { return heap_size == 0; }
	int size() { return heap_size; }

	void swap(int idx1, int idx2) {
		v[0] = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = v[0];
	}

	void upHeap(int idx) {
		if (idx == root_idx) return;

		int parent = idx / 2;

		if (v[idx] * direction < v[parent] * direction) {
			swap(idx, parent);
			upHeap(parent);
		}
		else return;

	}

	void downHeap(int idx) {
		int left = idx * 2;
		int right = idx * 2 + 1;

		if (right <= heap_size) {
			if (v[left] * direction <= v[right] * direction) {
				if (v[left] * direction < v[idx] * direction) {
					swap(left, idx);
					downHeap(left);
				}
				else return;
			}
			else {
				if (v[right] * direction < v[idx] * direction) {
					swap(right, idx);
					downHeap(right);
				}
				else return;
			}
		}
		else if (left <= heap_size) {
			if (v[left] * direction < v[idx] * direction) {
				swap(left, idx);
				downHeap(left);
			}
			else return;
		}
		else return;
	}

	void insert(int i) {
		v.push_back(i);
		heap_size++;
		upHeap(heap_size);
	}

	int pop() {
		if (isEmpty()) return -1;

		int top = v[root_idx];
		v[root_idx] = v[heap_size];
		v.pop_back();
		heap_size--;

		downHeap(root_idx);

		return top;
	}

	int top() {
		if (isEmpty()) return -1;
		return v[root_idx];
	}

	void print() {
		if (isEmpty()) {
			cout << -1 << endl;
			return;
		}
		for (vector<int>::iterator iter = ++v.begin(); iter != v.end(); iter++) {
			cout << *iter << ' ';
		}
		cout << endl;
	}
};

int main() {
	int T, n;

	cin >> T;

	Heap* H = new Heap(MAX);

	string s;
	for (int i = 0; i < T; i++) {
		cin >> s;
		if (s == "insert") {
			cin >> n;
			H->insert(n);
		}
		else if (s == "size") {
			cout << H->size() << endl;
		}
		else if (s == "isEmpty") {
			cout << H->isEmpty() << endl;
		}
		else if (s == "pop") {
			cout << H->pop() << endl;
		}
		else if (s == "top") {
			cout << H->top() << endl;
		}
		else if (s == "print") {
			H->print();
		}
	}
}
