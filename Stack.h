#pragma once
#include<iostream>
using namespace std;
namespace functionStack {
	template<typename T>
	struct Node {
		T key;
		Node* next;
	};

	template<typename T>
	struct stack {

		// Top of stack
		Node<T>* top;
		
		//Creat a new node 
		Node<T>* creatNode(T data) {
			Node<T>* temp = new Node<T>;
			temp->key = data;
			temp->next = nullptr;
			return temp;
		}

		//initilizie a stack
		void init() {
			top = nullptr;
		}

		//Is the stack empty?
		bool empty() {
			if (top == nullptr) return true;
			return false;
		}

		//Delete all nodes of stack
		void deinit() {
			if (empty() == true) return;
			Node<T>* temp = nullptr;
			while (top != nullptr) {
				temp = top;
				top = top->next;
				delete temp;
			}
			top == nullptr;
		}

		//Return size of stack
		int size() {
			if (empty() == true) return 0;
			int cnt = 0;
			Node<T>* temp = top;
			while (temp != nullptr) {
				cnt++;
				temp = temp->next;
			}
			return cnt;
		}

		//Push a node into the top of stack
		bool push(T data) {
			Node<T>* temp = creatNode(data);
			if (temp == nullptr) {
				return false;
			}
			temp->next = top;
			top = temp;
			return true;
		}

		//Pop the top out of a stack
		bool pop() {
			if (empty() == true) {
				throw "out of range";
				return false;
			}
			Node<T>* temp = top;
			if (temp == nullptr) {
				throw "Can not creat node!";
				return false;
			}
			top = top->next;
			delete temp;
			temp = nullptr;
			return true;
		}

		void print() {
			if (empty() == true) {
				cout << "Stack is empty!";
				return;
			}
			else {
				Node<T>* temp = top;
				while (temp != nullptr) {
					cout << temp->key << " ";
					temp = temp->next;
				}
			}
		}

	//Struct queue
	};

//Namespace stack
}
