#pragma once

class Board;

#include <iostream>
#include "Cell.h"
#include "../Vector/Vector.h"
#include "../Double linked list/DLList.h"
#include "Pair.h"
#include "AStar.h"

//#define NUMBER_OF_ELEMENTS_IN_CHAR std::pow(2, sizeof(char) * 8) / 2

// The valid symbols for this task are 128.
#define NUMBER_OF_ELEMENTS_IN_CHAR 256

class Board
{
	friend class Cell;

	struct BoardSymbols
	{
		BoardSymbols();
		char walkable;
		char wall;
		char start;
		char end;
	};
public:
	Board();
	int getRows() const;
	int getCols() const;
	void deserialize(std::istream& in);
	void printBoard(std::ostream& out) const; 
	void printDoorKeyPairs(std::ostream& out) const;
	void tempPath();
private:
	Cell* getCellAt(int i, int j);
	void getDimensions(std::istream& in, int& rows, int& cols) const;
	void allocateBoard(int rows, int cols);
	void initializeBoardCells(std::istream& in, Vector<Cell*>& specialCells);
	void makeDoorKeyPairs(std::istream& in, Vector<Cell*> & specialCells);
	void setPairValue(char c, Cell*& pairvalue, Vector<Cell*> & specialCells) const;
private:
	BoardSymbols boardSymbols;
	Vector<Vector<Cell>> board;
	Cell* startCell;
	Cell* endCell;
	DLList<Pair<Cell*, Cell*>> doorKeyPairs;
private:
	Board(const Board& board);
	Board& operator=(const Board& board);
};