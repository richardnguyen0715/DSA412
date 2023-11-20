#pragma once
#include<iostream>

using namespace std;

template<typename T>
struct Node {
	T data;
	Node* next;
};

template<typename T>
Node<T>* makeNode(T key) {
	Node<T>* newNode = new Node<T>;
	if (newNode != nullptr) {
		newNode->data = key;
		newNode->next = nullptr;
		return newNode;
	}
	return nullptr;
}

template<typename T>
struct stack {
	Node<T>* top;

	// Constructor
	void init() {
		top = nullptr;
	}

	// Destructor
	void deinit() {
		while (top != nullptr) {
			Node<T>* temp = top;
			top = top->next;
			delete temp;
			temp = nullptr;
		}
	}

	// Is the stack empty?
	bool empty() {
		if (top == nullptr) return true;
		return false;
	}
	
	// Push an element into stack
	bool push(T key) {
		Node<T>* newNode = makeNode(key);
		if (newNode == nullptr) return false;
		newNode->next = top;
		top = newNode;
		return true;
	}

	// Pop the top out of stack
	bool pop() {
		if (top == nullptr) return false;
		Node<T>* newNode = top;
		top = top->next;
		delete newNode;
		newNode = nullptr;
		return true;
	}

	// Show value of the top node of stack
	T peek() {
		return top->data;
	}

	// Return the size of stack
	int size() {
		Node<T>* runNode = top;
		int cnt = 0;
		while (runNode != nullptr) {
			cnt++;
			runNode = runNode->next;
		}
		return cnt;
	}

	//print all value of a stack
	void print() {
		Node<T>* runNode = top;
		while (runNode != nullptr) {
			cout << runNode->data << " ";
			runNode = runNode->next;
		}
	}

};
