#pragma once

#include "Board.h"
#include "../Double linked list/DLList.h"

class AStar
{
public:
	DLList<Cell*> pathFinder(Board& board, Cell* startCell, Cell* endCell) const;
};