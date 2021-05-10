#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;



class Tree{
	private:
		char data;
		Tree *leftptr, *rightptr;
	public:
		Tree(char new1, Tree *L, Tree *R);
		~Tree();
		char rootData(){return data;}
		Tree *left(){return leftptr;}
		Tree *right(){return rightptr;}
};

struct Node{
	Tree *safeT;
	Node *next;
};

class Stack {
	private:
		Node *listPtr;
	public:
		Stack();
		~Stack();
		void push(Tree *newT);
		void pop();
		Tree *top();			
		bool isEmpty();
};

void inOrder(Tree *T){
	if(T==NULL){return;}
	if(T->left()!=NULL){cout << "(";}
	inOrder(T->left());
	cout << T->rootData();
	inOrder(T->right());
	if(T->right()!=NULL){cout << ")";}
}

void preOrder(Tree *T){
	if(T==NULL){return;}
	cout << T->rootData() << " ";
	preOrder(T->left());
	preOrder(T->right());
}

void postOrder(Tree *T){
	if(T==NULL){return;}
	postOrder(T->left());
	postOrder(T->right());
	cout << T->rootData() << " ";
}

Stack S;
Tree *leftT, *rightT, *rootT;

int main (int argc, char **argv){
	char digit, oper, expression[100];
	ifstream inputFile;
	if(argc==2) {inputFile.open(argv[1]);}
	else{
		cout << "The program needs a filename as argument" << endl;
		exit(0);
	}
	//inputFile.open("RPN4.txt");
	
	while(inputFile >> expression){
		if(isdigit(expression[0])){
			sscanf(expression, "%c", &digit);
			//cout << digit << endl;
			S.push(new Tree(digit, NULL, NULL));
			
		}else{
			sscanf(expression, "%c", &oper);
			//cout << oper << endl;
			rightT = S.top();
			S.pop();
			leftT = S.top();
			S.pop();
			S.push(new Tree(oper, leftT, rightT));
		}
	}
	rootT = S.top();
	cout << "In-fix:" << endl;
	inOrder(rootT);
	cout << endl << "Post-fix:" << endl;
	postOrder(rootT);
	
}

Tree::Tree(char new1, Tree *L, Tree *R){
	data = new1;
	leftptr = L;
	rightptr = R;
}

Stack::Stack(){
	listPtr=NULL;
}

Stack::~Stack(){
	return;
}

void Stack::push(Tree *newT){
	Node *temp;
	temp = new Node;
	temp->safeT = newT;
	temp->next = listPtr;
	listPtr=temp;
}

void Stack::pop(){
	Node *t;
	t = listPtr;
	if(listPtr!=NULL){
		listPtr = listPtr->next;
		delete t;
	}
}

Tree *Stack::top(){
	if(listPtr!=NULL){
		return listPtr->safeT;
	}else{
		//cout <<"error. Things dun gon wrong" << endl;
		exit(5);
	}
}

bool Stack::isEmpty(){
	if(listPtr==NULL){
		return true;
	}else{
		return false;
	}
}
	
	