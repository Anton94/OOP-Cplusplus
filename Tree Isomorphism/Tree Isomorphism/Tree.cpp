
#include <iostream>		// ostream
#include <algorithm>	// sort
#include "Tree.h"



/*
*	Constructors and destructors
*/
Tree::Node::~Node()
{
	size_t size = children.size();
	for (size_t i = 0; i < size; ++i)
		delete children[i];
}
Tree::Tree()
{
	setDefaultValues();
}

Tree::Tree(const char * data)
{
	setDefaultValues();
	generateTreeByString(data, root);
	updateTotalChildren(root);
}

Tree::~Tree()
{
	delete root; // cascade destructor of Node
}

void Tree::setDefaultValues()
{
	root = NULL;
}


/*
*	Checks if the tree is isomorph with the other given tree @other.
*/

bool Tree::SortCompare::operator()(Tree::Node * left, Tree::Node * right) const
{
	return left->totalNodes > right->totalNodes;
}

bool Tree::isIsomorphWithOtherTree(const Tree& other) const
{
	if (!root && !other.root)
		return true; // Empty trees.
	if (!root || !other.root)
		return false; // One of the two trees is empty.

	queue<Tree::Node*> left; // queue for the left tree(@*this)
	left.push(root);
	left.push(NULL); // Delimiter of the levels
	queue<Tree::Node*> right; // queue for the given one(@other)
	right.push(other.root);
	right.push(NULL); // Delimiter of the levels

	while (!left.empty() && !right.empty()) // I will iterate the BFS level-by-level
	{
		vector<Tree::Node*> nodesLeft;  // The nodes on each level in the left tree (@*this)
		vector<Tree::Node*> nodesRight; // The nodes on each level in the right tree (@other)

		// Take the childs on the current level of left tree (in @nodesLeft vector) and right tree (in @nodesRight vector)
		iterateTreeLevel(left, nodesLeft);
		iterateTreeLevel(right, nodesRight);

		if (nodesLeft.size() != nodesRight.size())
			return false; // The number of childs on the current level is different.

		// Sort the childs so I can easy check if they match.
		std::sort(nodesLeft.begin(), nodesLeft.begin() + nodesLeft.size(), compare);
		std::sort(nodesRight.begin(), nodesRight.begin() + nodesRight.size(), compare);

		// Compare the values
		size_t size = nodesLeft.size();
		for (size_t i = 0; i < size; ++i)
			if (nodesLeft[i]->totalNodes != nodesRight[i]->totalNodes)
				return false;
	}

	if (!left.empty() || !right.empty()) // if there is some left element
		return false;

	return true;
}

// BFS and writes the children in the given vector on the current level(delim NULL ptr)
void Tree::iterateTreeLevel(queue<Tree::Node*> & q, vector<Tree::Node*> & v) const
{
	while (!q.empty())
	{
		Tree::Node* temp = q.front();
		q.pop();

		if (!temp)
		{
			if (q.empty())
				return;

			q.push(NULL);
			return;
		}

		size_t size = temp->children.size();
		for (size_t i = 0; i < size; ++i)
			q.push(temp->children[i]);

		v.push_back(temp);
	}
}

/*
*	Print the tree in the give ostream.
*/

void Tree::printDFS(std::ostream& out) const
{
	printDFS(out, root);
	out << "\n";
}

void Tree::printDFS(std::ostream& out, Tree::Node * n) const
{
	if (!n)
		return;

	out << "{" << n->value << ", children: " << n->totalNodes << "} ";

	size_t size = n->children.size();
	for (size_t i = 0; i < size; ++i)
		printDFS(out, n->children[i]);
}

void Tree::printBFS(std::ostream& out) const
{
	if (!root)
		return; // Empty tree
	queue<Tree::Node*> q;
	q.push(root);

	while (!q.empty())
	{
		Tree::Node* temp = q.front();
		q.pop();

		if (!temp)
			out << "NULL ";
		else
			out << "{" << temp->value << ", children: " << temp->totalNodes << "} ";

		size_t size = temp->children.size();
		for (size_t i = 0; i < size; ++i)
			q.push(temp->children[i]);
	}

	out << "\n";
}

/*
*	Generate the tree from the given string.
*/
// The sequence is (@num {children})
//  (5 {(9 {}) (1 {(4 {}) (12 {}) (42 {})})})
void Tree::generateTreeByString(const char*& data, Tree::Node *& n)
{
	if (*data != '(')
		return;

	++data; // skip the '('

	int number = getIntFromString(data);
	n = new Node(number);

	if (*data != '{')
		return;

	++data; // skip the '{'
	while (*data != ')')
	{
		Tree::Node * temp = NULL;

		if (*data == '(')
		{
			generateTreeByString(data, temp);
			n->children.push_back(temp);
		}
		else // *data == '}' No children
		{
			++data;
		}
	}

	++data; // Skip the ')'

	if (*data != '\0' && *data == ' ')
		++data; // Skip the white space.
}

/*
*	Makes DFS and updates the total child nodes of the given node.
*/
void Tree::updateTotalChildren(Node * n)
{
	if (!n)
		return; // Error something...

	int sum = 1; //Itself

	// If there is no childs the sum will be 1 (so the correct totalNodes.
	size_t size = n->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		updateTotalChildren(n->children[i]);
		sum += n->children[i]->totalNodes;
	}

	n->totalNodes = sum;
}

/*
*	Returns the number in the given string and moves the pointer after the white space(there is white space after the number).
*/
int Tree::getIntFromString(const char*& data) const // In utility.h TODO
{
	int number = 0;
	bool negative = false;
	if (*data == '-')
	{
		negative = true;
		++data;
	}

	while (*data >= '0' && *data <= '9')
	{
		number *= 10;
		number += int(*data - '0');
		++data;
	}

	if (*data != '\0' && *data == ' ')
		++data; // Skip the white space.

	return negative ? -number : number;
}