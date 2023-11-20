#pragma once
#include<iostream>
#include"stack.h"

using namespace std;

template<typename T>
struct queue {
	Node<T>* front;
	Node<T>* end;

	void init()
	{
		front = nullptr;
		end = nullptr;
	}

	void deinit() {
		while (front != nullptr) {
			Node<T>* temp = front;
			front = front->next;
			delete temp;
			temp = nullptr;
		}
		delete end;
		end = nullptr;
	}

	bool empty() {
		if (front == nullptr) return true;
		return false;
	}

	bool push(T key) {
		Node<T>* newNode = makeNode(key);
		if (newNode == nullptr) return false;
		if (empty() == true) {
			front = newNode;
			end = newNode;
		}
		else {
			end->next = newNode;
			end = newNode;
		}
		return true;
	}

	bool pop() {
		if (empty() == true) return false;
		Node<T>* newNode = front;
		front = front->next;
		delete newNode;
		newNode = nullptr;
		return true;
	}

	T peek() {
		if (empty() != true) return front->data;
		return NULL;
	}

	int size() {
		int cnt = 0;
		Node<T>* runNode = front;
		while (runNode != nullptr) {
			cnt++;
			runNode = runNode->next;
		}
		return cnt;
	}

	void print() {
		Node<T>* runNode = front;
		while (runNode != nullptr) {
			cout << runNode->data << " ";
			runNode = runNode->next;
		}
	}
};
