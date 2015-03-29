#ifndef AVL_TREE_INTERFACE
#define AVL_TREE_INTERFACE

#include <string>
std::string getName();
std::string getMoodleName();
std::string getFacultyNumber();

template <class T>
class Node
{
public:
	Node<T> *parent;
	Node<T> *leftChild, *rightChild;
	int height;
	T value;
};

template <class T>
class AVLTreeInterface
{
protected:
	Node<T> *root;
	int size;
public:
	/* Returns the number of nodes in the tree. 0 in case of empty tree. */
	virtual int getSize() const = 0;

	/* Inserts the given value as node in the tree. */
	virtual void insertNode(T value) = 0;

    /* Finds a node with value equal to the given parameter. Returns NULL if no such is found. */
	virtual Node<T>* findNode(T value) = 0;

	/* Deletes a node with the given value from the tree.
	   If the value is not found in the tree no modification to the tree should be made.
	*/
	virtual void deleteNode(T value) = 0;
};

#endif //AVL_TREE_INTERFACE