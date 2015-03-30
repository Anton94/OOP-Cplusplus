#pragma once

#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>

/*
* Data type that represents a template of min-heap implementation of Skew heap data stucture.
*/
template<typename T>
class SkewHeap
{
public:
	SkewHeap()
	{
		root = NULL;
	}

	~SkewHeap()
	{
		freeNode(root);
	}

	/*
	* Method that adds a node with data provided by @value in the current skew heap.
	*
	* @param value: value to be added in the heap
	*/
	void add(const T& value)
	{
		this->root = merge(this->root, new Node(value));
	}

	/*
	* This method removes and returns the smallest element in the current skew heap.
	*
	* @returns the removed element or throws exception if there are no any elements in the heap
	*/
	T removeMin()
	{
		if (empty())
			throw "Can`t get min element of empty tree!";

		// Save the min node and min node value.
		T val = root->value;
		Node * min = root;

		// Merge the two childrens.
		root = merge(root->left, root->right);

		delete min;

		return val;
	}

	/*
	* Tests whether there are any elements in the current heap.
	*
	* @returns true, if there are no any elements and false, otherwise
	*/
	bool empty() const
	{
		return root == NULL;
	}

	/*
	* Method that merges the current skew heap with the given by @other.
	* This method destructs the @other skew heap while merging it.
	*
	* @param other: reference to the skew heap data structure that will be merged with the current one
	*/
	void merge(SkewHeap<T>& other)
	{
		this->root = merge(this->root, other.root);
		other.root = NULL;
	}

	/*
	* Prints the values in the nodes to the std::cout.
	*/
	void printInOrder() const
	{
		printInOrder(root);
		std::cout << "Check values ? " << checkBST(root) << std::endl;
		std::cout << std::endl;
	}
private:
	/*
	* Data type that represents a node in the Skew heap
	*/
	class Node
	{
	public:
		Node(const T& value)
		{
			this->value = value;
			left = right = NULL;
		}

		~Node()
		{
			// Implement me...
		}

		T value; // data value
		Node* left; // left subtree
		Node* right; // right subtree
	};

	/*
	* Method that merges two skew heap data structures pointed to their roots by @root1 and @root2
	*
	* @param root1: pointer to the root of the first skew heap
	* @param root2: pointer to the root of the second skew heap
	*
	* @returns a pointer to the root of the merged data structure
	*/
	Node* merge(Node* root1, Node* root2)
	{
		// Iterators on the two heaps.
		Node * r1 = root1;
		Node * r2 = root2;

		Node * r3 = getMin(r1, r2);
		Node * resultTreeRoot = r3;

		while (r1 && r2)
		{
			r3->right = getMin(r1, r2);

			r3 = r3->right;
		}

		if (r1)
			r3->right = r1;
		else if (r2)
			r3->right = r2;

		// Now make the swapping, left and right child
		swapChildrens(resultTreeRoot);

		return resultTreeRoot;
	}

	/*
	* Goes through every right node to the end and after that swaps the childs (without the last node)
	*/
	void swapChildrens(Node * root)
	{
		if (!root)
			return;
		// Skip the last one.
		if (!root->right)
			return;

		swapChildrens(root->right);
		std::swap(root->left, root->right);
	}

	/*
	* Returns the min root of the given two, moves the @r1 or @r2 to their right child...
	*/
	Node * getMin(Node *& r1, Node*& r2)
	{
		if (!r1 && !r2)
			return NULL;

		Node * resultRoot = NULL;

		if (!r1)
		{
			resultRoot = r2;
			r2 = r2->right;
		}
		else if (!r2)
		{
			resultRoot = r1;
			r1 = r1->right;
		}
		else if (r1->value <= r2->value)
		{
			resultRoot = r1;
			r1 = r1->right;
		}
		else
		{
			resultRoot = r2;
			r2 = r2->right;
		}

		return resultRoot;
	}

	/*
	* Prints the values and the childs in every node, in order.
	*/
	void printInOrder(Node * root) const
	{
		if (!root)
			return;

		printInOrder(root->left);

		std::cout << root->value
			<< " and left child: " << ((root->left) ? root->left->value : -1)
			<< " and right child: " << ((root->right) ? root->right->value : -1) << std::endl;
		// std::cout << root->value << " ";

		printInOrder(root->right);
	}

	/*
	* Deletes the nodes in the left and right child of the given one and after that deletes it.
	*/
	void freeNode(Node * root)
	{
		if (!root)
			return;

		freeNode(root->left);
		freeNode(root->right);

		delete root;
	}

	/*
	* Checks if every node value is smaller than the values in it`s childs
	*/
	bool checkBST(Node * root) const
	{
		if (!root)
			return true;

		if ((root->left && root->left->value < root->value) || (root->right && root->right->value < root->value))
			return false;

		return checkBST(root->left) && checkBST(root->right);
	}

private:
	/*
	* Pointer to the root for the current skew heap
	*/
	Node* root;
};