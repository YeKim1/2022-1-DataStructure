#include <iostream>
#include <vector>
using namespace std;

class PQ {
private:
	vector<int> v;
public:
	void insert(int i) {
		v.push_back(i);
	}

	int pop_Min() {
		vector<int>::iterator p = v.begin();
		int Min = *p;

		for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
			if (*iter < Min) {
				Min = *iter;
				p = iter;
			}
		}

		v.erase(p);
		return Min;
	}


};

int main() {
	int T, N, n;

	cin >> T;

	for (int i = 0; i < T; i++) {
		PQ* pq = new PQ;
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> n;
			pq->insert(n);
		}

		int* arr = new int[N];

		for (int j = 0; j < N; j++) {
			arr[j] = pq->pop_Min();
			cout << arr[j] << ' ';
		}

		cout << endl;
	}
}