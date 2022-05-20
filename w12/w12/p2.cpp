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
		valid = LOGOUT;
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
		if (isFind(k) == false) {
			cout << "Submit" << endl;
			put(k, v);
		}
		else {
			cout << "Invalid" << endl;
		}
	}

	void put(string key, string value) {
		hash_table[hash_func(key)] = Entry(key, value);
	}

	void Login(string key, string value) {
		if (isFind(key) == false || hash_table[hash_func(key)].value != value) {
			cout << "Invalid" << endl;
			return;
		}

		else if (hash_table[hash_func(key)].value==value && hash_table[hash_func(key)].valid == LOGIN) {
			cout << "Quit" << endl;
		}

		else if (hash_table[hash_func(key)].value == value && hash_table[hash_func(key)].valid == LOGOUT) {
			cout << "Submit" << endl;
			hash_table[hash_func(key)].Login();
		}
	}

	void Logout(string key) {
		hash_table[hash_func(key)].Logout();
		cout << "Submit" << endl;
	}


	bool isFind(string k) {
		if (hash_table[hash_func(k)].valid == NOITEM) return false;
		else return true;
	}

};

int main() {
	int T;

	cin >> T;

	HashTable* HT = new HashTable(200000);

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