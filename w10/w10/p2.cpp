#include <iostream>
#include <vector>
using namespace std;

enum Dictionary { MIN = 1, MAX = -1 };

class Heap {
private:
	vector<int> v;
	int heap_size;
	int root_idx;
	int dictionary;
	int P;
public:
	Heap(int d, int p) {
		v.push_back(-1);
		heap_size = 0;
		root_idx = 1;
		dictionary = d;
		P = p;
	}

	void swap(int idx1, int idx2) {
		v[0] = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = v[0];
	}

	void upHeap(int idx) {
		if (idx == root_idx) return;

		int parent = idx / 2;

		if (v[idx] * dictionary < v[parent] * dictionary) {
			swap(idx, parent);
			upHeap(parent);
		}
		else return;
	}

	void downHeap(int idx) {
		int left = idx * 2;
		int right = idx * 2 + 1;

		if (right <= heap_size) {
			if (v[left] * dictionary <= v[right] * dictionary) {
				if (v[left] * dictionary < v[idx] * dictionary) {
					swap(left, idx);
					downHeap(left);
				}
				else return;
			}
			else {
				if (v[right] * dictionary < v[idx] * dictionary) {
					swap(right, idx);
					downHeap(right);
				}
				else return;
			}
		}
		else if (left <= heap_size) {
			if (v[left] * dictionary < v[idx] * dictionary) {
				swap(left, idx);
				downHeap(left);
			}
			else return;
		}
		else return;
	}

	void insert(int e) {
		v.push_back(e);
		heap_size++;
		upHeap(heap_size);
	}

	int pop() {
		int top = v[root_idx];
		v[root_idx] = v[heap_size];
		heap_size--;
		v.pop_back();
		downHeap(root_idx);
		return top;
	}

	bool isP() { // true면 모두 P 이하
		for (vector<int>::iterator iter = ++v.begin(); iter != v.end(); iter++) {
			if (*iter > P) return false;
		}
		return true;
	}

	void Step() {
		int n1 = pop();
		pop();
		int n2 = pop();
		int new_P = (n1 + n2) / 2;
		insert(new_P);
	}

	int size() { return heap_size; }

	void print() {
		for (vector<int>::iterator iter = ++v.begin(); iter != v.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}
};

int main() {
	int T, N, K, P;

	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> N >> P;
		Heap* H = new Heap(MAX, P);
		
		for (int j = 0; j < N; j++) {
			cin >> K;
			H->insert(K);
		}

		int count = 0;
		while (!H->isP()) {
			if (H->size() <= 2) break;
			H->Step();
			count++;
		}

		if (H->isP()) {
			cout << count << endl;
			H->print();
		}
		else cout << "False" << endl;

	}
}