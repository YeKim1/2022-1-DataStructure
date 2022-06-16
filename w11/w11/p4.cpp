#include <iostream>
using namespace std;

struct node {
	int key;
	node* parent;
	node* left;
	node* right;
	node(int k) {
		key = k;
		parent = left = right = NULL;
	}
};

class BST {
private:
	node* root;
public:
	BST() {
		root = NULL;
	}

	node* r() { return root; }

	int depth(node* n) {
		int d = 0;

		while (n != root) {
			n = n->parent;
			d++;
		}

		return d;
	}

	node* search(node* n, int k) {
		if (n == NULL) return NULL;

		if (n->key == k) return n;
		else if (n->key > k) return search(n->left, k);
		else return search(n->right, k);
	}

	void insert(int k) {
		if (search(root, k) != NULL) return;

		node* newNode = new node(k);

		if (root == NULL) {
			root = newNode;
			cout << depth(newNode) << endl;
			return;
		}

		node* cur = root;
		node* par = NULL;

		while (cur != NULL) {
			par = cur;
			
			if (cur->key > k) cur = cur->left;
			else cur = cur->right;
		}

		newNode->parent = par;

		if (par->key > k) par->left = newNode;
		else par->right = newNode;

		cout << depth(newNode) << endl;
	}

	void remove(int k) {
		node* delNode = search(root, k);
		if (delNode == NULL) return;

		cout << depth(delNode) << endl;

		node* par = delNode->parent;
		node* child;

		if (delNode->right == NULL && delNode->left == NULL) child = NULL;
		else if (delNode->right != NULL && delNode->left == NULL) child = delNode->right;
		else if (delNode->right == NULL && delNode->left != NULL) child = delNode->left;
		else {
			child = delNode->right;

			while (child->left != NULL) child = child->left;

			delNode->key = child->key;
			delNode = child;
			par = delNode->parent;
			child = delNode->right;
		}

		if (par == NULL) {
			root = child;
			if (child != NULL) root->parent = NULL;
		}

		else if (delNode == par->right) {
			par->right = child;
			if (child != NULL) child->parent = par;
		}
		else if (delNode == par->left) {
			par->left = child;
			if (child != NULL) child->parent = par;
		}

		delete delNode;
	}

	node* max(node* n, int& k) {
		if (n == NULL) return NULL;
		node* right = max(n->right, k);
		if (right != NULL) return right;
		k--;
		if (k == 0) return n;
		return max(n->left, k);
	}

	int height(node* n) {
		if (!n) return 0;
		else {
			int left_h = height(n->left);
			int right_h = height(n->right);
			return 1 + (left_h > right_h ? left_h : right_h);
		}
	}
};

int main() {
	int T, x;
	cin >> T;

	BST* bst = new BST();

	string s;

	for (int i = 0; i < T; i++) {
		cin >> s; 

		if (s == "insert") {
			cin >> x;
			bst->insert(x);
		}
		else if (s == "delete") {
			cin >> x;
			bst->remove(x);
		}
		else if (s == "max") {
			cin >> x;
			cout << bst->max(bst->r(), x)->key << endl;
		}
		else if (s == "height") {
			cin >> x;
			cout << bst->height(bst->search(bst->r(), x)) - 1 << endl;
		}
	}
}