#include <iostream>
#include <math.h>
#define NOITEM 0
#define LOGOUT 1
#define LOGIN 2
using namespace std;

struct Entry {
	string ID;
	string PASSWORD;
	int valid;

	Entry() {
		ID = "";
		PASSWORD = "";
		valid = NOITEM;
	}

	Entry(string I, string P) {
		ID = I;
		PASSWORD = P;
		valid = LOGOUT;
	}

	void valid_LOGIN() {
		valid = LOGIN;
	}

	void valid_LOGOUT() {
		valid = LOGOUT;
	}
	
};

class HashTable {
	Entry* hash_table;
	int capacity;

	int hash_func(string ID) {
		int sum = 0;
		for (int i = 0; i < ID.length(); i++) {
			sum += (ID[i] - 'a') * pow(26, i);
		}
		return sum % capacity;
	}

public:
	HashTable(int c) {
		capacity = c;
		hash_table = new Entry[capacity];
	}

	void put(string i, string p) {
		int idx = hash_func(i);
		int probing = 1;

		while (hash_table[idx].valid != NOITEM && probing <= capacity) {
			idx += 1;
			probing++;
		}
		
		if (probing > capacity) return;
		hash_table[idx] = Entry(i, p);
		return;
	}


	void signup(string i, string p) {
		if (find(i).valid == NOITEM) { // 등록한 적 없는 ID
			cout << "Submit" << endl;
			put(i, p);
		}
		else {
			cout << "Invalid" << endl;
		}
	}

	void login(string i, string p) {
		if (find(i).valid == NOITEM || find(i).PASSWORD != p) {
			cout << "Invalid" << endl;
		}
		else if (find(i).PASSWORD == p && find(i).valid == LOGIN) {
			cout << "Quit" << endl;
		}
		else if (find(i).PASSWORD == p && find(i).valid == LOGOUT) {
			cout << "Submit" << endl;
			find(i).valid_LOGIN();
		}
	}

	void logout(string i) {
		find(i).valid_LOGOUT();
		cout << "Submit" << endl;
	}

	Entry find(string i) {
		int idx = hash_func(i);
		int probing = 1;

		while (idx <= capacity) {
			if (hash_table[idx].ID == i) return hash_table[idx];
			idx += 1;
			probing++;
		}

	}

};

int main() {
	int T;
	cin >> T;

	HashTable* HT = new HashTable(400000);

	string s, id, p;
	for (int i = 0; i < T; i++) {
		cin >> s;
		if (s == "login") {
			cin >> id >> p;
			HT->login(id, p);
		}
		else if (s == "logout") {
			cin >> id;
			HT->logout(id);
		}
		else if (s == "signup") {
			cin >> id >> p;
			HT->signup(id, p);
		}
	}
}