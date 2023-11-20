#pragma once
#include<iostream>
#include"queue.h"
#include"stack.h"

template<typename T>
struct avlNode {
	T data;
	avlNode* left;
	avlNode* right;
	int height;
};

template<typename T>
avlNode<T>* makeAvlNode(T key) {
	avlNode<T>* newNode = new avlNode<T>;
	newNode->data = key;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->height = 0;
	return newNode;
}

template<typename T>
struct Avl {
	avlNode<T>* root;

	void init() {
		root = nullptr;
	}

	void deinit(avlNode<T>* root) {
		if (root == nullptr) return;
		deinit(root->left);
		deinit(root->right);
		delete root;
		root = nullptr;
	}

	void deinit() {
		deinit(root);
	}

	bool empty() {
		if (root == nullptr) return true;
		return false;
	}

	// Preoder travesel
	void NLR(avlNode<T>* root) {
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
	void LNR(avlNode<T>* root) {
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
	void LRN(avlNode<T>* root) {
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
	void levelOder(avlNode<T>* root) {
		if (root == nullptr) return;
		queue<avlNode<T>* > q;
		q.init();
		q.push(root);
		q.push(NULL);
		avlNode<T>* newNode = root;
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
	void print2DTree(avlNode<T>* root, int space) {
		if (root == nullptr) return;
		space += 10;
		print2DTree(root->right, space);
		cout << endl;
		for (int i = 10; i < space; i++) {
			cout << " ";
		}
		cout << root->data << endl;
		print2DTree(root->left, space);
	}

	// Overloading
	void print2DTree() {
		print2DTree(root, 0);
	}

	// Push a node into tree
	void push(avlNode<T>*& root, T key) {
		if (root == nullptr) {
			avlNode<T>* newNode = makeAvlNode(key);
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
		balanceTree(root);
		updateHeight(root);
	}

	// Find minimum of right child tree
	void minimum(avlNode<T>*& root, avlNode<T>*& temp) {
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
	void remove(avlNode<T>*& root, T key) {
		if (key < root->data) {
			remove(root->left, key);
		}
		else if (key > root->data) {
			remove(root->right, key);
		}
		else {
			avlNode<T>* temp = root;
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
		balanceTree(root);
		updateHeight(root);
	}

	// search a node in tree
	avlNode<T>* search(avlNode<T>* root, T key) {
		if (root == nullptr) {
			return nullptr;
		}
		else if (key < root->data) {
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
	avlNode<T>* search(T key) {
		return search(root, key);
	}

	// Find parent of a node in tree
	avlNode<T>* findParent(avlNode<T>* root, T key) {
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
	}

	// Overloading
	avlNode<T>* findParent(T key) {
		return findParent(root, key);
	}

	// Find height of Node
	int height(avlNode<T>* root) {
		if (root == nullptr) return 0;
		return 1 + max(height(root->left), height(root->right));
	}

	// Convert a tree into an array
	void treeToArray(T a[], int& arraySize, avlNode<T>* root) {
		treeToArray(a, arraySize, root->left);
		a[arraySize] = root->data;
		arraySize++;
		treeToArray(a, arraySize, root->right);
	}

	// Overloading
	void treeToArray(T a[], int& arraySize) {
		treeToArray(a, arraySize, root);
	}

	avlNode<T>* rotateLeft(avlNode<T>* root) {
		avlNode<T>* rightChild = root->right;
		avlNode<T>* leftRightChild = rightChild->left;
		rightChild->left = root;
		root->right = leftRightChild;
		return rightChild;
	}

	avlNode<T>* rotateRight(avlNode<T>* root) {
		avlNode<T>* leftChild = root->left;
		avlNode<T>* rightLeftChild = leftChild->right;
		leftChild->right = root;
		root->left = rightLeftChild;
		return leftChild;
	}

	int checkSitiuation(avlNode<T>* root) {
		if (root == nullptr) return 0;
		if (height(root->left) - height(root->right) > 0) { // Left Deviated
			if (height(root->left->left) - height(root->left->right) > 0) return 1; // L - L
			return 2; // L - R
		}
		else { // Right Deviated
			if (height(root->right->right) - height(root->right->left) > 0) return 3; // R - R
			return 4; // R - L
		}
	}

	void rotateNode(avlNode<T>* &root) {
		if (root == nullptr) return;
		if (checkSitiuation(root) == 1) {
			root = rotateRight(root);
		}
		else if (checkSitiuation(root) == 3) {
			root = rotateLeft(root);
		}
		else if (checkSitiuation(root) == 2) {
			root->left = rotateLeft(root->left);
			root = rotateRight(root);
		}
		else if (checkSitiuation(root) == 4) {
			root->right = rotateRight(root->right);
			root = rotateLeft(root);
		}
	}

	void balanceTree(avlNode<T>* &root) {
		if (root == nullptr) return;
		balanceTree(root->left);
		balanceTree(root->right);
		if (isBalance(root) == false) {
			rotateNode(root);
		}
	}

	void updateHeight(avlNode<T>* &root) {
		if (root == nullptr) return;
		updateHeight(root->left);
		updateHeight(root->right);
		root->height = height(root);
	}

	bool isBalance(avlNode<T>* root) {
		if (root == nullptr) return true; 
		if (abs(height(root->left) - height(root->right)) > 1) return false;
		return true;
	}

	// Is this tree balance?
	bool isAVLTree(avlNode<T>* root) {
		if (root == nullptr) return true;
		if (abs(height(root->left) - height(root->right)) > 1) return false;
		return isAVLTree(root->left) && isAVLTree(root->right);
	}

	// Overloading
	void isAVLTree() {
		isAVLTree(root);
	}

};
