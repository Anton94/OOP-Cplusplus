#ifndef TEST_AVL_TREE_HPP
#define TEST_AVL_TREE_HPP
#include "avl_tree.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <set>
#include <ctime>
#include <cstdarg>

using namespace std;
//#define MEASURE_TIME

inline double get_time(){    
#ifndef WIN32
 timeval tv;
 gettimeofday(&tv, 0);
 return tv.tv_sec + tv.tv_usec/1000000.0 ;
#else
 return ((double)clock() / CLOCKS_PER_SEC);
#endif
};

void print(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}


template <class T>
class TestAVLTree : public AVLTree<T>
{
#ifdef MEASURE_TIME
private:
	double avlPropertyTime, nodesLinksTime, hightsCorrectnessTime, correctValuesTime;
public:
	TestAVLTree();
	void printTimes() const;
#endif
private:
	int getHeight(Node<T> *node);
	bool isAVLPropertyHeld();
	bool isAVLPropertyHeldRec(Node<T> *node);
	int visitedNodes;
	bool areAllNodesLinkedCorrectly();
	bool areAllNodesLinkedCorrectlyRec(Node<T> *parent, Node<T> *node);
	bool areAllHeightsAccurate();
	bool areAllHeightsAccurateRec(Node<T> * node);
	int calculateNodeHeight(Node<T> * node);
	bool hasTreeCorrectValues(const multiset<T>& values);
	void getValuesRec(Node<T> *node, multiset<T>& values);
public:
	bool checkTree(const multiset<T>& values);
};

#ifdef MEASURE_TIME
template <class T>
TestAVLTree<T>::TestAVLTree()
{
	avlPropertyTime = nodesLinksTime = hightsCorrectnessTime = correctValuesTime = 0;
}

template <class T>
void TestAVLTree<T>::printTimes() const
{
	print("\nTime taken in avl property check: %0.5\n", avlPropertyTime);
	print("Time taken in node links check:  %0.5\n", nodesLinksTime);
	print("Time taken in hights correctness check:  %0.5\n", hightsCorrectnessTime);
	print("Time taken in correct values check:  %0.5\n", correctValuesTime);
}
#endif

/// assertion methods

template <class T>
bool TestAVLTree<T>::isAVLPropertyHeld()
{
	return isAVLPropertyHeldRec(root);
}

template <class T>
bool TestAVLTree<T>::isAVLPropertyHeldRec(Node<T> *node)
{
	if (node == NULL) return true;
	if (abs(getHeight(node->leftChild) - getHeight(node->rightChild)) > 1)
	{
		print("\nA node has its children with height of difference more than one\n");
		return false;
	}
	if (node->leftChild != NULL && node->leftChild->value > node->value)
	{
		print("\nA node has smaller value than its left child\n");
		return false;
	}
	if (node->rightChild != NULL && node->rightChild->value < node->value)
	{
		print("\nA node has greater value than its right child");
		return false;
	}
	return isAVLPropertyHeldRec(node->leftChild) && isAVLPropertyHeldRec(node->rightChild);
}

template <class T>
bool TestAVLTree<T>::areAllNodesLinkedCorrectly()
{
	visitedNodes = 0;
	if (!areAllNodesLinkedCorrectlyRec(NULL, root)) return false;

	if (visitedNodes != size)
	{
		print("\nThe number of linked nodes does not correspond the tree size\n");
		return false;
	}
	return true;
}

template <class T>
bool TestAVLTree<T>::areAllNodesLinkedCorrectlyRec(Node<T> *parent, Node<T> *node)
{
	if (node == NULL) return true;
	visitedNodes++;
	if (node->parent != parent)
	{
		print("\nA node has inaccurate parent\n");
		return false;
	}
	if (!areAllNodesLinkedCorrectlyRec(node, node->leftChild))
	{
		return false;
	}
	return areAllNodesLinkedCorrectlyRec(node, node->rightChild);
}

template <class T>
bool TestAVLTree<T>::areAllHeightsAccurate()
{
	return areAllHeightsAccurateRec(root);
}

template <class T>
bool TestAVLTree<T>::areAllHeightsAccurateRec(Node<T> * node)
{
	if (node == NULL) return true;
	if (1 + max(getHeight(node->rightChild), getHeight(node->leftChild))  != node->height)
	{
		print("\nFound node with inaccurate height property\n");
		return false;
	}
	return areAllHeightsAccurateRec(node->leftChild) && areAllHeightsAccurateRec(node->rightChild);
}

template <class T>
bool TestAVLTree<T>::hasTreeCorrectValues(const multiset<T>& values)
{
	multiset<T> treeValues;
	getValuesRec(root, treeValues);
	if (values.size() != treeValues.size())
	{
		print("\nThe values in the tree are not as expected in number\n");
		return false;
	}
	for (multiset<T>::iterator itr1 = values.begin(), itr2 = treeValues.begin(); itr1 != values.end() || itr2 != treeValues.end(); ++itr1, ++itr2)
	{
		if (*itr1 != *itr2)
		{
			print("\nThe vlaues in the tree are not as expected\n");
			return false; 
		}
	}
	return true;
}

template <class T>
void TestAVLTree<T>::getValuesRec(Node<T> *node, multiset<T>& values)
{

	if (node != NULL)
	{
		values.insert(node->value);
		getValuesRec(node->leftChild, values);
		getValuesRec(node->rightChild, values);
	}
}

template <class T>
int TestAVLTree<T>::getHeight(Node<T> *node)
{
	if (node == NULL)
	{
		return 0;
	} else {
		return node->height;
	}
}

template <class T>
bool TestAVLTree<T>::checkTree(const multiset<T>& values)
{
	if (values.size() != size)
	{
		print("\nThe size of the tree is not as expected\n");
		return false;
	}
	bool treeCorrect = true;

#ifdef MEASURE_TIME
	double begin, end;	
	begin = get_time();
#endif

	treeCorrect = isAVLPropertyHeld();

#ifdef MEASURE_TIME
	end = get_time();
	avlPropertyTime += end - begin;
	begin = end;
#endif

	if (!treeCorrect) return false;
	treeCorrect = areAllNodesLinkedCorrectly();

#ifdef MEASURE_TIME
	end = get_time();
	nodesLinksTime += end - begin;
	begin = end;
#endif

	if (!treeCorrect) return false;
	treeCorrect = areAllHeightsAccurate();

#ifdef MEASURE_TIME
	end = get_time();
	hightsCorrectnessTime += end - begin;
	begin = end;
#endif

	if (!treeCorrect) return false;
	treeCorrect = hasTreeCorrectValues(values);

#ifdef MEASURE_TIME
	end = get_time();
	correctValuesTime += end - begin;
#endif

	if (!treeCorrect) return false;
	return true;
}

#endif //TEST_AVL_TREE_HPP