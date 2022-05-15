#include <iostream>
using namespace std;

// https://doublesprogramming.tistory.com/236 참고
// 모르겠다 ㅅㅂ 시험기간에 다시 하자

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;

	Node(int k) {
		key = k;
		left = right = parent = NULL;
	}
};

class BST {

public:

	Node* root;

	int depth(Node* cur) {
		int count = 0;

		while (cur != root) {
			cur = cur->parent;
			count++;
		}

		return count;
	}

	Node* search(Node* cur, int k) {
		if (cur == NULL) return NULL;

		if (cur->key == k) return cur;
		else if (cur->key < k) return search(cur->right, k);
		else return search(cur->left, k);
	}

	void insert(int k) {
		if (search(root, k) != NULL) return;

		Node* newNode = new Node(k);
		if (root == NULL) {
			root = newNode;
			return;
		}

		Node* cur = root;
		Node* par = NULL;

		while (cur != NULL) {
			par = cur;

			if (cur->key < k) cur = cur->right;
			else cur = cur->left;
		}

		newNode->parent = par;

		if (par->key < k) par->right = newNode;
		else par->left = newNode;

		cout << depth(newNode) << endl;
	}

	void remove(int k) {
		Node* delNode = search(root, k);

		cout << depth(delNode) << endl;

		Node* par = delNode->parent;
		Node* chi;

		if (delNode->right == NULL && delNode->left == NULL) chi = NULL;
		else if (delNode->right != NULL && delNode->left == NULL) chi = delNode->right;
		else if (delNode->right == NULL && delNode->left != NULL) chi = delNode->left;
		else {
			chi = delNode->right;
			while (chi->left != NULL) chi = chi->left;
			delNode = chi;
			par = delNode->parent;
			chi = delNode->right;
		}

		if (par == NULL) {
			root = chi;
			if (root != NULL) root->parent = NULL;
		}
		else if (delNode == par->left) {
			par->left = chi;
			if (chi != NULL) chi->parent = par;
		}
		else {
			par->right = chi;
			if (chi != NULL) chi->parent = par;
		}
		delete delNode;

	}

	int treeSize(Node* node) {
		if (node == NULL) return 0;

		return (treeSize(node->left) + treeSize(node->right) + 1);
	}

	Node* min(Node* cur, int k) {
		int n = treeSize(cur->left) + 1;

		if (n == k) return cur;

		if (n > k) return min(cur->left, k);

		return min(cur->right, k - n);
	}


	int height(Node* cur) {

		int h = 0;
		if (cur != NULL) h = 1 + max(height(cur->left), height(cur->right));
		return h;
	}
	
};

int main() {
	int T, X;
	cin >> T;

	BST* bst = new BST();

	string s;
	
	for (int i = 0; i < T; i++) {
		cin >> s;
		if (s == "insert") {
			cin >> X;
			bst->insert(X);
		}
		else if (s == "delete") {
			cin >> X;
			bst->remove(X);
		}
		else if (s == "min") {
			cin >> X;
			cout << bst->min(bst->root, X)->key << endl;
		}
		else if (s == "height") {
			cin >> X;
			cout << bst->height(bst->search(bst->root, X)) << endl;
		}
	}
}