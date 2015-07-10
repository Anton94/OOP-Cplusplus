/*
*********************************************************************************************************************************************************************
*
*	Name: Anton Vasilev Dudov
*	FN:   71488
*
*
*	Github repository: https://github.com/Anton94/OOP-Cplusplus/tree/master/Special%20list%20project
*
*	Source for the 2-3 tree structure:	http://pages.cs.wisc.edu/~vernon/cs367/notes/10.23TREE.html
*										http://www.cs.nyu.edu/courses/fall06/G22.3520-001/lec5.pdf
*
*********************************************************************************************************************************************************************
*/

#pragma once



// Returns true if @l value is bigger than @r.
template<class T>
bool bigger(const T& l, const T& r)
{
	return l > r;
}
// Returns true if @l value is smaller than @r.
template<class T>
bool smaller(const T& l, const T& r)
{
	return l < r;
}

#include <vector>

using std::vector;

template <class T>
class SpecialList
{
private:
	// Basic abstract class.
	struct Node
	{
		Node(char h = 1) : height(h) {}
		virtual const T& getMin() const = 0;
		virtual const T& getMax() const = 0;
		virtual ~Node() = 0 {}; // No need for destructor for now.
		char height; // to avoid checing for leaf node at some places. more memory, TO DO check it if`s better...
	};

	// Leaf node.
	struct LeafNode : public Node
	{
		T data;

		LeafNode(const T& d, char h = 1) : Node(h), data(d) {}

		// The min and max values are the only value in this leaf.
		virtual const T& getMin() const { return data; }
		virtual const T& getMax() const { return data; }

		virtual ~LeafNode() {}; // for now not needed.
	};

	// Internal node.
	struct InternalNode : public Node
	{
		int size;
		bool reversed;
		LeafNode* min;
		LeafNode* max;
		vector<int> keys;
		vector<Node*> childs;

		InternalNode(char h = 1, int s = 1, bool rev = false, LeafNode * minimum = NULL, LeafNode* maximum = NULL) : Node(h), size(s), reversed(rev), min(minimum), max(maximum)
		{
			childs.resize(3, NULL); // Make 3 childs, NULL ptr.
		}

		// Returns the min value in this subtree. Throws exeption if something is wrong.
		virtual const T& getMin() const
		{
			return getDataFromLeafNode(min);
		}

		// Returns the min value in this subtree. Throws exeption if something is wrong.
		virtual const T& getMax() const
		{
			return getDataFromLeafNode(max);
		}

		virtual ~InternalNode() {}; // for now not needed.

	private:
		// Returns the value in this subtree. Throws exeption if something is wrong.
		const T& getDataFromLeafNode(LeafNode * n) const
		{
			if (!n)
				throw "Sorry, something went wrong with the list :(";

			return n->data;
		}
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

	// Merges the @this tree and the given one, and the given one stop exists.
	// Adds the elements of the @other list at the end of @this one.
	/*
		Case 1: If the tree is empty.
		Case 2: The @this and the @other are with the same hight.
		Case 3: h1 >= h2(height of the @this tree is bigger than (equal to) the height of @other tree). Attach the @other to the end of @this.
		Case 4: h1 < h2 Attach the @this to the end of @other and make @root to point other.root.
	*/
	void merge(SpecialList& other)
	{
		if (!other.root)
			return;

		// Case 1.
		if (!root)
		{
			root = other.root;
		}
		// Case 2.
		if (root->height == other.root->height) // their height is bigger than 1(the case where it is 1, is in the other method).
		{
			InternalNode * n = new InternalNode(root->height + 1);

			n->childs[0] = root;
			n->childs[1] = other.root;

			if (root->height == 1)
			{
				n->size = 2;
				n->keys.push_back(1);
				n->min = getBetterLeafNode(root, other.root, smaller);
				n->max = getBetterLeafNode(root, other.root, bigger);
			}
			else
			{
				InternalNode * internalNodeRoot  = isInternalNode(root);
				InternalNode * internalNodeOther = isInternalNode(other.root);
				n->size = internalNodeRoot->size + internalNodeOther->size;
				n->keys.push_back(internalNodeRoot->size);
				n->min = getBetterLeafNode(internalNodeRoot->min, internalNodeOther->min, smaller);
				n->max = getBetterLeafNode(internalNodeRoot->max, internalNodeOther->max, bigger);
			}
			
			root = n;
		}
		// Case 3.
		else if (root->height >= other.root->height)
		{
			merge(root, other.root, true); // Attach @other tree to the end of @this tree.
		}
		// Case 4.
		else
		{
			merge(other.root, root, false); // Attach @this tree to the beginning of @other tree.
			root = other.root;
		}

		other.root = NULL; // Make other tree empty.
	}

	// Merge the @root subtree with the @other subtree, where the height of the @root is bigger(or equal) to the height of the @other subtree.
	// @atTheEnd is to indicate where to put the subtree, at the beginning of the list(@atTheEnd = false) or at the end of the list (@atTheEnd = true).
	void merge(Node *& root, Node * other, bool atTheEnd)
	{
		InternalNode * internalNodeRoot = isInternalNode(root);
		InternalNode * internalNodeOther = isInternalNode(other);
		if (!internalNodeRoot || !internalNodeOther)
			throw "Sorry, something went wrong :(";

		// If the root node is reversed, than change the oriantation.
		bool insertAtTheEnd = internalNodeRoot->reversed ? !atTheEnd : atTheEnd; 

		
			// attach and goes back to recheck parents...


		// Find the parent.
	}

	// Returns the min value of the list, if the list is empty, throws exeption(or there is something wrong with the list). TO DO make it for min & max one function...
	T getMin() const
	{
		if (isEmpty())
			throw "Empty list, can`t get min value!";

		return root->getMin();
	}

	// Returns the max value of the list, if the list is empty, throws exeption(or there is something wrong with the list).
	T getMax() const
	{
		if (isEmpty())
			throw "Empty list, can`t get max value!";

		return root->getMax();
	}

	// Reverse the order of the elements in the list.
	void reverse()
	{
		if (!root)
			return;

		InternalNode * internalNode = isInternalNode(root);
		if (!internalNode)
			return; // the root node is leaf or so..

		internalNode->reversed = !internalNode->reversed;
	}

	// Returns the element on the given position.
	T getAt(int pos) const
	{
		if (pos < 1 || pos > getSize()) // Pos in interval [1,size]
			throw "Invalid position!";

		 return getAt(root, pos);
	}

	// Get size of the list.
	size_t getSize() const
	{
		if (isEmpty())
			return 0;
		
		InternalNode * internalNode = isInternalNode(root);
		if (!internalNode)
			return 1;

		return internalNode->size;
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
	// Helper function for min/max element: returns the min/max (compare function result) leaf node.
	LeafNode * getBetterLeafNode(Node * left, Node * right, bool(*compare)(const T& l, const T& r))
	{
		LeafNode * leafRoot = isLeafNode(left);
		LeafNode * leafOther = isLeafNode(right);
		if (!leafRoot || !leafOther)
			throw "Something went wrong :(";

		if (compare(leafRoot->data, leafOther->data))
			return leafRoot;
		else
			return leafOther;
	}

	// Returns the element on the given position.
	T getAt(Node * root, int pos) const
	{
		LeafNode * leaf = isLeafNode(root);
		if (leaf)
			return leaf->data;

		// It has to be internal node.
		InternalNode * internalNode = isInternalNode(root);
		if (internalNode->reversed)
		{
			// get the needed position if the node is reversed.
			pos = internalNode->size - pos + 1;
		}

		size_t i = 0;
		for (; i < internalNode->keys.size(); ++i)
		{
			if (pos <= internalNode->keys[i])
			{
				// Decrease the position with the key value (on the left). (because the left subtree(s) has the elements from 0 to key value with index i - 1)
				if (i > 0)
					pos -= internalNode->keys[i - 1];

				return getAt(internalNode->childs[i], pos);
			}
		}

		// else the needed childs is last one(last valid one!).
		return getAt(internalNode->childs[i], pos - internalNode->keys[i - 1]);
	}

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