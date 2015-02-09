#pragma once

class Board;

#include <iostream>
#include "Cell.h"
#include "../Vector/Vector.h"


class Board
{
	friend class Cell;
public:
	int getRows() const;
	int getCols() const;
	void printBoard(std::ostream) const;
private:
	Cell* getCellAt(int i, int j);
private:
	Vector<Vector<Cell>> board;
};