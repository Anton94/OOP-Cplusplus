#include "RadixTrie.h"
#include "Utility.h"

// Sets the default values.
RadixTrie::RadixTrie()
{
	setDefaultValues();
}

// Deletes the trie and sets the default values.
void RadixTrie::clear()
{
	free(root);
	setDefaultValues();
}

// Adds new word with value- @data.
void RadixTrie::insert(const char* word, int data)
{
	if (!word)
		return;
	// I made it unsigned char so it can take values for 0-255 symbols.. I don`t know if it`s OK... TO DO -- ask
	insert(root, (const unsigned char*)word, data, strlen(word) * 8, 0);
}

// Adds new word with value- @data.
/*
	Basic situations:
		1) If there is no more path for the word`s bit`s make a leaf.
		2) The word ends in some rib - splits the rib. (Adds new node in the rib).
		3) The bits in  the rib and the bits of the word are different. Splits the rib there and attaches the rest of the rib and the rest of the word as childrens.
		4) Exacly matches on the rib and it`s the end of the word - set`s only the value.
*/
void RadixTrie::insert(Node *& root, const unsigned char* word, int data, size_t wordLength, size_t curBit)
{
	// Some weird case, maybe not even possible, (empty word is one case... so possible...)
	if (curBit >= wordLength)
	{
		return; // Or throw some kind of exeption...
	}

	// If the given child is NULL, makes a new rib on it`s place with the rest of the word. Case 1)
	if (!root)
	{
		root = new Node(word, wordLength - curBit, data);
		return;
	}

	unsigned char bit, nodeBit;

	// Go through the bits of the rib (@root node) and check for matches.
	for (unsigned char i = 1; i <= root->length; ++i)
	{
		// Get the bits. (if the curBit is more than wordLength , no problem, it will take from the term null..)
		bit = getIthBitOfString(word, curBit);
		nodeBit = getIthBitOfString(root->word, curBit);

		// If the word ends in the rib or the bits are different(rib and word bits).
		if (curBit >= wordLength || bit != nodeBit)
		{
			Node * n = new Node(word, i - 1);
			root->length = root->length - i + 1;
			
			// If the word ends in some point of the rib(@root). Case 2)
			// Splits it where it ends and make new node with value - @data, makes the pointer to that new node , the real pointer @root (the father left/right child)
			if (curBit >= wordLength)
			{
				n->val = data;

				if (nodeBit == 0)
					n->left = root;
				else
					n->right = root;
			}
			else // bit != nodeBit. Case 3)
			{
				// If the bit is 0 and the rib bit is 1.
				// Splits the rib and adds the current splited half to the right and the rest of the word on the left.
				if (bit < nodeBit)
				{
					// Add the new node of the rest of the word.
					n->left = new Node(word, wordLength - curBit, data);
					n->right = root;
				}
				// If the bit is 1 and the rib bit is 0.
				// Splits the rib and adds the current splited half to the left and the rest of the word on the right.
				else // bit > nodeBit
				{
					// Add the new node of the rest of the word.
					n->right = new Node(word, wordLength - curBit, data);
					n->left = root;
				}
			}

			root = n;

			return;
		}

		++curBit;
	}

	// If the word matchs exactly on this rib(@root node), changes only the value of the rib. (Rewrites the existing word value, if there was valid value) Case 4)
	if (curBit >= wordLength)
	{
		root->val = data;
		return;
	}

	// Get the next bit value.
	bit = getIthBitOfString(word, curBit);

	// If the current taken bit @bit is 0, goes to left child, otherwise (it`s 1) and goes to the right child.
	if (bit == (unsigned char)0)
	{
		insert(root->left, word, data, wordLength, curBit);
	}
	else
	{
		insert(root->right, word, data, wordLength, curBit);
	}
}

// Returns the value of the given word, if it`s not in the radix trie, returns negative number.
int RadixTrie::find(const char* word) const
{
	if (!word)
		return -1;

	return find(root, (const unsigned char*)word, strlen(word) * 8, 0);
}

// Returns the value of the given word, if it`s not in the radix trie, returns negative number.
int RadixTrie::find(Node * root, const unsigned char* word, size_t wordLength, size_t curBit) const
{
	if (!root || curBit >= wordLength) // curBit >= wordLength if the searched word is empty("") or some weird shits...
		return -1;

	unsigned char bit, nodeBit;

	// Go through the bits of the rib (@root node) and check for matches.
	for (unsigned char i = 1; i <= root->length; ++i)
	{
		// Get the bits. (if the curBit is more than wordLength , no problem, it will take from the term null..)
		bit = getIthBitOfString(word, curBit);
		nodeBit = getIthBitOfString(root->word, curBit);

		// If the rib has more values(0 or 1) than the word.
		if (curBit >= wordLength)
			return -1;

		if (bit != nodeBit)
			return -1;

		++curBit;
	}

	// If the word matchs exactly on this rib(@root node).
	if (curBit >= wordLength)
	{
		return root->val; // If there is no word on that rib end, it will return -1.
	}

	// Get the next bit value.
	bit = getIthBitOfString(word, curBit);

	// If the current taken bit @bit is 0, goes to left child, otherwise (it`s 1) and goes to the right child.
	if (bit == (unsigned char) 0)
	{
		return find(root->left, word, wordLength, curBit);
	}
	else
	{
		return find(root->right, word, wordLength, curBit);
	}
}

// Returns the values of the words, whith the given @prefix
vector<int> RadixTrie::getAllWithPrefix(const char* prefix) const
{
	if (!prefix)
		return vector<int>();

	vector<int> result;
	getAllWithPrefix(root, (const unsigned char*)prefix, strlen(prefix) * 8, 0, result);
	return result;
}

// Returns the values of the words, whith the given @prefix
void RadixTrie::getAllWithPrefix(Node * root, const unsigned char* word, size_t wordLength, size_t curBit, vector<int> & result) const
{
	if (!root || curBit >= wordLength) // curBit >= wordLength if the searched word is empty("") or some weird shits...
		return;

	unsigned char bit, nodeBit;

	// Go through the bits of the rib (@root node) and check for matches.
	for (unsigned char i = 1; i <= root->length; ++i)
	{
		// Get the bits. (if the curBit is more than wordLength , no problem, it will take from the term null..)
		bit = getIthBitOfString(word, curBit);
		nodeBit = getIthBitOfString(root->word, curBit);

		// If the rib has more values(0 or 1) than the word,
		if (curBit >= wordLength)
		{
			DFS(root, result);
			return;
		}

		if (bit != nodeBit)
			return;

		++curBit;
	}

	// If the word matchs exactly on this rib(@root node).
	if (curBit >= wordLength)
	{
		DFS(root, result);
		return;
	}

	// Get the next bit value.
	bit = getIthBitOfString(word, curBit);

	// If the current taken bit @bit is 0, goes to left child, otherwise (it`s 1) and goes to the right child.
	if (bit == (unsigned char) 0)
	{
		getAllWithPrefix(root->left, word, wordLength, curBit, result);
	}
	else
	{
		getAllWithPrefix(root->right, word, wordLength, curBit, result);
	}
}

// Makes DFS on the subtree and adds to the given vector all values which are valid word(>=0). In-order.
void RadixTrie::DFS(Node * root, vector<int>& result) const
{
	if (!root)
		return;

	DFS(root->left, result);

	if (root->val >= 0)
		result.push_back(root->val);

	DFS(root->right, result);
}

// Removes a word from the radix trie. Returns true if the words was removed otherwise returns false.
bool RadixTrie::remove(const char* word)
{
	if (!word)
		return false;

	// If the first bit is 0, goes to left child, otherwise goes to the right child
	if (getIthBitOfSymbol(word[0], 0) == 0)
		return remove(root->left, root, (const unsigned char*)word, strlen(word) * 8, 0);
	else
		return remove(root->right, root, (const unsigned char*)word, strlen(word) * 8, 0);
}

// Removes a word from the radix trie. Returns true if the words was removed otherwise returns false.
bool RadixTrie::remove(Node *& root, Node *& father, const unsigned char* word, size_t wordLength, size_t curBit)
{
	if (!root || !father || curBit >= wordLength)
		return false;

	unsigned char bit, nodeBit;

	// Go through the bits of the rib (@root node) and check for matches.
	for (unsigned char i = 1; i <= root->length; ++i)
	{
		// Get the bits. (if the curBit is more than wordLength , no problem, it will take from the term null..)
		bit = getIthBitOfString(word, curBit);
		nodeBit = getIthBitOfString(root->word, curBit);

		// If the rib has more values(0 or 1) than the word.
		if (curBit >= wordLength)
			return false;

		if (bit != nodeBit)
			return false;

		++curBit;
	}

	// If the word matchs exactly on this rib(@root node).
	if (curBit >= wordLength)
	{
		return remove(root, father);
	}

	// Get the next bit value.
	bit = getIthBitOfString(word, curBit);

	// If the current taken bit @bit is 0, goes to left child, otherwise (it`s 1) and goes to the right child.
	if (bit == (unsigned char) 0)
	{
		return remove(root->left, root, word, wordLength, curBit);
	}
	else
	{
		return remove(root->right, root, word, wordLength, curBit);
	}
}

// By given nodes (child - @root and father @father) removes the child. Returns true if the words was removed otherwise returns false.
/*
	3 basic situations.

		1) The @root is a leaf - deletes it
			- if the father is a valid node (end of a word) - nothing
			- if the father is not a valid node, diferent than real root(not end of a word(value = -1)) - merge the father with his other child(if has some, if the trie has good structure it will have).
		2) The @root has left and right child - makes the value of the @root -1.
		3) The @root has only left/right child - merge the father with other child of the @root.
*/
bool RadixTrie::remove(Node*& root, Node*& father)
{
	// In that case there is no word, so returns false.
	if (!root || !father || root->val < 0)
		return false;

	// First case.
	if (!root->left && !root->right)
	{
		delete root;
		root = NULL;

		if (father->val < 0 && father != this->root)
			mergeNodeWithValidChild(father);
	}
	// Second case.
	else if (root->left && root->right)
	{
		root->val = -1;
	}

	// Third case. The root node has only one child.
	else
	{
		mergeNodeWithValidChild(root);
	}

	return true;
}

// Merges the given node with his valid child(the given node has only one child- left/right).
void RadixTrie::mergeNodeWithValidChild(Node *& root)
{
	if (root->left || root->right)
	{
		Node * n;

		if (root->left)
		{
			root->left->length += root->length;
			n = root->left;
		}
		else
		{
			root->right->length += root->length;
			n = root->right;
		}

		delete root;
		root = n;
	}	
}

// Deletes the trie.
RadixTrie::~RadixTrie()
{
	free(root);
}

// Deletes the trie post-order.
void RadixTrie::free(Node * root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

// Creates the default node for the root.
void RadixTrie::setDefaultValues()
{
	root = new Node();
}