#include <iostream>
#include "Board.h"

/// Default values for the board symbols.

Board::BoardSymbols::BoardSymbols()
{
	walkable = ' ';
	wall = '#';
	start = 'S';
	end = 'E';
}

/// Default constructor. Sets the start and end point to NULL.

Board::Board()
{
	startCell = endCell = NULL;
}

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

void Board::printBoard(std::ostream& out) const
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

/// Gets the board symbols and the pairs key->door from the input stream. If the input stream is wrong->throws exeption.
/// Makes vector with (128) elements and makes all pointers NULL. Binary search tree for alternative, but here insert and find are constant, so I wanted to try it out. Also I may use and hash MAP .
/// Every speacil cell (key or door) has constant search and constant add in the vector of pointers to cells.

void Board::deserialize(std::istream& in)
{
	// Get the rows, cols count.
	int rows = 0, cols = 0;
	getDimensions(in, rows, cols);

	// Allocate the memory for the board.
	allocateBoard(rows, cols);

	Vector<Cell*> specialCells(NUMBER_OF_ELEMENTS_IN_CHAR, NULL); 

	// Sets the cell symbols.
	initializeBoardCells(in, specialCells);

	// Makes pairs door->key.
	makeDoorKeyPairs(in, specialCells);

	/**/
	
	/*for (DLList<Pair<Cell*, Cell*>>::Iterator iter = doorKeyPairs.begin(); iter != doorKeyPairs.end(); ++iter)
	{
		std::cout << (((*iter).first == NULL) ? '*' : (*iter).first->getSymbol()) << (((*iter).second == NULL) ? '*' : (*iter).second->getSymbol()) << "\n";
	}*/

	/**/
}

/// Check if the board is with valud rows and cols (every row has same number of cols..). If the input stream is wrong->throws exeption.
/// Get also the number of special symbols(doors and keys).


void Board::getDimensions(std::istream& in, int& rows, int& cols) const
{
	in.clear();
	in.seekg(0, std::ios::beg);

	char c = 0;
	int counter = 0;

	// Find the number of columns in the board.
	while (in.get(c) && c != '\n')
		++cols;

	// Find the number of rows and if all of them have same number of cols.
	if (cols > 0)
	{
		++rows; // at leas one row was read from the file

		while (in.get(c))
		{
			if (c == '\n')
			{
				if (counter == 0)
					break;

				// the number of columns on each line must be the same
				if (cols != counter)
					throw "Invalid number of cols in the board!";

				++rows;
				counter = 0;
			}
			else
			{
				++counter;
			}
		}

		// The last row of the labyrinth may or may not be followed by a blank line (symbols and EOF..)
		if (c != '\n')
			++rows;
	}
	// No input data...
	else
	{
		throw "Invalid input file, no board to read!";
	}
}

/// Allocate the memory for the board. If the values are invalid->throws exeption.

void Board::allocateBoard(int rows, int cols)
{
	// Free the board to this moment. If there was other allocation, the resize will copy the other once when resizing the vector, we don`t need that, so I set it to 0 and then to the new counts..)
	board.resize(0);

	board.resize(rows);
	for (int i = 0; i < rows; ++i)
		board[i].resize(cols);
}

/// Initialize the cells. Set their indexes, symbol and owner.
/// NOTE: it will get rows * cols symbols from the istream and if the new lines are incorrect wont throw exeption! Only if there are less symbols (without new lines).
/// Checks if there are valid start/end cells, otherwise throws exeption.

void Board::initializeBoardCells(std::istream& in, Vector<Cell*> & specialCells)
{
	// Start from the beginning of the file.
	in.clear();
	in.seekg(0, std::ios::beg);

	int rows = getRows();
	int cols = getCols();
	char c;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			// Skips new line(s).
			do
			{
				in.get(c);
				if (!in)
					throw "Invalid input data for the point in the board!";
			} while (in && c == '\n');

			board[i][j].setIndexes(i, j); // the owner is NULL (in the case when the initialize is after the allocation) so it wont make check for the indexes.
			board[i][j].setSymbol(c);
			board[i][j].setOwner(this);

			if (c == boardSymbols.start)
			{
				if (startCell)
					throw "Invalid input data, more than one start point!";
				else
					startCell = &board[i][j];
			}
			else if (c == boardSymbols.end)
			{
				if (endCell)
					throw "Invalid input data, more than one end point!";
				else
					endCell = &board[i][j];
			}
			else if (c != boardSymbols.walkable && c != boardSymbols.wall) // it`s some kind of special symbol (door or key).
			{
				if (specialCells[c])
					throw "Invalid input data, more than one special symbol of one type!";
				else
					specialCells[c] = &board[i][j];
			}
		}
	}

	if (!startCell || !endCell)
		throw "Invalid input data, missing start/end point!";
}

/// Makes pairs from the input stream and the already saved special cells (dont have to go through the whole map and look for the cell with the wanted symbol).
/// If there is onle door with no key-> key is NULL ptr, if there is only key with no door-> door is null ptr.
/// the input stream is at the last new line from the board at this moment.

void Board::makeDoorKeyPairs(std::istream& in, Vector<Cell*> & specialCells)
{
	char c;
	Pair<Cell*, Cell*> currPair(NULL, NULL);

	while (in.get(c))
	{
		if (c != '\n')
		{
			// Door symbol is in the 'c'. If it`s white space, there is no door for the key.
			setPairValue(c, currPair.first, specialCells);

			// Now gets the key symbol. If it`s white space, there is no key for the door. If the symbol is new line, or EOF or the two symbols are white space, throws exeption for wrong input.
			in.get(c);
			if (!in || c == '\n' || (currPair.first == NULL && c == ' '))
				throw "Invalid input data while reading the pairs of door and keys!";

			setPairValue(c, currPair.second, specialCells);

			// Now adds the current  pair to the list of pairs.

			doorKeyPairs.push_back(currPair);
		}
	}
}

/// Checks if the symbol is white space and sets the pair value to NULL, otherwise sets it to the pointer to that cell.

void Board::setPairValue(char c, Cell*& pairvalue, Vector<Cell*> & specialCells) const
{
	if (c == ' ')
		pairvalue = NULL;
	else if (specialCells[c] == NULL)
		throw "Invalid input stream, can`t find the symbol of the pairs of door keys in the field!";
	else
		pairvalue = specialCells[c];
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