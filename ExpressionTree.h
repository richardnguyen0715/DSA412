#pragma once
#include"BST.h"
#include"stack.h"
#define MAX_SIZE 50
using namespace std;

struct Num {
	char val[MAX_SIZE];
	char ope;
};

bool checkOperator(char x[], int pos) {
	if ((x[pos] == '-' && x[pos + 1] == ' ') || (x[pos] == '-' && x[pos + 1] == '\0') ||
		x[pos] == '+' || x[pos] == '*' || x[pos] == '/' || x[pos] == '^') return true;
	return false;
}

void cutNum(char source[],Num &num, int sPos, int ePos) {
	int cnt = 0;
	for (int i = sPos; i <= ePos; i++) {
		num.val[cnt] = source[i];
		cnt++;
	}
	num.val[cnt] = '\0';
}


stack<bstNode<Num>*> Process(char source[]) {
	stack<bstNode<Num>*> s;
	s.init();
	int i = 0;
	while (source[i] != '\0') {
		if (source[i] == ' ') {
			i++;
		}
		else if (checkOperator(source, i) == true) {
			bstNode<Num>* opeRoot = new bstNode<Num>;
			opeRoot->data.ope = source[i];
			opeRoot->data.val[0] = ' ';
			bstNode<Num>* temp1 = s.top->data;
			s.pop();
			bstNode<Num>* temp2 = s.top->data;
			s.pop();
			opeRoot->left = temp2;
			opeRoot->right = temp1;
			s.push(opeRoot);
			i++;
		}
		else {
			bstNode<Num>* temp = new bstNode<Num>;
			temp->left = nullptr;
			temp->right = nullptr;
			int sPos = i;
			while (source[i] != ' ') {
				i++;
			}
			int ePos = i - 1;
			cutNum(source, temp->data, sPos, ePos);
			s.push(temp);
		}
	}
	return s;
}



void print2DTree_Expression(bstNode<Num>* root, int space) {
	if (root == nullptr) return;
	space += 10;
	print2DTree_Expression(root->right, space);
	cout << endl;
	for (int i = 10; i < space; i++) {
		cout << " ";
	}
	if (root->data.val[0] != ' ') {
		cout << root->data.val << endl;
	}
	else {
		cout << root->data.ope << endl;
	}
	print2DTree_Expression(root->left, space);
}
