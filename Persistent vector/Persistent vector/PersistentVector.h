

#pragma once

/*
* Anton Vasilev Dudov
* #71488
* Github repository: https://github.com/Anton94/OOP-Cplusplus/tree/master/Persistent%20vector
*
* Optimization maybe I can keep the position of the rightmost taken node in child node vector.
*
* NOTE : The stl vector maybe will not make the size of the vector on the power of 2, so for some compilators or so.... (the leafs may be bigger than 32 elements)
* I can use my vector from the github repository, but I will leave it with the stl one for now.
*
*
*
* I can make some of the functions more compact, but this thing is a little complicate for me, so I do it like that, to see better what is going on.
*/

#include <type_traits>
#include <vector>

// 32 childs per node for the tree.
#define B 32
#define BITS 5
#define MASK (B - 1) 

using std::vector;

template<typename T>
class PersistentVector {
	static_assert(std::is_scalar<T>::value,
		"PersistentVector can only be used with primitive types. Instantiate with a pointer type for"
		"something more complicated.");
private:
	/*
		Nodes.
	*/

	// Basic abstract class.
	struct Node
	{
		virtual ~Node() = 0 {}; // future stuff for deletion, maybe. Pure virtual with a body, because the derive classes will call the base class destructor.
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

		NodeInternal(const vector<Node*>& ch)
		{
			childs = ch;
		}

		virtual ~NodeInternal() {}; // future stuff for deletion, maybe.
	};

	// Leaf node.
	struct NodeLeaf : public Node
	{
		vector<T> values;

		NodeLeaf() {}

		NodeLeaf(const vector<T>& v)
		{
			values = v;
		}

		virtual ~NodeLeaf() {}; // future stuff for deletion, maybe.
	};

	/*
	The Vector impelementation.
	*/
private:
	Node * root;
	int count;
	int level;
public:
	PersistentVector();

	// Returns the value of the element at position *index*.
	T operator[](int index) const;

	// Returns a new vector with the element at position *index* replaced by *value*.
	PersistentVector update(int index, T value) const;

	// Returns a new vector with *value* appended at the end.
	PersistentVector append(T value) const;

	// Returns a new vector that's the same as this one but without the last element.
	PersistentVector pop() const;

	// Returns the number of elements in the vector.
	int size() const;

	// Basic DFS prints only leaf values.
	void print(std::ostream& out) const;
private:
	// Goes down on the tree to the needed element.
	T getAt(Node * root, int level, int index) const;

	// Goes down to the leaf level to get the right element and copy the path to that element.
	void fixLinkesForUpdate(Node *& root, int level, int index, T value) const;

	// The rightmost leaf node is full, copies the path till it founds a full node (internal or leaf) and makes new path to the leaf level (from the level above the full node)
	// and appends the value in the new leaf node.
	void append(int level, Node *& root, const T& value) const;

	// Adds only the value in the new vector. (there is space in the rightmost leaf node)
	void appendRightmostPath(int level, Node *& root, const T& value) const;

	// From the starting level @startLevel to the leaf level. Leaf level is 0.
	// Returns the leaf node.
	NodeLeaf* buildPathToTheLeaf(int level, Node *& root) const;

	//Till fisrt null ptr.
	size_t getSizeOfNotNullPointers(const vector<Node*> & v) const;

	// Checks if there is room in the rightmost leaf node. If so returns true.
	bool checkForRoomInRightmostLeafNode(int level, Node * root) const;

	// Checks if the root node vector of childs/values are all taken.
	bool checkIfRootNodeIsFull(Node * root) const;

	// Removes the last value in the new vector.
	void popRightmostPath(int level, Node *& root) const;

	// Basic DFS prints only leaf values.
	void print(int level, std::ostream& out, Node * root) const;
};


template<typename T>
PersistentVector<T>::PersistentVector()
{
	level = count = 0;
	root = NULL;
}


// Returns the value of the element at position *index*. NOTE: Make check for the index!
template<typename T>
T PersistentVector<T>::operator[](int index) const
{
	if (index < 0 || index >= size())
		throw "Index out of range";

	getAt(root, level, index);
}

// Returns a new vector with the element at position *index* replaced by *value*. MAKE CHECK FOR THE INDEXES
template<typename T>
PersistentVector<T> PersistentVector<T>::update(int index, T value) const
{
	if (index < 0 || index >= size())
		throw "Index out of range";

	PersistentVector<T> newVector(*this);

	fixLinkesForUpdate(newVector.root, newVector.level * 5, index, value);

	return newVector;
}

// Returns a new vector with *value* appended at the end.
	/*
		Basicaly four cases: 
		1) There is no root.
			- I create a leaf node and make the root pointer to this new leaf node. Just push the value.
		2) There is no room in the rightmost leaf node AND there is NO room in the root node.
			- I resize the tree (upwards), make the old tree leftmost child of the new root and append the new value in new rightmost path
		3) There is no room in the rightmost leaf node AND there is room in the root node.
			- Append the new value in new rightmost path.
		4) There is room in the righmost leaf node.
			- Append the value in the rightmost leaf.

		(copy the nodes on the way down)
	*/
template<typename T>
PersistentVector<T> PersistentVector<T>::append(T value) const
{
	// Creates exact copy of the vector.
	PersistentVector<T> newVector(*this);

	// If there is no elements in the tree. (first case)
	if (!newVector.root)
	{
		vector<T> v;
		v.push_back(value);
		newVector.root = new NodeLeaf(v);
	}
	// If there is no room in the rightmost leaf.
	else if (!checkForRoomInRightmostLeafNode(newVector.level, newVector.root))
	{
		// If the whole tree is full. Make new layer and append the old one (second case)
		if (checkIfRootNodeIsFull(newVector.root))
		{
			NodeInternal * newInternalNode = new NodeInternal();
			newInternalNode->childs[0] = newVector.root;
			appendRightmostPath(newVector.level, newInternalNode->childs[1], value);

			newVector.root = newInternalNode;
			++newVector.level;
		}
		// Only the leaf is full. (third case)
		else
		{
			append(newVector.level, newVector.root, value);
		}
	}
	else
		// There is room in the leaf. (fourth case)
	{
		appendRightmostPath(newVector.level, newVector.root, value);
	}

	++newVector.count;

	return newVector;
}

// Returns a new vector that's the same as this one but without the last element.
template<typename T>
PersistentVector<T> PersistentVector<T>::pop() const
{
	if (count <= 0)
		throw "Can`t pop on empty vector!";

	PersistentVector newVector(*this);

	// If there is more than one element in the rightmost leaf node only copy the path and remove the element from the vector.
	//if (moreThanOneElementInRightmostLeafNode(newVector.root))
	{
		popRightmostPath(newVector.level, newVector.root);

	}

	if (level > 0)
	{
		NodeInternal * temp = dynamic_cast<NodeInternal*>(newVector.root); // 100% it will not be NULL
		if (!temp)
			throw "Contact administrator.";

		// If the root node has only one child-> make the root node this child node and decrement the level.
		if (temp->childs[1] == NULL)
		{
			newVector.root = temp->childs[0];
			--newVector.level;
		}
	}

	--newVector.count;

	return newVector;
}

// Returns the number of elements in the vector.
template<typename T>
int PersistentVector<T>::size() const
{
	return count;
}

// Basic DFS prints only leaf values.
template<typename T>
void PersistentVector<T>::print(std::ostream& out) const
{
	print(level, out, root);
	out << "\n";
}

// Goes down on the tree to the needed element.
template<typename T>
T PersistentVector<T>::getAt(Node * root, int level, int index) const
{
	NodeInternal * temp = (NodeInternal*)root;
	
	for (int i = 5 * level; i > 0; i -= 5)
		temp = (NodeInternal*)temp->childs[(index >> i) & MASK];

	return ((NodeLeaf*)temp)->values[index & MASK];
}

// Goes down to the leaf level to get the right element and copy the path to that element.
template<typename T>
void PersistentVector<T>::fixLinkesForUpdate(Node *& root, int level, int index, T value) const
{
	if (level > 0)
	{
		root = new NodeInternal(((NodeInternal*)root)->childs);
		fixLinkesForUpdate(((NodeInternal*)root)->childs[(index >> level) & MASK], level - 5, index, value);
	}
	else
	{
		root = new NodeLeaf(((NodeLeaf*)root)->values);
		((NodeLeaf*)root)->values[index & MASK] = value;
	}
}

// The rightmost leaf node is full, copies the path till it founds a full node (internal or leaf) and makes new path to the leaf level (from the level above the full node)
// and appends the value in the new leaf node.
template<typename T>
void PersistentVector<T>::append(int level, Node *& root, const T& value) const
{
	// There is no way to get in that case if the leaf node is full, but if so(other people use my gorgeous function), returns...
	if (level <= 0)
		return;

	// Copies the internal node.
	root = new NodeInternal(dynamic_cast<NodeInternal*>(root)->childs);

	// Goes to the rightmost path.
	NodeInternal * temp = dynamic_cast<NodeInternal*>(root);

	// I know that the rightmost leaf is full, so I create new one. I use this case because in the other one I cast the child nodes to NodeInternal and so on... I have checked and I know that there is space to add new leaf here.
	if (level == 1)
	{
		for (int i = 0; i < B; ++i)// It can start from 1, because the rightmost path is full but..
		{
			if (temp->childs[i] == NULL)
			{
				NodeLeaf* newLeaf = new NodeLeaf();
				temp->childs[i] = newLeaf;
				newLeaf->values.push_back(value);
				return;
			}
		}
	}

	// If every node is taken and the rightmost child node is full, then the vector is FULL. I can make that check with some range checking for the size...
	for (int i = 1; i < B; ++i)
	{
		if (temp->childs[i] == NULL)
		{
			// if the rightmost child node is full, build new path and append it to the 'i-th' position.
			if (getSizeOfNotNullPointers(((NodeInternal*)(temp->childs[i - 1]))->childs) >= B)// gets the real size of marked nodes.
			{
				buildPathToTheLeaf(level - 1, temp->childs[i])->values.push_back(value); // The function will return a pointer to the leaf node.
			}
			// Otherwise there is place in the rightmost child node, so go down.
			else
			{
				append(level - 1, temp->childs[i - 1], value);
			}

			return;
		}
	}
}

// Adds only the value in the new vector. (there is space in the rightmost leaf node)
template<typename T>
void PersistentVector<T>::appendRightmostPath(int level, Node *& root, const T& value) const
{
	// Not a leaf node.
	if (level > 0)
	{
		// Copies the internal node.
		NodeInternal * temp = dynamic_cast<NodeInternal*>(root);
		NodeInternal * newNodeInternal;

		// If the pointer is null...(from before resizing of the tree.
		if (!temp)
			newNodeInternal = new NodeInternal();
		else
			newNodeInternal = new NodeInternal(temp->childs);

		// Goes to the rightmost path.
		int i = 1;
		for (; i < B; ++i)
		{
			if (newNodeInternal->childs[i] == NULL)
			{
				break;
			}
		}

		appendRightmostPath(level - 1, newNodeInternal->childs[i - 1], value);
		root = newNodeInternal;
	}
	else
	{
		NodeLeaf * newLeafNode = dynamic_cast<NodeLeaf*>(root);
		if (!newLeafNode) // maybe the root is NULL.
			newLeafNode = new NodeLeaf();
		else
			newLeafNode = new NodeLeaf(newLeafNode->values);

		newLeafNode->values.push_back(value);

		root = newLeafNode;
	}
}

// From the starting level @startLevel to the leaf level. Leaf level is 0.
// Returns the leaf node.
template<typename T>
typename PersistentVector<T>::NodeLeaf* PersistentVector<T>::buildPathToTheLeaf(int level, Node *& root) const // basicaly it`s not very const
{
	if (level > 0)
	{
		NodeInternal * newNode = new NodeInternal();
		root = newNode;
		return buildPathToTheLeaf(level - 1, newNode->childs[0]);
	}
	else
	{
		NodeLeaf * newNode = new NodeLeaf();
		root = newNode;
		return newNode;
	}
}

//Till fisrt null ptr.
template<typename T>
size_t PersistentVector<T>::getSizeOfNotNullPointers(const vector<Node*> & v) const
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] == NULL)
			return i;
	}

	return v.size();
}

// Checks if there is room in the rightmost leaf node. If so returns true.
template<typename T>
bool PersistentVector<T>::checkForRoomInRightmostLeafNode(int level, Node * root) const
{
	if (!root)
		return false;
	if (level <= 0)
	{
		NodeLeaf * leaf = dynamic_cast<NodeLeaf*>(root);
		if (!leaf)
			throw "Something bad happaned and cant locate some leafs...";

		return leaf->values.size() < B;
	}
	else
	{
		NodeInternal * temp = dynamic_cast<NodeInternal*>(root);
		int i = 1;
		for (; i < B; ++i)
		{
			if (temp->childs[i] == NULL)
			{
				break;
			}
		}

		return checkForRoomInRightmostLeafNode(level - 1, temp->childs[i - 1]);
	}
}

// Checks if the root node vector of childs/values are all taken.
template<typename T>
bool PersistentVector<T>::checkIfRootNodeIsFull(Node * root) const
{
	if (!root)
		return true;

	// Check if the root is actualy internal node. If so, the last value must be diferent than NULL.
	NodeInternal * rInternal = dynamic_cast<NodeInternal*>(root);
	if (rInternal != NULL)
	{
		return rInternal->childs[B - 1] != NULL;
	}

	// The root node is leaf, so the size of the vector must be equal (or bigger) than B.
	NodeLeaf * rLeaf = dynamic_cast<NodeLeaf*>(root);
	if (rLeaf != NULL)
	{
		return rLeaf->values.size() >= B;
	}

	return false;
}

// Removes the last value in the new vector. 
template<typename T>
void PersistentVector<T>::popRightmostPath(int level, Node *& root) const
{
	// Not a leaf node.
	if (level > 0)
	{
		// Copies the internal node.
		NodeInternal * temp = dynamic_cast<NodeInternal*>(root);
		NodeInternal * newNodeInternal;

		// If the pointer is null...(from before resizing of the tree.
		if (!temp)
			newNodeInternal = new NodeInternal();
		else
			newNodeInternal = new NodeInternal(temp->childs);

		// Goes to the rightmost path.
		int i = 1;
		for (; i < B; ++i)
		{
			if (newNodeInternal->childs[i] == NULL)
			{
				break;
			}
		}

		popRightmostPath(level - 1, newNodeInternal->childs[i - 1]);
		if (newNodeInternal->childs[0] == NULL) //if there was only 1 element in the child node and we pop it.
			root = NULL;
		else
			root = newNodeInternal;
	}
	else
	{
		NodeLeaf * newLeafNode = dynamic_cast<NodeLeaf*>(root);
		if (!newLeafNode) // maybe the root is NULL.
			newLeafNode = new NodeLeaf();
		else
			newLeafNode = new NodeLeaf(newLeafNode->values);

		newLeafNode->values.pop_back();

		if (newLeafNode->values.size() <= 0)
			newLeafNode = NULL;

		root = newLeafNode;
	}
}

// Basic DFS prints only leaf values.
template<typename T>
void PersistentVector<T>::print(int level, std::ostream& out, Node * root) const
{
	if (!root)
		return;
	if (level > 0)
	{
		NodeInternal * temp = dynamic_cast<NodeInternal*>(root);
		for (int i = 0; i < B; ++i)
		{
			print(level - 1, out, temp->childs[i]);
		}
	}
	else
	{
		NodeLeaf * temp = dynamic_cast<NodeLeaf*>(root);
		if (!temp)
			return;

		for (int i = 0; i < temp->values.size(); ++i)
		{
			out << temp->values[i] << " ";
		}
	}
}
