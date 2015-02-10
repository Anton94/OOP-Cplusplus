#include "AStar.h"

/// If there is no path, the returned path will be empty!

DLList<Cell*> AStar::pathFinder(Cell* startCell, Cell* endCell)
{
	DLList<Cell*> path;
	bool pathFound = false;

	Cell* currentCell = startCell;

	// Define the open and the close list.
	DLList<Cell*> openList;
	DLList<Cell*> closedList;
	DLList<Cell*>::Iterator i = openList.begin();
	DLList<Cell*>::Iterator iterHelper = openList.begin();

	// Add the start point to the open list.
	openList.push_back(startCell);
	startCell->setOpened(true);

	while (currentCell != endCell)
	{
		// Look for the smallest H value in the openList and make it the current point. The current is first one at the beginning. Iter helper is to delete the current from the opened list after that.
		for (i = openList.begin(), currentCell = (*i), iterHelper = i; i != openList.end(); ++i)
		{
			if ((*i)->getH() <= currentCell->getH())
			{
				currentCell = (*i);
				iterHelper = i;
			}
		}

		// Stop if we reached the end.
		if (currentCell == endCell)
		{
			pathFound = true;
			break;
		}

		// Remove the current cell from the openList.
		openList.removeAt(iterHelper);
		currentCell->setOpened(false);

		// Add the current cell to the closedList.
		closedList.push_back(currentCell);
		currentCell->setClosed(true);

		// Four direction....
		calcCell(currentCell, currentCell->getLeftCell(), openList, endCell);
		calcCell(currentCell, currentCell->getUpCell(), openList, endCell);
		calcCell(currentCell, currentCell->getRightCell(), openList, endCell);
		calcCell(currentCell, currentCell->getDownCell(), openList, endCell);
	}

	// Reset
	for (i = openList.begin(); i != openList.end(); ++i)
	{
		(*i)->setOpened(false);
	}
	for (i = closedList.begin(); i != closedList.end(); ++i)
	{
		(*i)->setClosed(false);
	}

	if (!pathFound)
		return path;

	// Path without the start and the end cells.
	// Removes the end cell...
	currentCell = currentCell->getParent();

	// Resolve the path starting from the end point
	while (currentCell && currentCell->getParent() && currentCell != startCell)
	{
		path.push_back(currentCell);
		currentCell = currentCell->getParent();
	}

	return path;
}


void AStar::calcCell(Cell* current, Cell* child, DLList<Cell*> & openList, Cell* endCell)
{
	// If it's closed or not walkable then pass
	if (child->getClosed() || !child->getWalkable())
	{
		return;
	}

	if (!child->getOpened())
	{
		// Add it to the openList with current point as parent
		openList.push_back(child);
		child->setOpened(true);

		// Compute it's g, h and f score
		child->setParent(current);
		child->computeH(endCell);
	}
}