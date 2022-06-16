#include <iostream>
#include <math.h>
#define NOITEM 0
#define LOGOUT 1
#define LOGIN 2
using namespace std;

// ¿À´ä..


struct Entry {
	string id;
	string password;
	int valid;

	Entry() {
		id = "";
		password = "";
		valid = NOITEM;
	}

	Entry(string id, string password) {
		this->id = id;
		this->password = password;
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
private:
	Entry* hash_table;
	int capacity;

	int hash_func(string id) {
		int sum = 0;
		for (int i = 0; i < id.length(); i++) {
			sum += (id[i] - 'a') * pow(26, i);
		}
		return sum % capacity;
	}

public:
	HashTable() {
		capacity = 250000;
		hash_table = new Entry[capacity];
	}

	void signUp(string id, string password) {
		int index = hash_func(id);

		if (hash_table[index].valid == NOITEM) {
			cout << "Submit" << endl;
			hash_table[index] = Entry(id, password);
		}
		else cout << "Invalid" << endl;
	}

	void logIn(string id, string password) {
		int index = hash_func(id);

		if (hash_table[index].valid == NOITEM || hash_table[index].password != password) {
			cout << "Invalid" << endl;
		}
		else if (hash_table[index].valid == LOGIN) {
			cout << "Quit" << endl;
		}
		else if (hash_table[index].valid == LOGOUT) {
			hash_table[index].Login();
			cout << "Submit" << endl;
		}
	}

	void logOut(string id) {
		int index = hash_func(id);
		hash_table[index].Logout();
		cout << "Submit" << endl;
	}
	
};

int main() {
	int T;
	cin >> T;
	HashTable* HT = new HashTable();
	string s, id, p;
	for (int i = 0; i < T; i++) {
		cin >> s;
		if (s == "signup") {
			cin >> id >> p;
			HT->signUp(id, p);
		}
		else if (s == "login") {
			cin >> id >> p;
			HT->logIn(id, p);
		}
		else if (s == "logout") {
			cin >> id;
			HT->logOut(id);
		}
	}

}