#include <iostream>
#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2	
using namespace std;

struct Entry {
	int key;
	string value;
	int valid;

	Entry() {
		key = 0;
		value = "";
		valid = NOITEM;
	}

	Entry(int k, string v) {
		this->key = k;
		this->value = v;
		valid = ISITEM;
	}

	void erase() {
		valid = AVAILABLE;
	}
};

class HashTable {
private:
	Entry* hash_table;
	int capacity;

	int hash_func(int k) { return (k % capacity); }

public:
	HashTable(int N) {
		capacity = N;
		hash_table = new Entry[capacity];
	}

	void put(int k, string v) {
		int index = hash_func(k);
		int probing = 1;

		while (hash_table[index].valid == ISITEM && probing <= capacity) {
			index = hash_func(index + 1);
			probing++;
		}

		cout << probing << endl;

		if (probing <= capacity) {
			hash_table[index] = Entry(k, v);
		}
	}

	void erase(int k) {
		int index = hash_func(k);
		int probing = 1;

		while (probing <= capacity) {
			if (hash_table[index].valid == ISITEM && hash_table[index].key == k) {
				cout << hash_table[index].value << endl;
				hash_table[index].erase();
				return;
			}
			index = hash_func(index + 1);
			probing++;
		}

		cout << "None" << endl;
	}

	void find(int k) {
		int index = hash_func(k);
		int probing = 1;

		while (probing <= capacity) {
			if (hash_table[index].valid == ISITEM && hash_table[index].key == k) {
				cout << hash_table[index].value << endl;
				return;
			}
			index = hash_func(index + 1);
			probing++;
		}

		cout << "None" << endl;
	}

	void vacant() {
		int v = 0;
		for (int i = 0; i < capacity; i++) {
			if (hash_table[i].valid != ISITEM) v++;
		}
		cout << v << endl;
	}
};

int main() {
	int T, N, K;
	cin >> T >> N;

	HashTable* HT = new HashTable(N);

	string s, v;

	for (int i = 0; i < T; i++) {
		cin >> s;

		if (s == "put") {
			cin >> K >> v;
			HT->put(K, v);
		}
		else if (s == "erase") {
			cin >> K;
			HT->erase(K);
		}
		else if (s == "find") {
			cin >> K;
			HT->find(K);
		}
		else if (s == "vacant") {
			HT->vacant();
		}
	}
}