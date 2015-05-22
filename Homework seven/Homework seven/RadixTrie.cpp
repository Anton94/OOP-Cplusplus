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
	insert(root, word, data, strlen(word) * 8, 0);
}

// Adds new word with value- @data.
void RadixTrie::insert(Node *& root, const char* word, int data, size_t wordLength, size_t curLength)
{
	// Get the current bit.
	int bit = getIthBitOfString(word, curLength);

	// If the bit is ZERO and there is no left child, adds the rest of the word as new rib.
	if (bit == 0 && !root->left)
	{
		root->left = new Node(word, wordLength - curLength, data);
		return;
	}

	// If the bit is 1 and there is no right child, adds the rest of the word as new rib.
	if (bit == 1 && !root->right)
	{
		root->right = new Node(word, wordLength - curLength, data);
		return;
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