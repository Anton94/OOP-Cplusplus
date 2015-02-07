#pragma once

struct Node
{
	Node(char d);
	char data;
	Node* left, *right;
};


class Tree
{
public:
	Tree(const char* rpn);
	void printInOrder() const; 
	double calcPostOrder() const;
	double calcInOrder() const;
	~Tree();
private:
	void printInOrder(Node * root) const;
	double calcPostOrder(Node * root) const;
	double calcInOrder(Node * root) const;
	void deleteRoot(Node * root);
private:
	Node * root;
};


bool isDigit(char ch);
bool isOper(char ch);
bool isValidSymbol(char ch);