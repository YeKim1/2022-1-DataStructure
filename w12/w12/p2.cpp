#include <iostream>
#include <math.h>
#define NOITEM 0
#define SIGNUP 1
#define LOGIN 2
#define LOGOUT 3
using namespace std;

struct Entry {
	string key;
	string value;
	int valid;

	Entry() {
		key = "";
		value = "";
		valid = NOITEM;
	}

	Entry(string key, string value) {
		this->key = key;
		this->value = value;
		valid = SIGNUP;
	}

	void Login() {
		valid = LOGIN;
	}

	void Logout() {
		valid = LOGOUT;
	}
};

class HashTable {
	Entry* hash_table;
	int capacity;

	int hash_func(string S) {
		int sum = 0;
		for (int i = 0; i < S.length(); i++) {
			sum += (S[i] - 'a') * pow(26, i);
		}
		return sum % capacity;

	}

public:
	HashTable(int N) {
		capacity = N;
		hash_table = new Entry[capacity];
		return;
	}

	void signup(string k, string v) {
		if (find(k) != "None") {
			cout << "Submit" << endl;
			put(k, v);
		}
		else {
			cout << "Invalid" << endl;
		}
	}

	void put(string key, string value) {
		int index = hash_func(key);
		int probing = 1;

		hash_table[index] = Entry(key, value);
	}

	void Login(string key, string value) {
		if (find(key) == "None" || find(key) != value || hash_table[hash_func(key)].valid == NOITEM) {
			cout << "Invalid" << endl;
			return;
		}

		else if (hash_table[hash_func(key)].valid == LOGIN) {
			cout << "Quit" << endl;
		}

		else {
			cout << "Submit" << endl;
			hash_table[hash_func(key)].valid = LOGIN;
		}
	}

	void Logout(string key) {
		hash_table[hash_func(key)].valid = LOGOUT;
	}


	string find(string key) {
		int index = hash_func(key);
		int probing = 1;

		while (hash_table[index].valid != NOITEM && probing <= capacity) {
			if (hash_table[index].key == key) {
				return hash_table[index].value;
			}
			index += 1;
			probing++;
		}
		return "None";
	}

};

int main() {
	int T;

	cin >> T;

	HashTable* HT = new HashTable(400000);

	string str, K, V;

	for (int i = 0; i < T; i++) {
		cin >> str;

		if (str == "signup") {
			cin >> K >> V;
			HT->signup(K, V);
		}
		else if (str == "login") {
			cin >> K >> V;
			HT->Login(K, V);
		}
		else if (str == "logout") {
			cin >> K;
			HT->Logout(K);
		}
	}
}