#pragma once

#include "Cell.h"
#include "../Double linked list/DLList.h"
#include "Pair.h"


/*

	Graph node has pointer to the cell , which it represents, list with pairs(pair of pointer to other node and the path to that cell on the map).

	The graph has a list of roots...

	I keep and list with all ever created nodes, so I can delete them..
*/

class Graph
{
	struct Node
	{
		Cell* cell;
		DLList<Pair<Node*, DLList<Cell*>>> sons;

		Node(Cell * cell);
	};

	DLList<Node*> allNodes;
public:
	void insertEdge(Cell* source, Cell* dest, DLList<Cell*>& path);
	void print(std::ostream& out); // Prints all edges between cells and the paths...
	~Graph();
private:
	Graph::Node* findNode(const Cell* cell); // Finds the node, which represents the given cell... if there is no, returns NULL... it returns pointer to node, so it`s not very constant function.
	Graph::Node* getNode(Cell* cell);
	void printNode(std::ostream& out, Node* node);
private:
	void free();
};