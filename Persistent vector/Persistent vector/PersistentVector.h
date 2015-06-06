#pragma once

/*
	* Anton Vasilev Dudov
	* #71488
	* Github repository: 
	*
	* The starting level of the vector tree is 6.
	* Optimization maybe I can keep the position of the rightmost taken node in child node vector.
	*
	*
*/

#include <type_traits>
#include <vector>

// 32 childs per node for the tree.
#define B 32
#define MAX_LEVEL 5

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
public:
	PersistentVector()
	{
		buildPathToTheLeaf(MAX_LEVEL, root); // From level 5(real root) to level 0(the leaf level).
		count = 0;
	}

	// Returns the value of the element at position *index*.
	T operator[](int index) const;

	// Returns a new vector with the element at position *index* replaced by *value*.
	PersistentVector update(int index, T value) const;

	// Returns a new vector with *value* appended at the end.
	PersistentVector append(T value) const
	{
		// Creates exact copy of the vector.
		PersistentVector<T> newVector(*this);


		// If onle need to append the value in the vector of valus in the leaf node.
		if (checkForRoomInRightmostLeafNode(MAX_LEVEL, root))
		{
			appendRightmostPath(MAX_LEVEL, newVector.root, value);
		}
		else
		// If needed creates new internal nodes and adds the value.
		{
			append(MAX_LEVEL, newVector.root, value);
		}


		++newVector.count;

		return newVector;
	}

	// Returns a new vector that's the same as this one but without the last element.
	PersistentVector pop() const;

	int size() const
	{
		return count;
	}


	// Basic DFS prints only leaf values.
	void print(std::ostream& out) const
	{
		print(MAX_LEVEL, out, root);
		out << "\n";
	}
private:
	// Basic DFS prints only leaf values.
	void print(int level, std::ostream& out, Node * root) const
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

	// Adds only the value in the new vector. (there is space in the rightmost leaf node)
	void appendRightmostPath(int level, Node *& root, const T& value) const
	{
		if (level > 0)
		{
			// Copies the internal node.
			root = new NodeInternal(dynamic_cast<NodeInternal*>(root)->childs);

			// Goes to the rightmost path.
			NodeInternal * temp = dynamic_cast<NodeInternal*>(root);

			for (int i = 1; i < B; ++i)
			{
				if (temp->childs[i] == NULL)
				{
					appendRightmostPath(level - 1, temp->childs[i - 1], value);
					return;
				}
			}
		}
		else
		{
			root = new NodeLeaf(dynamic_cast<NodeLeaf*>(root)->values);
			dynamic_cast<NodeLeaf*>(root)->values.push_back(value);
		}
	}

	// The rightmost leaf node is full, copies the path till it founds a full node (internal or leaf) and makes new path to the leaf level (from the level above the full node)
	// and appends the value in the new leaf node.
	void append(int level, Node *& root, const T& value) const
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
			for (int i = 1; i < B; ++i)
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

	//Till fisrt null ptr.
	size_t getSizeOfNotNullPointers(const vector<Node*> & v) const
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (v[i] == NULL)
				return i;
		}
	}

	// From the starting level @startLevel to the leaf level. Leaf level is 0.
	// Returns the leaf node.
	NodeLeaf* buildPathToTheLeaf(int level, Node *& root) const // basicaly it`s not very const
	{
		if (level > 0)
		{
			NodeInternal * newNode = new NodeInternal();
			root = newNode;
			buildPathToTheLeaf(level - 1, newNode->childs[0]);
		}
		else
		{
			NodeLeaf * newNode = new NodeLeaf();
			root = newNode;
			return newNode;
		}
	}

	// Checks if there is room in the rightmost leaf node. If so returns true.
	bool checkForRoomInRightmostLeafNode(int level, Node * root) const
	{
		if (!root)
			return false;
		if (level <= 0)
		{
			return (dynamic_cast<NodeLeaf*>(root))->values.size() < B;
		}
		else
		{
			NodeInternal * temp = dynamic_cast<NodeInternal*>(root);
			for (int i = 1; i < B; ++i)
			{
				if (temp->childs[i] == NULL)
				{
					return checkForRoomInRightmostLeafNode(level - 1, temp->childs[i - 1]);
				}
			}

			return false;
		}
	}
};