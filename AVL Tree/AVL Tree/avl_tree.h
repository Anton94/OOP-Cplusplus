#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP


/*
	Github repository: https://github.com/Anton94/OOP-Cplusplus

	AVL tree project: https://github.com/Anton94/OOP-Cplusplus/tree/master/AVL%20Tree
	
	I can insert the elements which already exist , but in some queue, and the deadline is basicaly now, so ...
*/

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
	
	/* Prints the tree values...	
	*/
	void printInOrder() const;
	bool checkBST() const;
private:
	void insertNode(Node<T> *& root, T value);
	Node<T>* findNode(Node<T> * root, T value);
	void freeNode(Node<T> * root);
	void createNodeAndItsData(Node<T> *& child, Node<T> * parent, const T& value);
	void recheckToTheRoot(Node<T> *& root);
	int getMaxHeightOfTwoNodes(Node<T> * left, Node<T> * right) const;
	void printInOrder(Node<T>* root) const;
	bool checkBST(Node<T>* root) const;
	void rotationRight(Node<T> *& root);
	void rotationLeft(Node<T> *& root);
	void fixHeightsToTheRoot(Node<T> * root);
	void fixHeightsOfNode(Node<T> * root);
	int getHeightOfSubtree(Node<T>* root) const;
	Node<T> * minInRightSubtree(Node<T> *& root);
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
int AVLTree<T>::getHeightOfSubtree(Node<T>* root) const
{
	if (!root)
		return 0;

	return root->height;
}

template <class T>
void AVLTree<T>::insertNode(T value)
{
	insertNode(root, value);
}


template <class T>
void AVLTree<T>::insertNode(Node<T> *& root, T value)
{
	if (!root) // only one element in the tree...
	{
		createNodeAndItsData(root, NULL, value);
	}
	else if (value <= root->value)
	{
		if (!root->leftChild) // if the element has to go to left root as a leaf
		{
			createNodeAndItsData(root->leftChild, root, value);
			fixHeightsToTheRoot(root->leftChild); // it can start with the root even...
			recheckToTheRoot(root->leftChild);
		}
		else
		{
			insertNode(root->leftChild, value);
		}
	}
	else if (value > root->value)
	{
		if (!root->rightChild)
		{
			createNodeAndItsData(root->rightChild, root, value);
			fixHeightsToTheRoot(root->rightChild);
			recheckToTheRoot(root->rightChild);			
		}
		else
		{
			insertNode(root->rightChild, value);
		}
	}
}

/// Starts with the given 'root' (leaf) and goes through the path nodes from the leaf to the root and fixes the heights.

template <class T>
void AVLTree<T>::fixHeightsToTheRoot(Node<T> * root)
{
	if (!root)
		return;

	root->height = getMaxHeightOfTwoNodes(root->leftChild, root->rightChild) + 1;

	fixHeightsToTheRoot(root->parent);
}

/// Starts with the given 'root' (leaf) and goes through the path nodes from the leaf to the root and checks for the heights, if there is somehting wrong, makes the needed rotations.

template <class T>
void AVLTree<T>::recheckToTheRoot(Node<T> *& root)
{
	if (!root || !root->parent || !root->parent->parent)
		return;

	// The checks are for the following 4 cases (the new leaf is in): root.left.left, root.left.right, root.right.right, root.right.left. So if the root or root->parent or root->parent->parent are NULL, there is nothing for check...
	
	Node<T> * grP = root->parent->parent; // Just not to write root->parent->parent ...

	// Get the real pointer to the grandparent.
	//if (!grandParent->parent) // In that case there grandparent is the real root
	//	this->root;
	//else if (grandParent->parent->leftChild == grandParent)
	//	grandParent->parent->leftChild;
	//else // if (grandParent->parent->rightChild == grandParent)
	//	grandParent->parent->rightChild;	

	Node<T> *& grandParent = (!grP->parent ? this->root : (grP->parent->leftChild == grP ? grP->parent->leftChild : grP->parent->rightChild));

	// If the heights are fucked up.
	if (std::abs(getHeightOfSubtree(grandParent->leftChild) - getHeightOfSubtree(grandParent->rightChild)) > 1)
	{
		// Check for the four cases(above ones)...

		if (grandParent->leftChild && grandParent->leftChild->leftChild == root)
		{
			// Make right rotation on the grand parent.
			rotationRight(grandParent);
		}
		else if (grandParent->leftChild && grandParent->leftChild->rightChild == root)
		{
			// Make left rotation on the parent and right rotation on the grand parent.

			// We know that the parent is the left child of the grand parent.
			rotationLeft(grandParent->leftChild);
			rotationRight(grandParent);
		}
		// The other two cases are symetrical.
		else if (grandParent->rightChild && grandParent->rightChild->rightChild == root)
		{
			// Make left rotation on the grandparent.
			rotationLeft(grandParent);
		}
		else if (grandParent->rightChild && grandParent->rightChild->leftChild == root)
		{
			// Make right rotation on the parent and lefr rotation on the grand parent.

			// We know that the parent is the right child of the grand parent.
			rotationRight(grandParent->rightChild);
			rotationLeft(grandParent);	
		}

		fixHeightsToTheRoot(grandParent);
		recheckToTheRoot(grandParent);
	}
	else // the situation here is good and check upper nodes...
	{
		recheckToTheRoot(root->parent);
	}	
}

/// Gets the biggest heigh of it`s subtrees and adds 1.

template <class T>
void AVLTree<T>::fixHeightsOfNode(Node<T> * root)
{
	if (!root)
		return;

	root->height = getMaxHeightOfTwoNodes(root->leftChild, root->rightChild) + 1;
}

/// Right rotation

template <class T>
void AVLTree<T>::rotationRight(Node<T> *& root) 
{
	// If there is no root or no left subtree.
	if (!root || !root->leftChild)
		return;

	// Parents.
	root->leftChild->parent = root->parent;
	root->parent = root->leftChild;
	if (root->leftChild->rightChild)
		root->leftChild->rightChild->parent = root;

	Node<T> * n = root;

	root = root->leftChild;

	n->leftChild = root->rightChild;

	root->rightChild = n;

	// Heights. Maybe the left child height has no need to be recalc...
	fixHeightsOfNode(root->leftChild);
	fixHeightsOfNode(root->rightChild);
	fixHeightsOfNode(root);
}

/// Left rotation.

template <class T>
void AVLTree<T>::rotationLeft(Node<T> *& root)
{
	// If there is no root or no right subtree.
	if (!root || !root->rightChild)
		return;

	// Parents.
	root->rightChild->parent = root->parent;
	root->parent = root->rightChild;
	if (root->rightChild->leftChild)
		root->rightChild->leftChild->parent = root;

	Node<T> * n = root;

	root = root->rightChild;

	n->rightChild = root->leftChild;

	root->leftChild = n;

	// Heights. Maybe the right child height has no need to be recalc...
	fixHeightsOfNode(root->leftChild);
	fixHeightsOfNode(root->rightChild);
	fixHeightsOfNode(root);
}

/// It would be nice this function to be a constructor of the Node class...
/// Sets the data for the node, and increments the size of the tree...

template <class T>
void AVLTree<T>::createNodeAndItsData(Node<T> *& child, Node<T> * parent, const T& value)
{
	child = new Node<T>();
	child->height = 1;
	child->leftChild = child->rightChild = NULL;
	child->parent = parent;
	child->value = value;
	++size;
}

/// Returns the biggest height of two subtrees.

template <class T>
int AVLTree<T>::getMaxHeightOfTwoNodes(Node<T> * left, Node<T> * right) const
{
	if (!left && !right)
		return 0;

	if (!left)
		return right->height;
	if (!right)
		return left->height;

	return std::max(left->height, right->height);
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
	else if (value < root->value)
		return findNode(root->leftChild, value);
	else 
		return findNode(root->rightChild, value);
}

template <class T>
void AVLTree<T>::deleteNode(T value)
{
	Node<T> * node = findNode(value);
	if (!node)
		return;

	// Get the real pointer to the node, needed to be removed... (similar to the real pointer in the recheck function)
	Node<T> *& pNode = (!node->parent ? this->root : (node->parent->leftChild == node ? node->parent->leftChild : node->parent->rightChild));

	// Keep the node to remove...
	Node<T> * toDel = node;

	if (!pNode->leftChild && !pNode->rightChild) // Its a leaf...
	{
		pNode = NULL;
	}
	else if (!pNode->leftChild) // If it has no left subtree
	{
		pNode->rightChild->parent = pNode->parent; // Sets the new parent of the right child
		pNode = pNode->rightChild;
	}
	else if (!pNode->rightChild) // If it has no right subtree
	{
		pNode->leftChild->parent = pNode->parent; // Sets the new parent of the left child
		pNode = pNode->leftChild;
	}
	else
	{
		Node<T> * min = minInRightSubtree(pNode->rightChild);
		pNode->value = min->value;
		toDel = min;
	}

	Node<T> * parentOfToDelNode = toDel->parent;
	delete toDel;
	recheckToTheRoot(pNode);

	--size;
}

/// Returns a pointer to the min element in right subtree.

template <class T>
Node<T> * AVLTree<T>::minInRightSubtree(Node<T> *& root)
{
	if (!root)
		return NULL;

	if (!root->leftChild) // The current node is the min one, because it has no left subtrees.
	{
		Node<T> * min = root;
		root = root->rightChild;
		if (root)
			root->parent = min->parent;
		return min;
	}

	return minInRightSubtree(root->leftChild);
}

/// Frees the left and right AVL subtrees nodes and then delets the root node.

template <class T>
void AVLTree<T>::freeNode(Node<T> * root)
{
	if (!root)
		return;

	freeNode(root->leftChild);
	freeNode(root->rightChild);

	delete root;
}

/// Prints the tree 'in order'.

template <class T>
void AVLTree<T>::printInOrder() const
{
	printInOrder(root);
	std::cout << std::endl;
}

template <class T>
void AVLTree<T>::printInOrder(Node<T> * root) const
{
	if (!root)
		return;

	printInOrder(root->leftChild);

	/*std::cout << root->value << " with height: " << root->height
	<< " and left child: " << ((root->leftChild) ? root->leftChild->value : -1)
	<< " and right child: " << ((root->rightChild) ? root->rightChild->value : -1) << std::endl;*/
	std::cout << root->value << " ";
	printInOrder(root->rightChild);
}

/// Checks for the BST rule...

template <class T>
bool AVLTree<T>::checkBST() const
{
	return checkBST(root);
}

template <class T>
bool AVLTree<T>::checkBST(Node<T> * root) const
{
	if (!root)
		return true;

	if ((root->leftChild && root->leftChild->value > root->value) || (root->rightChild && root->rightChild->value <= root->value))
		return false;

	return checkBST(root->leftChild) && checkBST(root->rightChild);
}

#endif // AVL_TREE_HPP