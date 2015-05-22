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
void RadixTrie::insert(const unsigned char* word, int data)
{
	insert(root, word, data, strlen((const char*)word) * 8, 0);
}

// Adds new word with value- @data.
void RadixTrie::insert(Node *& root, const unsigned char* word, int data, size_t wordLength, size_t curBit)
{
	// Some weird case, maybe not even possible, (empty word is one case... so possible...)
	if (curBit >= wordLength)
	{
		return; // Or throw some kind of exeption...
	}

	// If the given child is NULL, makes a new rib on it`s place with the rest of the word.
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

		// If the word ends in some point of the rib(@root).
		// Splits it where it ends and make new node with value - @data, makes the pointer to that new node , the real pointer @root (the father left/right child)
		if (curBit >= wordLength)
		{ 
			Node * n = new Node(root->word, i, data);
			root->length -= i;
			if (nodeBit == 0)
				n->left = root;
			else
				n->right = root;

			root = n;

			return;
		}
		// If the bit is 0 and the rib bit is 1.
		// Splits the rib and adds the current splited half to the right and the rest of the word on the left.
		else if (bit < nodeBit)
		{
			Node * n = new Node(root->word, i - 1); // -1 because there is match till now. TO DO CHECK
			root->length = root->length - i + 1;
			// Add the new node of the rest of the word.
			n->left = new Node(word, wordLength - curBit, data);
			n->right = root;

			root = n;

			return;
		}
		// If the bit is 1 and the rib bit is 0.
		// Splits the rib and adds the current splited half to the left and the rest of the word on the right.
		else if (bit > nodeBit)
		{
			Node * n = new Node(root->word, i - 1);
			root->length = root->length - i + 1;
			// Add the new node of the rest of the word.
			n->right = new Node(word, wordLength - curBit, data);
			n->left = root;

			root = n;

			return;
		}

		++curBit;
	}

	// If the word matchs exactly on this rib(@root node), changes only the value of the rib.
	if (curBit >= wordLength)
	{
		root->val = data;
		return;
	}

	// Get the next bit value.
	bit = getIthBitOfString(word, curBit);

	// If the current taken bit @bit is 0, goes to left child, otherwise (it`s 1) and goes to the right child.
	if (bit == 0)
	{
		insert(root->left, word, data, wordLength, curBit);
	}
	else
	{
		insert(root->right, word, data, wordLength, curBit);
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