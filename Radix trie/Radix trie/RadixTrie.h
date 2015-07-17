#pragma once

/*
	Homework seven, SD 2
	Anton Dudov, #71488

	Github repository: https://github.com/Anton94/OOP-Cplusplus
	Github project: https://github.com/Anton94/OOP-Cplusplus/tree/master/Homework%20seven

	I make the pointers to const unsigned char* but it realy does not matter ...
*/

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
		int length; // TO DO change the 'int' type to 'unsigned char' but I don`t know if I will manage to make all ribs max 256 (in testing functions) so I will leave it like that.
		Node *left, *right;
		Node(const unsigned char * w = NULL, int len = 0, int v = -1, Node * l = NULL, Node* r = NULL) : word(w), length(len), val(v), left(l), right(r) {}
	};
public:
	RadixTrie();

	// Deletes the trie and sets the default status.
	void clear();
	
	// Adds new word with value- @data.
	void insert(const char* word, int data);

	// Returns the value of the given word, if it`s not in the radix trie, returns negative number.
	int find(const char* word) const;

	// Returns the values of the words, whith the given @prefix.
	vector<int> getAllWithPrefix(const char* prefix) const;

	// Removes a word from the radix trie. Returns true if the words is removed otherwise returns false.
	bool remove(const char* word);

	// Deletes the trie.
	~RadixTrie();
private:
	// Deletes the trie post-order.
	void free(Node * root);

	// Adds new word with value- @data.
	void insert(Node *& root, const unsigned char* word, int data, size_t wordLength, size_t curBit);
	
	// Returns the value of the given word, if it`s not in the radix trie, returns negative number.
	int find(Node * root, const unsigned char* word, size_t wordLength, size_t curBit) const;

	// Returns the values of the words, whith the given @prefix
	void getAllWithPrefix(Node * root, const unsigned char* word, size_t wordLength, size_t curBit, vector<int> & result) const;

	// DFS on the given node, writes the valid words(the value is >= 0) in the given vector.
	void DFS(Node * root, vector<int>& result) const;

	// Removes a word from the radix trie. Returns true if the words was removed otherwise returns false.
	bool remove(Node *& root, Node *& father, const unsigned char* word, size_t wordLength, size_t curBit);

	// By given nodes (child - @root and father @father) removes the child.
	bool remove(Node*& root, Node*& father);

	// Merges the given node with his valid child(the given node has only one child- left/right).
	void mergeNodeWithValidChild(Node *& root);

	// Creates the default node for the root.
	void setDefaultValues();
private:
	Node * root;
private:
	// For this homework I don`t need to copy radix tries.
	RadixTrie(const RadixTrie& other);
	RadixTrie& operator=(const RadixTrie& other);
};