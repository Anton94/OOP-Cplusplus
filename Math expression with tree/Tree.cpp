#include <iostream>
#include <stack>
#include "Tree.h"

Node::Node(char d)
{
	data = d;
	left = right = NULL;
}

Tree::Tree(const char* rpn)
{
	if (!rpn)
	{
		root = NULL;
	}
	else
	{
		std::stack<Node *> sNode;

		while (*rpn)
		{
			if (isValidSymbol(*rpn)) // for mostly space symbol..
			{
				Node * newNode = new Node(*rpn);

				if (isOper(*rpn))
				{
					newNode->right = sNode.top();
					sNode.pop();
					newNode->left = sNode.top();
					sNode.pop();
				}

				sNode.push(newNode);
			}

			++rpn;
		}

		root = sNode.top();
	}
}

double Tree::calcPostOrder() const
{
	return calcPostOrder(root);
}

double Tree::calcPostOrder(Node * root) const
{
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return root->data - '0';

	double left = calcPostOrder(root->left),
		right = calcPostOrder(root->right);

	switch (root->data)
	{
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/': return left / ((right) ? right : 1); // right != 0
		default: return 0;
	}
}
double Tree::calcInOrder() const
{
	return calcInOrder(root);
}

double Tree::calcInOrder(Node * root) const
{
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return root->data - '0';

	switch (root->data)
	{
		case '+': return calcInOrder(root->left) + calcInOrder(root->right);
		case '-': return calcInOrder(root->left) - calcInOrder(root->right);
		case '*': return calcInOrder(root->left) * calcInOrder(root->right);
		case '/': return calcInOrder(root->left) / calcInOrder(root->right); // right != 0
		default: return 0;
	}
}

void Tree::printInOrder() const
{
	printInOrder(root);
}

void Tree::printInOrder(Node * root) const
{
	if (!root)
		return;

	printInOrder(root->left);
	std::cout << root->data << " ";
	printInOrder(root->right);
}


Tree::~Tree()
{
	deleteRoot(root);
}

void Tree::deleteRoot(Node * root)
{
	if (root)
	{
		deleteRoot(root->left);
		deleteRoot(root->right);
		delete root;
	}
}



bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool isOper(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isValidSymbol(char ch)
{
	return isDigit(ch) || isOper(ch);
}