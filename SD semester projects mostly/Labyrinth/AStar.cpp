#include "AStar.h"

/// If there is no path, the returned path will be empty!

DLList<Cell*> AStar::pathFinder(Board& board, Cell* startCell, Cell* endCell) const
{
	DLList<Cell*> path;

	Cell* currentCell;
	Cell* childCell;

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
			break;
		}

		// Remove the current cell from the openList.
		openList.removeAt(iterHelper);
		currentCell->setOpened(false);

		// Add the current cell to the closedList.
		closedList.push_back(currentCell);
		currentCell->setClosed(true);

		// Get all current's adjacent walkable points
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				// If it's current point then pass
				if (x == 0 && y == 0)
				{
					continue;
				}

				// Get this point
				child = getPoint(current->getX() + x, current->getY() + y);

				// If it's closed or not walkable then pass
				if (child->closed || !child->walkable)
				{
					continue;
				}

				// If we are at a corner
				if (x != 0 && y != 0)
				{
					// if the next horizontal point is not walkable or in the closed list then pass
					if (!pointIsWalkable(current->getX(), current->getY() + y) || getPoint(current->getX(), current->getY() + y)->closed)
					{
						continue;
					}
					// if the next vertical point is not walkable or in the closed list then pass
					if (!pointIsWalkable(current->getX() + x, current->getY()) || getPoint(current->getX() + x, current->getY())->closed)
					{
						continue;
					}
				}

				// If it's already in the openList
				if (child->opened)
				{
					// If it has a wroste g score than the one that pass through the current point
					// then its path is improved when it's parent is the current point
					if (child->getGScore() > child->getGScore(current))
					{
						// Change its parent and g score
						child->setParent(current);
						child->computeScores(end);
					}
				}
				else
				{
					// Add it to the openList with current point as parent
					openList.push_back(child);
					child->opened = true;

					// Compute it's g, h and f score
					child->setParent(current);
					child->computeScores(end);
				}
			}
		}
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

	// Resolve the path starting from the end point
	while (currentCell->getParent() && currentCell != startCell)
	{
		path.push_back(currentCell);
		currentCell = currentCell->getParent();
	}


}