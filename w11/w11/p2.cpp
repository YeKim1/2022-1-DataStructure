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
	int size;
public:
	BST() {
		root = NULL;
		size = 0;
	}

	int depth(node* cur) {
		int d = 0;
		while (cur != root) {
			cur = cur->parent;
			d++;
		}
		return d;
	}

	node* search(node* cur, int key) {
		if (cur == NULL) return NULL;

		if (cur->key == key) return cur;
		else if (cur->key < key) return search(cur->right, key);
		else return search(cur->left, key);

	}

	void insert(int key) {
		if (search(root, key) != NULL) return;

		node* newNode = new node(key);

		if (root == NULL) {
			root = newNode;
			cout << depth(newNode) << endl;
			return;
		}

		node* cur = root;
		node* par = NULL;

		while (cur != NULL) {
			par = cur;
			if (cur->key > key) cur = cur->left;
			else cur = cur->right;
		}

		newNode->parent = par;
		if (par->key > key) par->left = newNode;
		else par->right = newNode;

		size++;

		cout << depth(newNode) << endl;

	}

	void remove(int key) {
		node* delNode = search(root, key);
		if (delNode == NULL) return;

		cout << depth(delNode) << endl;

		node* par = delNode->parent;
		node* child;

		if (delNode->left == NULL && delNode->right == NULL) child = NULL;
		else if (delNode->left != NULL && delNode->right == NULL) child = delNode->left;
		else if (delNode->left == NULL && delNode->right != NULL) child = delNode->right;
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
		else if (delNode == par->left) {
			par->left = child;
			if (child != NULL) child->parent = par;
		}
		else {
			par->right = child;
			if (child != NULL) child->parent = par;
		}

		size--;

		delete delNode;
	}


	node* min(node* n, int& k) {
		if (n == NULL) return NULL;

		node* left = min(n->left, k);

		if (left != NULL) return left;

		k--;
		if (k == 0) return n;

		return min(n->right, k);

	}

	int height(node* n) {
		if (!n) return 0;
		else {
			int left_h = height(n->left);
			int right_h = height(n->right);
			return 1 + (left_h > right_h ? left_h : right_h);
		}
	}

	node* r() { return root; }

	int size_() { return size; }

	void inorder(node* n) {
		if (n != NULL) {

			inorder(n->left);
			cout << n->key << " ";
			inorder(n->right);

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
		else if (s == "print") {
			bst->inorder(bst->r());
		}
		else if (s == "min") {
			cin >> x;
			cout << bst->min(bst->r(), x)->key << endl;
		}
		else if (s == "height") {
			cin >> x;
			cout << bst->height(bst->search(bst->r(), x)) - 1 << endl;
		}
	}
}