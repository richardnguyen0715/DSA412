#pragma once
#include<iostream>
#include<math.h>
#include"stack.h"
#include"queue.h"

namespace BST {

	template<typename T>
	struct Node {
		T key;
		Node* left;
		Node* right;
	};

	template<typename T>
	struct Tree {

		Node<T>* root;

		//initialize a binary search tree
		void init() {
			root == nullptr;
		}

		//deinitialize a binary search tree
		void deinit(Node<T>* &root) {
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
				throw "Key is not exist";
				return nullptr;
			}
			if (key < root->key) {
				search(root->left, key);
			}
			else if (key > root->key) {
				search(root->right, key);
			}
			else if(key == root->key) {
				return root;
			}
		}

		//Insert a node into a tree
		bool insert(Node<T>* &root, T key) {
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
		bool remove(Node<T>* &root, T data) {
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
		void treeToArray(T a[], int &n, Node<T>* root) {
			if (root == nullptr) return;
			treeToArray(a, n, root->left);
			a[n] = root->key;
			n++;
			treeToArray(a, n, root->right);
		}

		//Count the number of nodes in a tree
		int countNode(Node<T>* root) {
			int n=0;
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
			for (int i = 0; i < n-1; i++) {
				if (a[i] >= a[i+1]) return false;
			}
			return true;
		}

		//Is node have 0 or 2 childs?
		bool isFullChild(Node<T>* p) {
			if (p->left == nullptr && p->right == nullptr) return true;
			if (p->left != nullptr && p->right != nullptr) return true;
			return false;
		}

		//Is the tree a full binary search tree?
		bool isFullBST(Node<T>* root) {
			if (root == nullptr) return true;
			if (isBST(root) == true) {
				if (isFullChild(root) == true) {
					return isFullBST(root->left) && isFullBST(root->right);
				}
			}
			return false;
		}


	//Struct Tree
	};

//Namespace
}
