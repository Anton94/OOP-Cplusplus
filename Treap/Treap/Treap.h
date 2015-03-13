#pragma once

#include <iostream>

class TreapNode
{
public:
	TreapNode(int k)
	{
		key = k;
		priority = (float)(rand()) / RAND_MAX;
		left = NULL;
		right = NULL;
	}
	int key;			// key provided by user
	float priority;		// node's generated priority
	TreapNode* left;	// pointer for the left subtree
	TreapNode* right;	// pointer for the right subtree
};

class Treap
{
public:
	Treap();
	~Treap();

	/**
	* Inserts a node in the treap with the provided @key
	*
	* @param key: key to be inserted
	*/
	void insert(int key);

	/**
	* Removes the node from the treap with the provided @key
	*
	* @param key: key to be removed
	*/
	void remove(int key);

	/**
	* Checks whether a given @key is already in the treap
	*
	* @param key: key to be searched for
	* @return true, if the key is in the treap, and false, otherwise
	*/
	bool containsKey(int key) const;
	
	/**
	* In order printing of the treap. (In the given @out). NOTE: does not returns the ostream...
	*
	* @param out: ostream to be 'printed' the information.
	*/
	void print(std::ostream& out) const;

	
	bool checkPriorities() const;
	bool checkKeys() const;
private:
	/**
	* Inserts a node in the treap with the provided @key . For now there are no option for 2 elements with same key.
	*
	* @param key: key to be inserted
	* @param root: root where to be inserted
	*/
	void insert(int key, TreapNode *& root);
	

	/**
	* Frees the treap by the given root.
	*
	* @param root: the root of the subTreap.
	*/
	void freeSubTree(TreapNode * root);


	/**
	* Removes the node from the treap given as @root . makes it a leaf and deletes it.
	*
	* @param root: the node to delete
	*/
	void Treap::remove(TreapNode*& root);

	/**
	* In order printing of the treap. (In the given @ostream). NOTE: does not returns the ostream...
	*
	* @param out: ostream to be 'printed' the information.
	* @param root: the root of the subTreap.
	*/
	void print(std::ostream& out, TreapNode * root) const;


	/**
	* Searches for the node of given @key and given @root for the subtree, and if there is a node with that @key. If there is no node with that key, throws exeption, use function 'containsKey' to check before using that function.
	*
	* @param key: key to be searched for
	* @return returns THE pointer to it, otherwise returns NULL
	*/
	TreapNode*& searchNodeByKey(TreapNode *& root, int key);


	/**
	* Makes left rotation, the given root is the parent.
	*
	* @param root: the root of the subTreap.
	*/
	void leftRotation(TreapNode*& root);

	/**
	* Makes right rotation, the given root is the parent.
	*
	* @param root: the root of the subTreap.
	*/
	void rightRotation(TreapNode*& root);


	/**
	* Checks whether a given @key is already in the treap
	*
	* @param root: the root of the subtree
	* @param key: key to be searched for
	* @return true, if the key is in the treap, and false, otherwise
	*/
	bool containsKey(TreapNode * root, int key) const;


	bool checkPriorities(TreapNode * root) const;
	bool checkKeys(TreapNode * root) const;
private:
	TreapNode * root;
private:
	Treap& operator=(const Treap&); // Do not implement me!
	Treap(const Treap&); // Do not implement me!
};