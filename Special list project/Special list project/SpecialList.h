#pragma once

/*
 *	
 *
 *
 *	I can store the information in other nodes as leafe node. For now I store it as a pointer to the object in every node. More memory(null pointers in non-leaf nodes), but for now it is not a problem.
*/

#include <vector>

using std::vector;

template <class T>
class SpecialList
{
private:
	// Basic abstract class.
	struct Node
	{
		virtual ~Node() = 0 {}; // No need for destructor for now.
	};

	// Internal node.
	struct InternalNode : public Node
	{
		char height;
		int size;
		bool reversed;
		Node* min;
		Node* max;
		vector<int> keys;
		vector<Node*> childs;

		InternalNode(char h = 1, int s = 1, bool rev = false, Node * minimum = NULL, Node* maximum = NULL) : height(h), size(s), reversed(rev), min(minimum), max(maximum)
		{
			childs.resize(3, NULL); // Make 3 childs, NULL ptr.
		}

		virtual ~InternalNode() {}; // for now not needed.
	};

	// Leaf node.
	struct LeafNode : public Node
	{
		T data;

		LeafNode(const T& d) : data(d) {}
		
		virtual ~LeafNode() {}; // for now not needed.
	};

	Node * root;
public:
	SpecialList()
	{
		root = NULL;
	}

	// Creates one node in the given SpecialList object(@id) with the given @value.
	// NOTE: deletes the nodes in the list, if there were some... 
	// I can make it static, with argument.. like that "static void create(SpecialList& list, const T& value)"
	void create(const T& value)
	{
		// Deletes the memory (in any case..).
		free(root);
		root = NULL;

		root = new LeafNode(value);
	}

	// Returns the min value of the list, if the list is empty, throws exeption(or there is something wrong with the list). TO DO make it for min & max one function...
	T getMin() const
	{
		if (isEmpty())
			throw "Empty list, can`t get min value!";

		InternalNode * internalNode;
		LeafNode * leafNode;

		if (internalNode = isInternalNode(root))
			if (leafNode = isLeafNode(internalNode->min))
				return leafNode->data;
		else if (leafNode = isLeafNode(root)) // not realy need for check, but in any case if there is other types of nodes..(I still have to make a dynamic cast)
			return leafNode->data;

		throw "Sorry, something went wrong with the list."; // If the min node pointer is NULL, or it`s not pointing to leaf node
	}

	// Returns the max value of the list, if the list is empty, throws exeption(or there is something wrong with the list).
	T getMax() const
	{
		if (isEmpty())
			throw "Empty list, can`t get max value!";

		InternalNode * internalNode;
		LeafNode * leafNode;

		if (internalNode = isInternalNode(root))
			if (leafNode = isLeafNode(internalNode->max))
				return leafNode->data;
		else if (leafNode = isLeafNode(root)) // not realy need for check, but in any case if there is other types of nodes..(I still have to make a dynamic cast)
			return leafNode->data;

		throw "Sorry, something went wrong with the list while trying to get the max value."; // If the min node pointer is NULL, or it`s not pointing to leaf node
	}

	// Reverse the order of the elements in the list.
	void reverse()
	{
		if (!root)
			return;

		root->reversed = !root->reversed;
	}

	// Prints the values of the list. To the given ostream.
	void printValues(std::ostream& out) const
	{
		printValues(out, root);
		out << "\n";
	}

	// Checks if the list is empty.
	bool isEmpty() const
	{
		return !root;
	}

	// Destructor. Deletes the memory for the nodes.
	~SpecialList()
	{
		free(root);
	}
private:
	// Deletes all nodes in the given subtree.
	void free(Node * root)
	{
		if (!root)
			return;

		InternalNode * internalNode;
		
		if (internalNode = isInternalNode(root))
		{
			size_t size = internalNode->childs.size();
			for (size_t i = 0; i < size; ++i)
				free(internalNode->childs[i]);
		}

		delete root;
	}

	// Prints the values of the list by the given root node. To the given ostream.
	void printValues(std::ostream& out, Node* root) const
	{
		if (!root)
			return;
		
		LeafNode * leafNode;
		InternalNode * internalNode;
		
		if (leafNode = isLeafNode(root))
		{
			out << leafNode->data << " ";
		}
		else if (internalNode = isInternalNode(root))
		{
			// TO DO something smarter...
			if (!internalNode->reversed)
				for (size_t i = 0; i < internalNode->childs.size(); ++i)
					printValues(out, internalNode->childs[i]);
			else
				for (size_t i = internalNode->childs.size(); i >= 0; --i)
					printValues(out, internalNode->childs[i]);
		}
	}


	// If the given node is a leaf node, returns a pointer to it, otherwise returns NULL.
	LeafNode * isLeafNode(Node* n) const
	{
		return dynamic_cast<LeafNode*>(n);
	}

	// If the given node is a internal node, returns a pointer to it, otherwise returns NULL.
	InternalNode * isInternalNode(Node* n) const
	{
		return dynamic_cast<InternalNode*>(n);
	}
private:
	// Ban copy constructor and operator=...
	SpecialList(const SpecialList& other);
	SpecialList& operator=(const SpecialList& other);
};