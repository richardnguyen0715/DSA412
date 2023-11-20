#pragma once
#include"stack.h"
#include"queue.h"

using namespace std;

template<typename T>
struct bstNode {
	T data;
	bstNode* left;
	bstNode* right;
};

template<typename T>
bstNode<T>* makeBstNode(T key) {
	bstNode<T>* newNode = new bstNode<T>;
	if (newNode != nullptr) {
		newNode->data = key;
		newNode->left = nullptr;
		newNode->right = nullptr;
	}
	return newNode;
}

template<typename T>
struct bstTree {
	bstNode<T>* root;

	void init() {
		root = nullptr;
	}

	void empty() {
		if (root == nullptr) return true;
		return false;
	}

	void deinit(bstNode<T>* root) {
		if (root == nullptr) return;
		deinit(root->left);
		deinit(root->right);
		delete root;
		root = nullptr;
	}

	// Overloading
	void deinit() {
		deinit(root);
	}

	// Preoder travesel
	void NLR(bstNode<T>* root) {
		if (root == nullptr) return;
		cout << root->data << " ";
		NLR(root->left);
		NLR(root->right);
	}

	// Overloading
	void NLR() {
		NLR(root);
	}

	// Inoder travesel
	void LNR(bstNode<T>* root) {
		if (root == nullptr) return;
		LNR(root->left);
		cout << root->data << " ";
		LNR(root->right);
	}

	// Overloading
	void LNR() {
		LNR(root);
	}

	// Posoder travesel
	void LRN(bstNode<T>* root) {
		if (root == nullptr) return;
		LRN(root->left);
		LRN(root->right);
		cout << root->data << " ";
	}

	// Overloading
	void LRN() {
		LRN(root);
	}

	// Leveloder travesel
	void levelOder(bstNode<T>* root) {
		if (root == nullptr) return;
		queue<bstNode<T>* > q;
		q.init();
		q.push(root);
		q.push(NULL);
		bstNode<T>* newNode = root;
		while (q.size() > 1) {
			newNode = q.front->data;
			q.pop();
			if (newNode == NULL) {
				cout << endl;
				q.push(NULL);
			}
			else {
				if (newNode->left != nullptr) {
					q.push(newNode->left);
				}
				if (newNode->right != nullptr) {
					q.push(newNode->right);
				}
				cout << newNode->data << " ";
			}
		}
	}

	// Overloading
	void levelOder() {
		levelOder(root);
	}

	// Print 2D Tree in a pretty way
	void print2DTree(bstNode<T>* root, int space) {
		if (root == nullptr) return;
		space += 10;
		print2DTree(root->right, space);
		cout << endl;
		for (int i = 10; i < space; i++) {
			cout << " ";
		}
		cout << root->data << " ";
		print2DTree(root->left, space);
	}

	// Overloading
	void print2DTree() {
		print2DTree(root, 0);
	}

	// Push a node into tree
	void push(bstNode<T>* &root,T key) {
		if (root == nullptr) {
			bstNode<T>* newNode = makeBstNode(key);
			root = newNode;
		}
		else if (key < root->data) {
			push(root->left, key);
		}
		else if (key > root->data) {
			push(root->right, key);
		}
		else if (key == root->data) {
			;
		}
	}

	// Overloading 
	void push(T key) {
		push(root, key);
	}

	// Find minimum of right child tree
	void minimum(bstNode<T>* &root, bstNode<T>* &temp) {
		if (root->left == nullptr) {
			temp->data = root->data;
			temp = root;
			root = root->right;
		}
		else {
			minimum(root->left, temp);
		}
	}

	// Remove a node out of tree
	void remove(bstNode<T>* &root, T key) {
		if (key < root->data) {
			remove(root->left, key);
		}
		else if (key > root->data) {
			remove(root->right, key);
		}
		else {
			bstNode<T>* temp = root;
			if (root->left == nullptr) {
				root = root->right;
			}
			else if (root->right == nullptr) {
				root = root->left;
			}
			else {
				minimum(root, temp);
			}
			delete temp;
			temp = nullptr;
		}
	}

	// Overloading
	void remove(T key) {
		remove(root, key);
	}

	// search a node in tree
	bstNode<T>* search(bstNode<T>* root,T key) {
		if (root == nullptr) {
			return nullptr;
		}
		else if(key < root->data) {
			search(root->left, key);
		}
		else if (key > root->data) {
			search(root->right, key);
		}
		else {
			return root;
		}
	}

	// Overloading
	bstNode<T>* search(T key) {
		return search(root, key);
	}

	// Find parent of a node in tree
	bstNode<T>* findParent(bstNode<T>* root, T key) {
		if (root == nullptr) return nullptr;
		if (root->data == key) {
			return root;
		}
		else if (key < root->data) {
			if (root->left->data == key) return root;
			findParent(root->left, key);
		}
		else if (key > root->data) {
			if (root->right->data == key) return root;
			findParent(root->right, key);
		}
		return nullptr;
	}

	// Overloading
	bstNode<T>* findParent(T key) {
		return findParent(root, key);
	}

	// Find height of Node
	int height(bstNode<T>* root) {
		if (root == nullptr) return 0;
		return 1 + max(height(root->left), height(root->right));
	}

	// Convert a tree into an array
	void treeToArray(T a[], int &arraySize, bstNode<T>* root) {
		treeToArray(a, arraySize, root->left);
		a[arraySize] = root->data;
		arraySize++;
		treeToArray(a, arraySize, root->right);
	}

	// Overloading
	void treeToArray(T a[], int& arraySize) {
		treeToArray(a, arraySize, root);
	}
};


template<typename T>
void buildTree(bstTree<T> &b, int size) {
	b.init();
	cout << "Enter value of tree: \n";
	for (int i = 0; i < size; i++) {
		int k = 0; cin >> k;
		b.push(k);
	}
}
