#pragma once

class Graph;

#include "Cell.h"
#include "../Double linked list/DLList.h"
#include "Pair.h"
#include "Map_Char_pCell.h"


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
		bool visited;
		Node * parent;

		int code;

		Node(Cell * cell);
	};

	
	DLList<Node*> allNodes;
public:
	void insertEdge(Cell* source, Cell* dest, DLList<Cell*>& path);
	void print(std::ostream& out); // Prints all edges between cells and the paths...
	DLList<DLList<Cell*>> AllPathsBetweenCells(Cell* start, Cell* end);
	DLList<DLList<Cell*>> AllPathsBetweenCellsWithBannedCells(Cell* start, Cell* end, Map_Char_pCell & bannedCells);
	DLList<Cell*> Graph::getFullPathFromSpecialCells(DLList<Cell*> & path);
	~Graph();
private:	
	void DFSPathsBetweenCells(Node* startNode, Node* endNode, DLList<Cell*> & pathToThatCell, DLList<Cell*> currPath, DLList<DLList<Cell*>>& allPaths, Map_Char_pCell & bannedCells);	
	Graph::Node* findNode(const Cell* cell); // Finds the node, which represents the given cell... if there is no, returns NULL... it returns pointer to node, so it`s not very constant function.
	Graph::Node* getNode(Cell* cell);
	void printNode(std::ostream& out, Node* node);
	DLList<Cell*> getDirectPathBetweenTwoNodes(Node * parent, Node * child);
private:
	void free();
};