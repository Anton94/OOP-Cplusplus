#pragma once

/*
*
*	Anton Vasilev Dudov
*	Tree isomorphism
*
*
*
*	The input tree is given with string like: (5 {(9 {}) (1 {(4 {}) (12 {}) (42 {})})})
*	where the nedes are: (<value> { <children> })
*	The given example is a root 5 with two children: left 9 and right 1. Right (1) has three children: 4, 12 and 42.
*/

#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Tree
{
	struct Node
	{
		int value;
		vector<Node*> children;
		int totalNodes;
		Node(int v) : value(v) , totalNodes(0) {}
		~Node();
	};

	Node * root;
public:
	Tree();
	Tree::Tree(const char * data);
	~Tree();

	void printDFS(std::ostream& out) const;
	void printDFS(std::ostream& out, Node * n) const;

	void printBFS(std::ostream& out) const;

private:
	void setDefaultValues();
	void generateTreeByString(const char*& data, Tree::Node *& n);
	void updateTotalChildren(Node * n);
	int getIntFromString(const char*& data) const;

private:
	Tree(const Tree& other);
	Tree& operator=(const Tree& other);
};