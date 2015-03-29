#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "avl_tree_interface.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string getName() 
{
	return "Anton Vasilev Dudov";
}

string getMoodleName() 
{
	return "adudov";
}


string getFacultyNumber() 
{
	return "71488";
}

template <class T>
class AVLTree : public  AVLTreeInterface<T>
{
public:
	AVLTree();
	virtual ~AVLTree();

		/* Returns the number of nodes in the tree. 0 in case of empty tree. */
	virtual int getSize() const;

	/* Inserts the given value as node in the tree. */
	virtual void insertNode(T value);

    /* Finds a node with value equal to the given parameter. Returns NULL if no such is found. */
	virtual Node<T>* findNode(T value);

	/* Deletes a node with the given value from the tree.
	   If the value is not found in the tree no modification to the tree should be made.
	*/
	virtual void deleteNode(T value);
private:
	Node<T>* findNode(Node<T> * root, T value);
	void freeNode(Node * root);
};

template <class T>
AVLTree<T>::AVLTree()
{
	root = NULL;
	size = 0;
}

template <class T>
AVLTree<T>::~AVLTree()
{
	freeNode(root);
}

template <class T>
int AVLTree<T>::getSize() const
{
	return size;
}


template <class T>
void AVLTree<T>::insertNode(T value)
{
}

template <class T>
Node<T>* AVLTree<T>::findNode(T value)
{
	return findNode(root, value);
}

template <class T>
Node<T>* AVLTree<T>::findNode(Node<T> * root, T value)
{
	if (!root)
		return NULL;

	if (value == root->value)
		return root;
	else if (root < root->value)
		return findNode(root->leftChild, value);
	else 
		return findNode(root->rightChild, value);
}

template <class T>
void AVLTree<T>::deleteNode(T value)
{
	
}

/// Frees the left and right AVL subtrees nodes and then delets the root node.

template <class T>
void AVLTree<T>::freeNode(Node * root)
{
	if (!root)
		return;

	freeNode(root->leftChild);
	freeNode(root->rightChild);

	delete root;
}

#endif // AVL_TREE_HPP