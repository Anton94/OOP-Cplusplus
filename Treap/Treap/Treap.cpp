#include "Treap.h"

Treap::Treap()
{
	root = NULL;
}

Treap::~Treap()
{
	freeSubTree(root);
}

/// INSERT.

/**
* Inserts a node in the treap with the provided @key
*
* @param key: key to be inserted
*/
void Treap::insert(int key)
{
	insert(key, root);
}

/**
* Inserts a node in the treap with the provided @key . For now there are no option for 2 elements with same key.
*
* @param key: key to be inserted
* @param root: root where to be inserted
*/
void Treap::insert(int key, TreapNode *& root)
{
	// The treap is empty, and thats the first insertion. No need for for roatation up to the root... (or some kind of magic happaned and the function get NULL pointer for the root..)
	if (!root)
	{
		root = new TreapNode(key);
		return;
	}

	if (key < root->key)
	{
		// If the root has no left child, makes it leaf.
		if (!root->left)
			root->left = new TreapNode(key);
		else
			insert(key, root->left);

		// The rotation needed to fix the heap rules.
		if (root->left->priority < root->priority)
			rightRotation(root);
	}
	else if (key > root->key)
	{
		// If the root has no right child, makes it leaf.
		if (!root->right)
			root->right = new TreapNode(key);
		else
			insert(key, root->right);

		// The rotation needed to fix the heap rules.
		if (root->right->priority < root->priority)
			leftRotation(root);
	}
}

/// REMOVE.

 // TO DO optimisation of the while loop checks...

/**
* Removes the node from the treap with the provided @key
*
* @param key: key to be removed
*/
void Treap::remove(int key)
{
	// If there is no key with the given key value, returns...
	if (!containsKey(key))
		return;

	// References, so I keep the real connection...
	TreapNode *& elementToDelete = searchNodeByKey(root, key);

	// Now rotates the nodes while the needed one is a leaf. (while has left or right child subtree goes..
	while (elementToDelete->left || elementToDelete->right)
	{
		// If there is no right subtree, that means there is only left subtree and makes right rotation.
		if (!elementToDelete->right)
		{
			rightRotation(elementToDelete);
			elementToDelete = elementToDelete->right;
		}
		// If there is no left subtree, that means there is only right subtree and makes left rotation.
		else if (!elementToDelete->left)
		{
			leftRotation(elementToDelete);
			elementToDelete = elementToDelete->left;
		}
		// Last case, we have left and right subtrees.
		else
		{
			if (elementToDelete->left->priority < elementToDelete->right->priority)
			{
				rightRotation(elementToDelete);
				elementToDelete = elementToDelete->right;
			}
			else
			{
				leftRotation(elementToDelete);
				elementToDelete = elementToDelete->left;
			}
		}
	}

	// Now deletes the leaf and makes that pointer (real left/right child subtree pointer of parent node) NULL.
	delete elementToDelete;
	elementToDelete = NULL;
}

/// SEARCH.

/**
* Checks whether a given @key is already in the treap
*
* @param key: key to be searched for
* @return true, if the key is in the treap, and false, otherwise
*/
bool Treap::containsKey(int key) const
{
	return containsKey(root, key);
}

/**
* Checks whether a given @key is already in the treap
*
* @param root: the root of the subtree
* @param key: key to be searched for
* @return true, if the key is in the treap, and false, otherwise
*/
bool Treap::containsKey(TreapNode * root, int key) const
{
	if (!root)
		return false;

	if (key == root->key)
	{
		return true;
	}
	else if (key < root->key)
	{
		return containsKey(root->left, key);
	}
	else // key > root->key
	{
		return containsKey(root->right, key);
	}
}

/**
* Searches for the node of given @key and given @root for the subtree, and if there is a node with that @key. If there is no node with that key, throws exeption, use function 'containsKey' to check before using that function.
*
* @param key: key to be searched for
* @return returns THE pointer to it(the real pointer, not copy, so reference...), otherwise returns NULL
*/
TreapNode*& Treap::searchNodeByKey(TreapNode *& root, int key)
{
	if (!root)
		throw "Can`t find node with the given key!";

	if (key == root->key)
	{
		return root;
	}
	else if (key < root->key)
	{
		return searchNodeByKey(root->left, key);
	}
	else // key > root->key
	{
		return searchNodeByKey(root->right, key);
	}
}

/// PRINT.

/**
* In order printing of the treap. (In the given @ostream). NOTE: does not returns the ostream...
*
* @param out: ostream to be 'printed' the information.
*/
void Treap::print(std::ostream& out) const
{
	print(out, root);
	out << "\n";
}

/**
* In order printing of the treap. (In the given @ostream). NOTE: does not returns the ostream...
*
* @param out: ostream to be 'printed' the information.
* @param root: the root of the subTreap.
*/

void Treap::print(std::ostream& out, TreapNode * root) const
{
	if (!root)
		return;

	print(out, root->left);
	out << "[" << root->key << " " << root->priority << "] ";
	print(out, root->right);
}

/// FREE.

/**
* Frees the treap by the given root.
*
* @param root: the root of the subTreap.
*/
void Treap::freeSubTree(TreapNode * root)
{
	if (!root)
		return;

	// Let`s delete the left and right subtrees, and after that delete the current node.
	freeSubTree(root->left);
	freeSubTree(root->right);
	delete root;
}


/// ROTATIONS.

/**
* Makes left rotation, the given root is the parent.
*
* @param root: the root of the subTreap.
*/
void Treap::leftRotation(TreapNode*& root)
{
	// Check if there is right child, if no - returns.
	if (!root->right)
		return;

	// Keep the original rootNode.
	TreapNode * originalRoot = root;

	// The new rootNode of the treap now is the right child.
	root = root->right;

	// The original rootNode is now left child. (Keeps the left child of the original root)
	TreapNode * newRootLeftChild = root->left;
	root->left = originalRoot;

	// The right child of the original rootNode is the left child of the new rootNode.
	root->left->right = newRootLeftChild;
}

/**
* Makes right rotation, the given root is the parent.
*
* @param root: the root of the subTreap.
*/
void Treap::rightRotation(TreapNode*& root)
{
	// Check if there is left child, if no - returns.
	if (!root->left)
		return;

	// Keep the original rootNode.
	TreapNode * originalRoot = root;

	// The new rootNode of the treap now is the right child.
	root = root->left;

	// The original rootNode is now left child. (Keeps the left child of the original root)
	TreapNode * newRootRightChild = root->right;
	root->right = originalRoot;

	// The right child of the original rootNode is the left child of the new rootNode.
	root->right->left = newRootRightChild;
}



/// TO DO : delete this functions...

bool Treap::checkPriorities() const
{
	return checkPriorities(root);
}

bool Treap::checkPriorities(TreapNode* root) const
{
	if (!root)
		return true;

	if ((root->left && root->left->priority < root->priority) || (root->right && root->right->priority < root->priority))
		return false;

	return checkPriorities(root->left) || checkPriorities(root->right);
}

bool Treap::checkKeys() const
{
	return checkKeys(root);
}

bool Treap::checkKeys(TreapNode* root) const
{
	if (!root)
		return true;

	if ((root->left && root->left->key > root->key) || (root->right && root->right->key < root->key))
		return false;

	return checkKeys(root->left) || checkKeys(root->right);
}