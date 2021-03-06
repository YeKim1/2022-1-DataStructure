#include <iostream>
using namespace std;

struct node {
	int key;
	node* parent;
	node* right;
	node* left;
	node(int k) {
		key = k;
		parent = right = left = NULL;
	}
};

class BST {
private:
	node* root;
public:
	node* search(node* n, int k) {
		if (n == NULL) return NULL;

		if (n->key == k) return n;
		else if (n->key > k) return search(n->left, k);
		else return search(n->right, k);
	}

	void insert(int e) {
		if (search(root, e) != NULL) return;

		node* newNode = new node(e);

		if (root == NULL) {
			root = newNode;
			return;
		}
		node* cur = root;
		node* par = NULL;

		while (cur != NULL) {
			par = cur;
			
			if (cur->key > e) cur = cur->left;
			else cur = cur->right;
		}

		newNode->parent = par;
		
		if (par->key > e) par->left = newNode;
		else par->right = newNode;
	}

	int inorder(node* n, int& count) {
		if (n != NULL) {

			inorder(n->left, count);
			count++;
			inorder(n->right, count);
			return count;
		}
		else return count;
	}

	node* r() { return root; }
};

int main() {
	int n, m, x;

	cin >> n >> m;

	BST* bst = new BST();

	for (int i = 0; i < n; i++) {
		cin >> x;
		bst->insert(x);
	}

	for (int i = 0; i < m; i++) {
		cin >> x;
		int count = 0;
		cout << bst->inorder(bst->search(bst->r(), x)->left, count) << endl;
	}
}