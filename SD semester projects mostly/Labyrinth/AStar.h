#pragma once

#include "Board.h"
#include "../Double linked list/DLList.h"

class AStar
{
public:
	static DLList<Cell*> pathFinder(Cell* startCell, Cell* endCell);
private:
	static void calcCell(Cell* current, Cell* child, DLList<Cell*> & openList, Cell* endCell);
};