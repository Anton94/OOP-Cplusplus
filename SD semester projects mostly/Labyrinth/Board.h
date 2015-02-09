#pragma once

class Board;

#include <iostream>
#include "Cell.h"
#include "../Vector/Vector.h"


class Board
{
	friend class Cell;

	struct BoardSymbols
	{
		BoardSymbols();
		char walkable;
		char start;
		char end;
	};
public:
	Board();
	int getRows() const;
	int getCols() const;
	void deserialize(std::istream& in);
	void printBoard(std::ostream& out) const;
private:
	Cell* getCellAt(int i, int j);
	void getDementions(std::istream& in, int& rows, int& cols) const;
	void allocateBoard(int rows, int cols);
	void initializeBoardCells(std::istream& in);
private:
	BoardSymbols boardSymbols;
	Vector<Vector<Cell>> board;
	Cell* startCell;
	Cell* endCell;
private:
	Board(const Board& board);
	Board& operator=(const Board& board);
};