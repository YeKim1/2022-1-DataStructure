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

	int pop_Max() {
		vector<int>::iterator p = v.begin();
		int Max = *p;

		for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
			if (*iter > Max) {
				Max = *iter;
				p = iter;
			}
		}

		v.erase(p);
		return Max;
	}

	int size() {
		return v.size();
	}

};

int main() {
	int T, N, n;

	cin >> T;

	for (int i = 0; i < T; i++) {
		PQ* pq_even = new PQ; //Â¦¼ö
		PQ* pq_odd = new PQ; //È¦¼ö
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> n;
			if (n % 2 == 0) pq_even->insert(n);
			else pq_odd->insert(n);
		}

		int even_size = pq_even->size();
		int odd_size = pq_odd->size();

		int* arr_even = new int[even_size];
		int* arr_odd = new int[odd_size];
		
		for (int j = 0; j < odd_size; j++) {
			arr_odd[j] = pq_odd->pop_Max();
			cout << arr_odd[j] << ' ';
		}

		for (int j = 0; j < even_size; j++) {
			arr_even[j] = pq_even->pop_Max();
			cout << arr_even[j] << ' ';
		}

		cout << endl;
	}
}