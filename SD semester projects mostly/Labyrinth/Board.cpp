#include <iostream>
#include "Board.h"


/// Returns the number of rows (number of vectors in the vector of vectors).

int Board::getRows() const
{
	return board.getSize();
}

/// Returns the number of cols (number of cells in the first vector in the vector of vectors(board with no vector is invalid board, but if its a 'thing' returns 0 cols)).

int Board::getCols() const
{
	if (getRows() <= 0)
		return 0;

	return board[0].getSize();
}

/// Prints the board symbols.

void Board::printBoard(std::ostream out) const
{
	int rows = getRows();
	int cols = getCols();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			out << board[i][j].getSymbol();
		}
		
		out << "\n";
	}
}

/// Returns a pointer to the cell, with the given coords. If the cell is outside the bounds of the map->returns NULL;

Cell* Board::getCellAt(int i, int j)
{
	// If the 'i' coordinate is valid one(otherwise it will return NULL ptr..), check the 'j' coord.
	Vector<Cell> * row = board.getAt(i);

	if (row)
		return row->getAt(j);
	else
		return NULL;
}