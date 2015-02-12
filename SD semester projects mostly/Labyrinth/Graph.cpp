#include "Graph.h"

Graph::Node::Node(Cell * cell)
{
	this->cell = cell;
}

Graph::~Graph()
{
	free();
}

/// Inserts Edge between two cells in the graph.
/// Checks if the source cell is already in the graph and get it`s pointer to that NODE, if it`s not in the graph, adds it in the list of nodes.
/// Also for the dest cell.
/// Adds dest cell and path in the 'sons' of source NODE.

void Graph::insertEdge(Cell* source, Cell* dest, DLList<Cell*>& path)
{
	// Get the nodes, which contains the needed cells..
	Node * sourceNode = getNode(source);
	Node * destNode = getNode(dest);

	// Make the connection between the source and dest node, e.g. push the destNode (and it`s path to the cell) to the sons of source node.
	sourceNode->sons.push_back(Pair<Node*, DLList<Cell*>>(destNode, path));
}

// Prints all edges between cells and the paths...

void Graph::print(std::ostream& out)
{
	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
	{
		printNode(out, *iter);
		out << "\n";
	}
}

/// Prints the cell info and it`s sons, so the edge between the given cell(node*) and the sons of that node...

void Graph::printNode(std::ostream& out, Node* node)
{
	for (DLList<Pair<Node*, DLList<Cell*>>>::Iterator iter = node->sons.begin(); iter != node->sons.end(); ++iter)
	{
		out << node->cell->getSymbol() << " -> " << (*iter).first->cell->getSymbol() << " path: ";
		for (DLList<Cell*>::Iterator pathIter = (*iter).second.begin(); pathIter != (*iter).second.end(); ++pathIter)
		{
			out << "(" << (*pathIter)->getIndexRow() << ", " << (*pathIter)->getIndexCol() << ") ";
		}
		out << "\n";
	}
}

// If there is no node, representing the given cell, creates the node and pushes it to the list of allNodes, returns the new node, otherwise (if there is- returns the found one).

Graph::Node * Graph::getNode(Cell* cell)
{
	Node * node = findNode(cell);

	if (!node)
	{
		node = new Node(cell);
		allNodes.push_back(node);
	}

	return node;
}

/// Search for a node with the given cell(first one if ever there are more than one...). If no matches, returns NULL; Check if the pointer addresses are the same...
/// O(n) n- number of nodes... 

Graph::Node * Graph::findNode(const Cell * cell)
{
	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
	{
		if ((*iter)->cell == cell)
			return (*iter);
	}

	return NULL;
}

/// Goes through every node and deletes it.

void Graph::free()
{
	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
	{
		delete (*iter);
	}
}