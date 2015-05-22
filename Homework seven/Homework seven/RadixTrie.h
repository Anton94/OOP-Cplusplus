#pragma once

#include <fstream>
#include <vector>

using std::vector;
using std::ifstream;

/*
	Radix trie. If the node contains some value >= 0 , then it`s end of some word. If it conatins negative (-1) it`s not.
	Left subtree is for 0 bit and right is for 1.
*/
class RadixTrie
{
	struct Node
	{
		int val;
		const unsigned char * word;
		int length; // TO DO unsigned char 
		Node * left, *right;
		Node(const unsigned char * w = NULL, int len = 0, int v = -1, Node * l = NULL, Node* r = NULL) : word(w), length(len), val(v), left(l), right(r) {}
	};
public:
	RadixTrie();

	// Deletes the trie and sets the default status.
	void clear();
	
	// Adds new word with value- @data.
	void insert(const unsigned char* word, int data);

	// Deletes the trie.
	~RadixTrie();
private:
	// Deletes the trie post-order.
	void free(Node * root);

	// Adds new word with value- @data.
	void insert(Node *& root, const unsigned char* word, int data, size_t wordLength, size_t curBit);

	// Creates the default node for the root.
	void setDefaultValues();
private:
	Node * root;
private:
	// For this homework I don`t need to copy radix tries.
	RadixTrie(const RadixTrie& other);
	RadixTrie& operator=(const RadixTrie& other);
};