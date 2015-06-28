#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <iostream>
#include <algorithm>    // merge

template<class T>
struct Node
{
	Node *right;
	Node *parent;
	Node *leftmostChild;
	T key;
};

template<class T>
class BinomialHeap
{
private:
	// The root of the heap. Should be kept NULL all the time the heap is empty
	Node<T> *root;
	// The number of elements currently stored in the heap.
	int size;

protected:
	/**
	* Auxiliary function to be used when uniting two heaps.
	*
	* This function should merge the two given root lists in the root list of a
	* single binomial heap - the result of the merging.
	*
	* This method is virtual for ease of testing. Still you need to implement it.
	*
	* |NOTE| This method could have been static as long as it will not access any
	* |NOTE| of the fields of the class. Still it is not static, because in some
	* |NOTE| of the tests it will be overridden.
	*
	* @param leftRoot - the first node of the root list of the first heap
	* @param leftSize - the number of the elements in the left heap
	* @param rightRoot - the first node of the root list of the second heap
	* @param rightSize - the number of the elements in the right heap
	* @return the first node of the root list of the binomial heap result of
	*		the merging of the two given heaps
	*/
	virtual Node<T>* consolidate(Node<T>* leftRoot, int leftSize,
		Node<T>* rightRoot, int rightSize);
public:
	/**
	* Construct empty binomial heap
	*/
	BinomialHeap();

	/**
	* Construct heap with the given elements.
	* Expected runneing time O(elementsSize)
	* @param elements - array containing the elements
	* @param elementsSize - the number of elements in the array
	*/
	BinomialHeap(T elements[], int elementsSize);

	/**
	* @return - the key of the minimal element currently stored in the heap
	*/
	T getMin() const;

	/**
	* @return - the root of the heap. Will be used for testing purposes.
	*/
	Node<T>* getRoot() const;

	/**
	* @return - the number of the elements currently stored in the heap.
	*/
	int getSize() const;

	/**
	* Extracts (removes) the element with minimal key from the heap
	* @return - the key of the minimal element currently stored in the heap
	*/
	T extractMin();

	/**
	* Unites the current heap with the one given.
	* It is expected that the structure of otherHeap will be destroyed in this method.
	*
	* @param otherHeap - the heap with which we will unite. It will be destroyed in this method
	*/
	void unite(BinomialHeap<T>& otherHeap);

	/**
	* Inserts element with the new given key in the heap.
	* @param newKey - the key of the element to be inserted
	* @return a pointer to the newly created element in the heap
	*/
	Node<T>* push(const T& newKey);

	/**
	* Decreases the key of the given element to the given amount.
	* It is guaranteed the ptr is real pointer to element of the heap.
	* WARNING!!!
	*       No changes should be made if the newly given key is larger than
	*       the current value of the key.
	* WARNING!!!
	*
	* @param ptr - a pointer to the element which key is to be modified
	* @param newKey - the new value of the key to be used for element pointed by ptr
	*/
	void decreaseKey(Node<T>* ptr, const T& newKey);
};


///
/// Definitions.
///

/**
* Sets the default pointer values
* @param node - the node, which pointers will be NULL.
*/

template<class T>
void setNodeDefaults(Node<T> * node)
{
	node->right = NULL;
	node->parent = NULL;
	node->leftmostChild = NULL;
}


/**
* Construct empty binomial heap
*/
template<class T>
BinomialHeap<T>::BinomialHeap()
{
	root = NULL;
	size = 0;
}


///
/// MERGE FUNCTIONS...
///


/**
* Auxiliary function to be used when uniting two heaps.
*
* This function should merge the two given root lists in the root list of a
* single binomial heap - the result of the merging.
*
* This method is virtual for ease of testing. Still you need to implement it.
*
* |NOTE| This method could have been static as long as it will not access any
* |NOTE| of the fields of the class. Still it is not static, because in some
* |NOTE| of the tests it will be overridden.
*
* @param leftRoot - the first node of the root list of the first heap
* @param leftSize - the number of the elements in the left heap
* @param rightRoot - the first node of the root list of the second heap
* @param rightSize - the number of the elements in the right heap
* @return the first node of the root list of the binomial heap result of
*		the merging of the two given heaps
*/
template<class T>
Node<T>* BinomialHeap<T>::consolidate(Node<T>* leftRoot, int leftSize, Node<T>* rightRoot, int rightSize)
{
	int * mergedDegrees = NULL;
	Node<T> * newRoot = merge(leftRoot, leftSize, rightRoot, rightSize, mergedDegrees);
	size_t mergedDegreesCounter = 0;
	size_t mergedDegreesNextCounter = 1;

	leftRoot = NULL;
	rightRoot = NULL;

	// If the lists of roots are empty..
	if (!newRoot) 
		return NULL;

	Node<T> * prev = NULL;
	Node<T> * current = newRoot;
	Node<T> * next = newRoot->right;

	while (next) 
	{
		if (mergedDegrees[mergedDegreesCounter] != mergedDegrees[mergedDegreesNextCounter] ||
			(next->right != NULL && mergedDegrees[mergedDegreesNextCounter + 1] == mergedDegrees[mergedDegreesCounter]))
		{
			prev = current;
			current = next;
			++mergedDegreesCounter;
			++mergedDegreesNextCounter;
		}
		else 
		{
			if (current->key <= next->key) 
			{
				current->right = next->right;
				uniteTwoOfSameDegree(next, current);
				mergedDegrees[mergedDegreesCounter]++;

				++mergedDegreesNextCounter;
			}
			else 
			{
				if (prev == NULL) 
					newRoot = next;
				else 
					prev->right = next;

				uniteTwoOfSameDegree(current, next);
				mergedDegrees[mergedDegreesNextCounter]++;
				current = next;

				mergedDegreesCounter = mergedDegreesNextCounter;
				++mergedDegreesNextCounter;
			}
		}

		next = current->right;
	}

	delete[] mergedDegrees;

	return newRoot;
}

/**
* Creates a array with the degrees of the root list binomial trees. 
* For example if the size is 13, the binary number will be 1101 and the array will contains [0, 2, 3], because the binomial trees are in increasing order in the root list.
* @param size - the number of the elements in the left heap
* @return - a pointer to that array.
* NOTE: has to delete the memory for the array
*/

int * allocateDegreeArray(int size)
{
	size_t numberOfBits = sizeof(size) * 8;
	int * degreeArray = new int[numberOfBits]; // Binary number, place for every digit to save the degrees.
	for (size_t i = 0; i < numberOfBits; ++i) // Lets set default big values(not valid once).
	{
		degreeArray[i] = numberOfBits + 1;
	}

	size_t degreeArrayCounter = 0;

	int mask = 1;

	for (size_t i = 0; i < numberOfBits; ++i)
	{
		if (size & mask != 0) // if the bit in the number is 1
		{
			degreeArray[degreeArrayCounter++] = i;
		}

		size = size >> 1;
	}

	return degreeArray;
}

/**
* Merges two arrays with degrees values in increasing order.
* @param left - pointer to the left array
* @param right - pointer to the right array
* @return a pointer to that array.
*/

int * mergeTwoDegreesArray(int * left, int * right, size_t numberOfBits)
{
	int * degreeArray = new int[numberOfBits * 2]; // Binary number, place for every digit to save the degrees.

	std::merge(left, left + numberOfBits, right, right + numberOfBits, degreeArray);

	return degreeArray;
}


/**
* Unites two binomial trees (@y and @z) from the same degree in one.
* @z will be the root of the combined binomial tree.
* @param y - first binomial tree root
* @param z - second binomial tree root
*/
template <class T>
void uniteTwoOfSameDegree(Node<T>* y, Node<T>* z)
{
	y->parent = z;
	y->right = z->leftmostChild;
	z->leftmostChild = y;
}


/**
* Merges the root list of the given two binomial heaps(given roots).
* @param leftRoot - the first node of the root list of the first heap
* @param leftSize - the number of the elements in the left heap
* @param rightRoot - the first node of the root list of the second heap
* @param rightSize - the number of the elements in the right heap
* @param mergedArray - the pointer to the merged degree array
* @return the root of the merged list.
*/
template <class T>
Node<T> * merge(Node<T>* leftRoot, int leftSize, Node<T>* rightRoot, int rightSize, int *& mergedDegreeArray) // I assume that the sizes are correct...
{
	if (leftRoot == NULL)
		return rightRoot;
	if (rightRoot == NULL)
		return leftRoot;

	Node<T> * newRoot;
	int * leftDegrees = allocateDegreeArray(leftSize);
	int leftDegreesCounter = 0;
	int * rightDegrees = allocateDegreeArray(rightSize);
	int rightDegreesCounter = 0;

	if (leftDegrees[0] <= rightDegrees[0])
	{
		newRoot = leftRoot;
		leftRoot = leftRoot->right;
		++leftDegreesCounter;
	}
	else
	{
		newRoot = rightRoot;
		rightRoot = rightRoot->right;
		++rightDegreesCounter;
	}

	Node<T> * temp = newRoot;

	while (leftRoot && rightRoot)
	{
		if (leftDegrees[leftDegreesCounter] <= rightDegrees[rightDegreesCounter])
		{
			temp->right = leftRoot;
			leftRoot = leftRoot->right;
			++leftDegreesCounter;
		}
		else
		{
			temp->right = rightRoot;
			rightRoot = rightRoot->right;
			++rightDegreesCounter;
		}

		temp = temp->right;
	}

	if (leftRoot)
		temp->right = leftRoot;
	else
		temp->right = rightRoot;

	mergedDegreeArray = mergeTwoDegreesArray(leftDegrees, rightDegrees, sizeof(leftSize) * 8); // all of the sizes must be one type...

	delete[] leftDegrees;
	delete[] rightDegrees;

	return newRoot;
}

///
/// END OF MERGING...
///


/**
* @return - the key of the minimal element currently stored in the heap
*/
template <class T>
T BinomialHeap<T>::getMin() const
{
	if (!root) 
		throw "No elements in the binomial heap and called getMin!";

	Node<T>* min = root;
	Node<T>* next = root->right;

	while (next) 
	{
		if (min->key > next->key) 
		{
			min = next;
		}

		next = next->right;
	}

	return min->key;
}

/**
* @return - the root of the heap. Will be used for testing purposes.
*/
template<class T>
Node<T>* BinomialHeap<T>::getRoot() const
{
	return root;
}

/**
* @return - the number of the elements currently stored in the heap.
*/
template<class T>
int BinomialHeap<T>::getSize() const
{
	return size;
}

/**
* Inserts element with the new given key in the heap.
* @param newKey - the key of the element to be inserted
* @return a pointer to the newly created element in the heap
*/
template<class T>
Node<T>* BinomialHeap<T>::push(const T& newKey)
{
	Node<T> * n = new Node<T>();
	setNodeDefaults(n);
	n->key = newKey;

	root = consolidate(root, size, n, 1);
	++size;

	return n;
}

/**
* Unites the current heap with the one given.
* It is expected that the structure of otherHeap will be destroyed in this method.
*
* @param otherHeap - the heap with which we will unite. It will be destroyed in this method
*/
template <class T>
void unite(BinomialHeap<T>& otherHeap)
{
	root = consolidate(root, size, otherHeap.root, otherHeap.size);
	size += otherHeap.size;

	otherHeap.root = NULL;
	otherHeap.size = 0;
}

/**
* Decreases the key of the given element to the given amount.
* It is guaranteed the ptr is real pointer to element of the heap.
* WARNING!!!
*       No changes should be made if the newly given key is larger than
*       the current value of the key.
* WARNING!!!
*
* @param ptr - a pointer to the element which key is to be modified
* @param newKey - the new value of the key to be used for element pointed by ptr
*/
template <class T>
void BinomialHeap<T>::decreaseKey(Node<T>* ptr, const T& newKey)
{

}


#endif //BINOMIAL_HEAP_HPP