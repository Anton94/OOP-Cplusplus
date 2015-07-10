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

#include <vector>
#include "Utility.h"

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
		virtual int getSize() const = 0;
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
		virtual int getSize() const { return 1; }

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

		virtual int getSize() const 
		{
			return size;
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
		Case 2: The @this and the @other are with the same height.
		Case 3: h1 > h2(height of the @this tree is bigger than the height of @other tree). Attach the @other to the end of @this.
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
		else if (root->height == other.root->height) // their height is bigger than 1(the case where it is 1, is in the other method).
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

	// Merge the @root subtree with the @other subtree, where the height of the @root IS BIGGER than the height of the @other subtree.
	// @atTheEnd is to indicate where to put the subtree, at the beginning of the list(@atTheEnd = false) or at the end of the list (@atTheEnd = true).
	void merge(Node *& root, Node * other, bool atTheEnd)
	{
		InternalNode * internalNodeRoot = isInternalNode(root);
		//InternalNode * internalNodeOther = isInternalNode(other);
		if (!internalNodeRoot)
			throw "Sorry, something went wrong :(";

		// If the root node is reversed, than change the oriantation.
		bool insertAtTheEnd = internalNodeRoot->reversed ? !atTheEnd : atTheEnd; 

		// The parent is root.
		if (root->height == other->height + 1)
		{
			// attach and goes back to recheck parents...
			if (insertAtTheEnd)
			{
				int i = getIndexOfRightMostChild(internalNodeRoot);
				++i; // go to the next child (NULL)
				
				if (i >= internalNodeRoot->childs.size())
					internalNodeRoot->childs.push_back(other);
				else
					internalNodeRoot->childs[i] = other;
				
				internalNodeRoot->keys.push_back(internalNodeRoot->keys.size() + internalNodeRoot->childs[i - 1]->getSize()); // The next key value must be the previous one + the size of previous last child
			}
			// Insert it in the front
			else
			{
				// Insert the child at the beginnig. (it fixes the keys too).
				pushFrontOnChildVector(internalNodeRoot, other);				
			}
		}
		else
		{
			int i = 0; // index (in which child will be inserted the subtree). By default it`s in leftmost child
			
			if (insertAtTheEnd) // If I had to insert it at the end, go to the right-most child.
			{
				// Find the right-most valid child.
				i = getIndexOfRightMostChild(internalNodeRoot);

				merge(internalNodeRoot->childs[i], other, insertAtTheEnd);
				// No need to fix the key value, because it`s last one.
			}
			else
			{
				merge(internalNodeRoot->childs[0], other, insertAtTheEnd);

				fixKeyValuesOfInternalNode(internalNodeRoot);
			}
				
			// Check if the child, where the subtree is inserted has more than 3 childs, if so, split it and attach the new child to the childs of this one (@internalNodeRoot).
			int indexOfNewRightMostChild = getIndexOfRightMostChild(internalNodeRoot);
			if (indexOfNewRightMostChild >= 3) // If the righ-most child index is 3, that means that the childs are four
			{
				// Split the childs.
				InternalNode * neededToSplitChild = isInternalNode(internalNodeRoot->childs[i]); // Its internal for sure.
				
				InternalNode * n = new InternalNode(neededToSplitChild->height);
				
				// Combine two childs and put them in new internal node, which will take place after this node(at the end of chlids of @internalNodeRoot)
				
				if (neededToSplitChild->reversed) // If the child node is reversed, than take first 2 
				{
					n->childs[0] = neededToSplitChild->childs[0];
					n->childs[1] = neededToSplitChild->childs[1];

					neededToSplitChild->childs[0] = neededToSplitChild->childs[2];
					neededToSplitChild->childs[1] = neededToSplitChild->childs[3];
					neededToSplitChild->childs[2] =	neededToSplitChild->childs[3] = NULL;
				}
				else // Last two 
				{
					n->childs[0] = neededToSplitChild->childs[2];
					n->childs[1] = neededToSplitChild->childs[3];
					neededToSplitChild->childs[2] = neededToSplitChild->childs[3] = NULL;
				}
				
				neededToSplitChild->childs.resize(3); //Cut the last child..
				// TO DO: make a function... if this shit works some day...
				// Fix the sizes.
				n->size = n->childs[0]->getSize() + n->childs[1]->getSize();
				neededToSplitChild->size = neededToSplitChild->childs[0]->getSize() + neededToSplitChild->childs[1]->getSize();

				// Fix the keys.
				n->keys.push_back(n->childs[0]->getSize()); 
				neededToSplitChild->keys.clear();
				neededToSplitChild->keys.push_back(neededToSplitChild->childs[0]->getSize());

				// Fix min/max values.
				n->min = getBetterLeafNode(n->childs[0], n->childs[1], smaller);
				n->max = getBetterLeafNode(n->childs[0], n->childs[1], bigger);
				neededToSplitChild->min = getBetterLeafNode(neededToSplitChild->childs[0], neededToSplitChild->childs[1], smaller);
				neededToSplitChild->max = getBetterLeafNode(neededToSplitChild->childs[0], neededToSplitChild->childs[1], bigger);

				if (insertAtTheEnd)
				{
					internalNodeRoot->childs.push_back(n);

					// Fix internal node keys. add last key = last - 1 key + splited child size
					internalNodeRoot->keys.push_back(internalNodeRoot->keys[internalNodeRoot->keys.size() - 1] + neededToSplitChild->getSize());
				}
				else // insert the splited child to be second...
				{
					InternalNode * firstChild = isInternalNode(internalNodeRoot->childs[0]);
					internalNodeRoot->childs[0] = n;
					pushFrontOnChildVector(internalNodeRoot, firstChild); // It fixes the key values.
				}
			}
		}

		// Fix min/max values.
		if (other->height == 1)
		{
			internalNodeRoot->min = getBetterLeafNode(internalNodeRoot->min, other, smaller);
			internalNodeRoot->max = getBetterLeafNode(internalNodeRoot->max, other, bigger);
		}
		else
		{
			InternalNode * internalNodeOther = isInternalNode(other);
			internalNodeRoot->min = getBetterLeafNode(internalNodeRoot->min, internalNodeOther->min, smaller);
			internalNodeRoot->max = getBetterLeafNode(internalNodeRoot->max, internalNodeOther->max, bigger);
		}

		// Fix the size.
		internalNodeRoot->size += other->getSize();

	}

	// Inserts a child at the beginning of the vector
	void pushFrontOnChildVector(InternalNode * n, Node * newChild)
	{
		if (n->childs[n->childs.size() - 1] != NULL)
			n->childs.push_back(NULL);

		for (size_t i = getIndexOfRightMostChild(n) + 1; i >= 1; --i)
		{
			n->childs[i] = n->childs[i - 1];
		}
		
		n->childs[0] = newChild;// Fix the keys.
		
		n->keys.push_back(-1); // unvalid value...
		fixKeyValuesOfInternalNode(n);
	}

	// Fix the key values in internal node by it`s childs.
	void fixKeyValuesOfInternalNode(InternalNode * n)
	{
		// Fix the key values.
		size_t size = n->keys.size();
		n->keys[0] = n->childs[0]->getSize();
		for (size_t i = 1; i < size && n->childs[i] != NULL; ++i)
		{
			n->keys[i] = n->childs[i]->getSize() + n->keys[i - 1];
		}
	}

	// Returns the index of the valid right-most child. (-1 if no-valid once)
	int getIndexOfRightMostChild(InternalNode * n) const
	{
		int i = n->childs.size() - 1;
		for (; i >= 0; --i)
		{
			if (n->childs[i] != NULL)
				return i;
		}

		return i;
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