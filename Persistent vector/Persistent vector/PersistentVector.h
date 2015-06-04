#pragma once

/*
	* Anton Vasilev Dudov
	* #71488
	* Github repository: 
	*
	*
	*
	*
	*
*/

#include <type_traits>
#include <vector>

// 32 childs per root for the tree.
#define B 32

using std::vector;

template<typename T>
class PersistentVector {
	static_assert(std::is_scalar<T>::value,
		"PersistentVector can only be used with primitive types. Instantiate with a pointer type for"
		"something more complicated.");
private:

	/*
		Nodes.
		I use the default copy constructor and assignment operator.
	*/

	// Basic abstract class.
	struct Node
	{
		virtual ~Node() {}; // future stuff for deletion, maybe.
	};

	// Internal node.
	struct NodeInternal : public Node
	{
		vector<Node*> childs;

		NodeInternal()
		{
			// Allocate the memory for the node childs. Set all pointers to NULL.
			childs.resize(B, NULL);
		}

		virtual ~NodeInternal() {}; // future stuff for deletion, maybe.
	};

	// Leaf node.
	struct NodeLeaf : public Node
	{
		vector<T> values;

		NodeLeaf()
		{
			values.resize(B); // The default values doesn`t matter so much...
		}

		virtual ~NodeLeaf() {}; // future stuff for deletion, maybe.
	};


	/*
		The Vector impelementation.
	*/

private:
	Node * root;
	int count;
public:
	PersistentVector()
	{
		root = new NodeInternal();
		count = 0;
	}

	// Returns the value of the element at position *index*.
	T operator[](int index) const;

	// Returns a new vector with the element at position *index* replaced by *value*.
	PersistentVector update(int index, T value) const;

	// Returns a new vector with *value* appended at the end.
	PersistentVector append(T value) const;

	// Returns a new vector that's the same as this one but without the last element.
	PersistentVector pop() const;

	int size() const
	{
		return count;
	}
};