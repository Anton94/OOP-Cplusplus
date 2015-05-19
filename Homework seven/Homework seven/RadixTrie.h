#pragma once

#include <fstream>
#include "Dictionary.h"

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
		const char * word;
		int startBit, length;
		Node * left, *right;
		Node(char * w = NULL, int sb = 0, int len = 0, int v = -1, Node * l = NULL, Node* r = NULL) : word(w), startBit(sb), length(len), val(v), left(l), right(r) {}
	};
public:
	RadixTrie()
	{
		root = new Node(); // Default node...
	}
	
	bool deserializeDictionary(char * dictionaryFile)
	{
		ifstream inDictionary(dictionaryFile);
		if (!inDictionary)
			return false;

		bool res = dictionary.deserialize(inDictionary);
		
		inDictionary.close();

		return res;
	}

	void printDictionaryToCout() const
	{
		dictionary.printToCout();
	}

	~RadixTrie()
	{
		free(root);
	}
private:
	void free(Node * root)
	{
		if (!root)
			return;

		free(root->left);
		free(root->right);

		delete root;
	}
private:
	Dictionary<int> dictionary;
	Node * root;
};