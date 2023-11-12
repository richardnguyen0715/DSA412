#pragma once
#include<iostream>

using namespace std;

namespace functionQueue {

	template<typename T>
	struct Node {
		T key;
		Node* next;
	};

	template<typename T>
	struct queue {
		Node<T>* front;
		Node<T>* end;

		//initialize a queue
		void init() {
			front = nullptr;
			end = nullptr;
		}

		//deinitialize a queue
		void deinit() {
			if (empty() == true) return;
			Node<T>* temp = nullptr;
			while (front != nullptr) {
				temp = front;
				front = front->next;
				delete temp;
			}
			front = nullptr;
			end = nullptr;
		}

		//create a  new node 
		Node<T>* createNode(T data) {
			Node<T>* temp = new Node<T>;
			temp->key = data;
			temp->next = nullptr;
			return temp;
		}

		//Is the queue empty?
		bool empty() {
			if (front == nullptr) return true;
			return false;
		}

		//Return size of queue
		int size() {
			if (empty() == true) return 0;
			int cnt = 0;
			Node<T>* temp = front;
			while (temp != nullptr) {
				cnt++;
				temp = temp->next;
			}
			return cnt;
		}

		//Push a node into the tail of queue
		bool push(T data) {
			Node<T>* temp = createNode(data);
			if (temp == nullptr) {
				throw "Can not creat node!";
				return false;
			}
			if (empty() == true) {
				front = temp;
				end = temp;
			}
			else {
				end->next = temp;
				end = temp;
			}
			return true;
		}

		//Remove a node from the top of queue
		bool pop() {
			if (empty() == true) {
				throw "out of range";
				return false;
			}
			if (size() == 1) {
				delete front;
				front = nullptr;
				end = nullptr;
			}
			else {
				Node<T>* temp = front;
				front = front->next;
				delete temp;
				temp = nullptr;
			}
			return true;
		}

		void print() {
			if (empty() == true) {
				cout << "Queue is empty!\n";
				return;
			}
			Node<T>* temp = front;
			while (temp != nullptr) {
				cout << temp->key << " ";
				temp = temp->next;
			}
		}

	//Struct queue
	};

//Namespace queue
}
