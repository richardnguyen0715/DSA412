#pragma once
#include<iostream>
#include<math.h>
#include"stack.h"
#include"queue.h"

namespace AVLTree {

	template<typename T>
	struct Node {
		T key;
		Node* left;
		Node* right;
		int height;
	};

	template<typename T>
	struct Tree {

		Node<T>* root;

		//initialize a binary search tree
		void init() {
			root == nullptr;
		}

		//deinitialize a binary search tree
		void deinit(Node<T>*& root) {
			if (root == nullptr) return;
			deinit(root->left);
			deinit(root->right);
			delete root;
		}

		//is the tree empty?
		bool empty() {
			if (root == nullptr) return true;
			return false;
		}

		//create a new node
		Node<T>* creatNode(T data) {
			Node<T>* temp = new Node<T>;
			temp->key = data;
			temp->left = nullptr;
			temp->right = nullptr;
			temp->height = 0;
			return temp;
		}

		//  PreOder Travesel - NLR
		void NLR(Node<T>* root) {
			if (root == nullptr) return;
			cout << root->key << " ";
			NLR(root->left);
			NLR(root->right);
		}

		// inOder travesel - LNR
		void LNR(Node<T>* root) {
			if (root == nullptr) return;
			LNR(root->left);
			cout << root->key << " ";
			LNR(root->right);
		}

		// posOder travesel - LRN
		void LRN(Node<T>* root) {
			if (root == nullptr) return;
			LRN(root->left);
			LRN(root->right);
			cout << root->key << " ";
		}

		// levelOder travesel 
		void levelOder(Node<T>* root) {
			if (root == nullptr) {
				cout << "Tree is empty! \n";
				return;
			}
			functionQueue::queue<Node<T>*> q;
			q.init();
			q.push(root);
			q.push(NULL);
			Node<T>* temp = NULL;
			while (q.size() > 1) {
				temp = q.front->key;
				q.pop();
				if (temp == NULL) { // Finished a level
					q.push(NULL);
					cout << endl;
				}
				else {
					if (temp->left != nullptr) {
						q.push(temp->left);
					}
					if (temp->right != nullptr) {
						q.push(temp->right);
					}
					cout << temp->key << " ";
				}
			}
		}

		//Seach a key in tree
		Node<T>* search(Node<T>* root, T key) {
			if (root == nullptr) {
				cout<< "Key is not exist";
				return nullptr;
			}
			if (key < root->key) {
				search(root->left, key);
			}
			else if (key > root->key) {
				search(root->right, key);
			}
			else if (key == root->key) {
				return root;
			}
		}

		//Rotate left
		Node<T>* rotateLeft(Node<T>* root) {
			Node<T>* rightChild = root->right;
			Node<T>* leftOfRightChild = rightChild->left;
			root->right = leftOfRightChild;
			rightChild->left = root;
			return rightChild;
		}

		//Rotate right
		Node<T>* rotateRight(Node<T>* root) {
			Node<T>* leftChild = root->left;
			Node<T>* rightOfLeftChild = leftChild->right;
			root->left = rightOfLeftChild;
			leftChild->right = root;
			return leftChild;
		}

		//Check sitiuation of a unbalance node
		int checkSitiuation(Node<T>* root) {
			if (root != nullptr) {
				if (height(root->left) - height(root->right) > 0) { // Left deviated
					if (height(root->left->left) - height(root->left->right) > 0)
						return 1;	//Left - Left
					else	
						return 2;	// Left - Right
				}
				else { // Right deviated
					if (height(root->right->left) - height(root->right->right) > 0) 
						return 3;	// Right - Left
					else    
						return 4;	// Right - Right
				}
			}
		}

		//Is node balance?
		bool isBalance(Node<T>* root) {
			if (root != nullptr) {
				if (abs(height(root->left) - height(root->right)) > 1) {
					return false;
				}
			}
			return true;
		}

		Node<T>* findParent(T x, Node<T>* root) {
			Node<T>* temp = root;
			while (temp != nullptr) {
				if (x < temp->key) {
					if (temp->left != nullptr) {
						if (temp->left->key == x) {
							return temp;
						}
						else {
							temp = temp->left;
						}
					}
					else {
						cout << "Node x khong ton tai";
						return nullptr;
					}
				}
				else if (x > temp->key) {
					if (temp->right != nullptr) {
						if (temp->right->key == x) {
							return temp;
						}
						else {
							temp = temp->right;
						}
					}
					else {
						cout << "Node x khong ton tai";
						return nullptr;
					}
				}
				else {
					return temp;
				}
			}
		}

		//Rotate node to right if it not balance 
		Node<T>* rotateNode(Node<T>* &root) {
			if (root == nullptr) {	
				throw "Out of range!";
				return nullptr;
			}
			else if (checkSitiuation(root) == 1) { // Left - Left
				root = rotateRight(root);
			}
			else if (checkSitiuation(root) == 4) { // Right - Right
				root = rotateLeft(root);
			}
			else if (checkSitiuation(root) == 2) { // Left - Right
				root->left = rotateLeft(root->left);
				root = rotateRight(root);
			}
			else if (checkSitiuation(root) == 3) { // Right - Left
				root->right = rotateRight(root->right);
				root = rotateLeft(root);
			}
			return root;
		}

		//Balance a tree
		void balanceTree(Node<T>* &run, Node<T>* root ) {
			if (run == nullptr) return;
			balanceTree(run->left, root);
			balanceTree(run->right, root);
			if (isBalance(run) == false) {
				Node<T>* parent = findParent(run->key, root);
				if (run->key > parent->key) {
					parent->right = rotateNode(run);
				}
				else if (run->key < parent->key)  {
					parent->left = rotateNode(run);
				}
				else if (run->key == parent->key) {
					run = rotateNode(run);
				}
			}
		}

		//Update Height of Node
		void updateHeight(Node<T>* root) {
			if (root == nullptr) return;
			root->height = height(root);
			updateHeight(root->left);
			updateHeight(root->right);
		}
		
		//Insert a node into a tree
		bool insertNode(Node<T>*& root, T key) {
			if (root == nullptr) {
				Node<T>* temp = creatNode(key);
				if (temp == nullptr) {
					throw "can not creat node! \n";
					return false;
				}
				root = temp;
				return true;
			}
			else if (key < root->key) {
				insert(root->left, key);
			}
			else if (key > root->key) {
				insert(root->right, key);
			}
			else if (key == root->key) {
				return true;
			}
		}

		void insert(Node<T>* &root, T key) {
			insertNode(root, key);
			balanceTree(root, root);
			updateHeight(root);
		}

		//Find the minimist node of right child 
		void minimum(Node<T>*& root, Node<T>*& mini) {
			if (root->left == nullptr) {
				mini->key = root->key;
				mini = root;
				root = root->right;
			}
			else {
				minimum(root->left, mini);
			}
		}

		//Remove a node in tree
		bool removeNode(Node<T>*& root, T data) {
			if (root == nullptr) {
				throw "Data is not exist! \n";
				return false;
			}
			else if (data < root->key) {
				remove(root->left, data);
			}
			else if (data > root->key) {
				remove(root->right, data);
			}
			else if (data == root->key) {
				Node<T>* mini = root;
				if (root->left == nullptr) {
					root = root->right;
				}
				else if (root->right == nullptr) {
					root = root->left;
				}
				else {
					minimum(root->right, mini);
				}
				delete mini;
			}
			return true;
		}

		//Remove node and balance 
		void remove(Node<T>*& root, T data) {
			removeNode(root, data);
			balanceTree(root, root);
			updateHeight(root);
		}

		//Create tree from an array
		Node<T>* arrayToTree(T a[], int n) {
			Node<T>* temp = nullptr;
			for (int i = 0; i < n; i++) {
				insert(temp, a[i]);
			}
			return temp;
		}

		//Height of node
		int height(Node<T>* root) {
			if (root == nullptr) return 0;
			return 1 + max(height(root->left), height(root->right));
		}

		//Create an array from a tree
		void treeToArray(T a[], int& n, Node<T>* root) {
			if (root == nullptr) return;
			treeToArray(a, n, root->left);
			a[n] = root->key;
			n++;
			treeToArray(a, n, root->right);
		}

		//Count the number of nodes in a tree
		int countNode(Node<T>* root) {
			int n = 0;
			T a[30];
			treeToArray(a, n, root);
			return n;
		}

		//Return sum of nodes in a tree
		int sumNode(Node<T>* root) {
			int n = 0;
			int sum = 0;
			T a[30];
			treeToArray(a, n, root);
			for (int i = 0; i < n; i++) {
				sum += a[i];
			}
			return sum;
		}

		//Height of node has a default key
		int heightKey(Node<T>* root, T key) {
			Node<T>* temp = search(root, key);
			if (temp == nullptr) {
				throw "Key is not exist!\n";
				return 0;
			}
			return height(temp);
		}

		//Level of a node in tree
		int levelOfNode(Node<T>* root, Node<T>* p) {
			return height(root) - height(p);
		}

		//Count the number of node leaf in a tree
		int countLeaf(Node<T>* root) {
			if (root == nullptr) return 0;
			if (root->left == nullptr && root->right == nullptr) return 1;
			return countLeaf(root->left) + countLeaf(root->right);
		}

		//Count the number of node which is less than a key in a tree
		int countLess(Node<T>* root, T key) {
			int n = 0;
			int cnt = 0;
			T a[30];
			treeToArray(a, n, root);
			for (int i = 0; i < n; i++) {
				if (key > a[i]) {
					cnt++;
				}
			}
			return cnt;
		}

		//Count the number of node which is greater than a key in a tree
		int countGreat(Node<T>* root, T key) {
			int n = 0;
			int cnt = 0;
			T a[30];
			treeToArray(a, n, root);
			for (int i = 0; i < n; i++) {
				if (key < a[i]) {
					cnt++;
				}
			}
			return cnt;
		}

		//Is the tree a binary search tree?
		bool isBST(Node<T>* root) {
			int n = 0;
			T a[30];
			treeToArray(a, n, root);
			for (int i = 0; i < n - 1; i++) {
				if (a[i] >= a[i + 1]) return false;
			}
			return true;
		}

		// Is the tree a AVL tree?
		bool isAVL(Node<T>* root) {
			if (root == nullptr) return true;
			if (isBalance(root) == true) return true;
			else {
				return false;
			}
			return isAVL(root->left) && isAVL(root->right);
		}

		//Show heiht of node
		void showHeight(Node<T>* root) {
			functionQueue::queue<Node<T>*> q;
			q.init();
			q.push(root);
			q.push(NULL);
			Node<T>* temp = nullptr;
			while (q.size() > 1) {
				temp = q.front->key;
				q.pop();
				if (temp == NULL) {
					q.push(NULL);
					cout << endl;
				}
				else {
					if (temp->left != NULL) {
						q.push(temp->left);
					}
					if (temp->right != NULL) {
						q.push(temp->right);
					}
					cout << temp->height << " ";
				}
			}
		}

	//Struct Tree
	};

//Namespace
}
