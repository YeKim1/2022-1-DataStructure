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

	Entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
	}

	void erase() {
		valid = AVAILABLE;
	}
};

class HashTable {
	Entry* hash_table;
	int capacity;

	int hash_func(int key) {
		return key % capacity;
	}

public:
	HashTable(int N) {
		capacity = N;
		hash_table = new Entry[capacity];
		return;
	}

	void put(int key, string value) {
		int index = hash_func(key);
		int probing = 1;

		while (hash_table[index].valid == ISITEM && probing <= capacity) {
			index = hash_func(index + 1);
			probing++;
		}

		if (probing > capacity) return;
		hash_table[index] = Entry(key, value);
		return;
	}

	void erase(int key) {
		int index = hash_func(key);
		int probing = 1;

		while (hash_table[index].valid != NOITEM && probing <= capacity) {
			if (hash_table[index].valid == ISITEM && hash_table[index].key == key) {
				hash_table[index].erase();
			}
			index = hash_func(index + 1);
			probing++;
		}
		return;
	}

	string find(int key) {
		int index = hash_func(key);
		int probing = 1;

		while (hash_table[index].valid != NOITEM && probing <= capacity) {
			if (hash_table[index].valid == ISITEM && hash_table[index].key == key) {
				return hash_table[index].value;
			}
			index = hash_func(index + 1);
			probing++;
		}
		return "";
	}
};