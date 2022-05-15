#include <iostream>
using namespace std;

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
	}

	void remove(int k) {
		Node* delNode = search(root, k);
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

	int left_Count(Node* cur) {
		int count;

		if (cur == NULL) count = 0;
		else {
			count = left_Count(cur->left) + left_Count(cur->right) + 1;
		}

		return count;
	}
};

int main() {
	int N, M, X;

	cin >> N >> M;

	BST* bst = new BST();

	for (int i = 0; i < N; i++) {
		cin >> X;
		bst->insert(X);
	}

	for (int j = 0; j < M; j++) {
		cin >> X;
		cout << bst->left_Count(bst->search(bst->root, X)->left) << endl;
	}
}