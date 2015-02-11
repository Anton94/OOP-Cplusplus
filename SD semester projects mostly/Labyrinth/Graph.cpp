#include "Graph.h"

Graph::Graph()
{

}



Graph::~Graph()
{
	free();
}

void Graph::free()
{
	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
	{
		delete (*iter);
	}
}