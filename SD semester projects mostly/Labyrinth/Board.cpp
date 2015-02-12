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
	mapOfSpecialCells = new Graph();
}

Board::~Board()
{
	delete mapOfSpecialCells;
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

void Board::printDoorKeyPairs(std::ostream& out) const
{
	for (DLList<Pair<Cell*, Cell*>>::Iterator iter = const_cast<DLList<Pair<Cell*, Cell*>>&>(doorKeyPairs).begin(); iter != const_cast<DLList<Pair<Cell*, Cell*>>&>(doorKeyPairs).end(); ++iter)
	{
		std::cout << (((*iter).first == NULL) ? '*' : (*iter).first->getSymbol()) << (((*iter).second == NULL) ? '*' : (*iter).second->getSymbol()) << "\n";
	}

	//out << "\nPrint doors: \n";
	//doors.printIfNotNULL(out);
	//out << "\n";
	//out << "\nPrint keys: \n";
	//keys.printIfNotNULL(out);
	//out << "\n";
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

	Map_Char_pCell specialCells; 

	// Sets the cell symbols.
	initializeBoardCells(in, specialCells);

	// Makes pairs door->key. (sets also the maps with doors and keys...
	makeDoorKeyPairs(in, specialCells);

	generateMapOfSpecialCells();

	mapOfSpecialCells->print(std::cout);
}

/// For each cell in specialCells, starts BFS with no target cell, and if it goes through other special cell, adds the edge to the map of special cells.(graph).

void Board::generateMapOfSpecialCells()
{
	// Make BFS for the start cell and end cell.
	BFS(startCell);
	BFS(endCell);

	for (DLList<Pair<Cell*, Cell*>>::Iterator iter = doorKeyPairs.begin(); iter != doorKeyPairs.end(); ++iter)
	{
		// If there is NULL on the key/door, the BFS will return...
		BFS((*iter).first); // On the door.		
		BFS((*iter).second); // On the key. 
	}
}

/// Starts BFS with no target cell, and if it goes through other special cell, adds the edge to the map of special cells.(graph).

void Board::BFS(Cell * start)
{
	if (!start)
		return;

	Queue<Cell*> queue;
	DLList<Cell*> path;

	queue.enqueue(start);
	start->setVisited(true);

	while (!queue.isEmpty())
	{
		Cell* currentCell = queue.dequeue();

		path.push_back(currentCell);

		BFSAddNeighbour(start, currentCell, currentCell->getLeftCell(), queue);
		BFSAddNeighbour(start, currentCell, currentCell->getUpCell(), queue);
		BFSAddNeighbour(start, currentCell, currentCell->getRightCell(), queue);
		BFSAddNeighbour(start, currentCell, currentCell->getDownCell(), queue);
	}

	resetCells();
}



void Board::BFSAddNeighbour(Cell* start, Cell* current, Cell* neighbour, Queue<Cell*>& queue)
{
	// If the neighbour cell is outside of the map, or it`s wall, return...
	if (!neighbour || !neighbour->getWalkableWithoutWalls())
		return;



	// If the neighbour is not visited. 
	if (neighbour->getVisited() == false)
	{
		// If the neighbour cell is special one (door or key) we add it as a EDGE to the graph and we assume that it`s not walkable field.
		if (doors.getCellAt(neighbour->getSymbol()) || keys.getCellAt(neighbour->getSymbol()) || neighbour == startCell || neighbour == endCell)
		{
			DLList<Cell*> path;

			BFSResolveThaPath(current, neighbour, start, path);

			mapOfSpecialCells->insertEdge(start, neighbour, path);
		}
		else
		{
			queue.enqueue(neighbour);
			neighbour->setParent(current);
		}

		// Makr it as visited, so I don`t go there if there is other way to that cell...(if the cell is special one...).
		neighbour->setVisited(true);
	}
}

/// Gets the path by its parents...
/// Retursn the path from cell to cell, using the parent pointer. A save the path in the given one, so It dont make more copies... I Use current and neighbour so I dont add the neighbour because I don`t want to go throuh special cells, only paths without special cells.

void Board::BFSResolveThaPath(Cell* current, Cell* neighbour, Cell* start, DLList<Cell*> & path)
{
	// Adds the ending cell.
	path.push_front(neighbour);

	while (current && current->getParent() && current != start)
	{
		path.push_front(current);
		current = current->getParent();
	}

	// Adds the starting cell.
	path.push_front(start);
}

/// Goes through every cell and sets visited variable to false.

void Board::resetCells()
{
	int rows = getRows();
	int cols = getCols();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			board[i][j].setVisited(false);
			board[i][j].setParent(NULL);
		}
	}
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

void Board::initializeBoardCells(std::istream& in, Map_Char_pCell & specialCells)
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
				if (specialCells.getCellAt(c))
					throw "Invalid input data, more than one special symbol of one type!";
				else
					specialCells.setCellAt(c, &board[i][j]);
			}
		}
	}

	if (!startCell || !endCell)
		throw "Invalid input data, missing start/end point!";
}

/// Makes pairs from the input stream and the already saved special cells (dont have to go through the whole map and look for the cell with the wanted symbol).
/// If there is onle door with no key-> key is NULL ptr, if there is only key with no door-> door is null ptr.
/// the input stream is at the last new line from the board at this moment.

void Board::makeDoorKeyPairs(std::istream& in, Map_Char_pCell & specialCells)
{
	char c;
	Pair<Cell*, Cell*> currPair(NULL, NULL);

	while (in.get(c))
	{
		if (c != '\n')
		{
			// Door symbol is in the 'c'. If it`s white space, there is no door for the key. also sets the pointer in the map with doors.
			setPairValue(c, currPair.first, specialCells);
			doors.setCellAt(c, currPair.first);

			// Now gets the key symbol. If it`s white space, there is no key for the door. If the symbol is new line, or EOF or the two symbols are white space, throws exeption for wrong input.
			in.get(c);
			if (!in || c == '\n' || (currPair.first == NULL && c == ' '))
				throw "Invalid input data while reading the pairs of door and keys!";

			setPairValue(c, currPair.second, specialCells);
			keys.setCellAt(c, currPair.second);

			// Now adds the current  pair to the list of pairs.

			doorKeyPairs.push_back(currPair);
		}
	}
}

/// Checks if the symbol is white space and sets the pair value to NULL, otherwise sets it to the pointer to that cell.

void Board::setPairValue(char c, Cell*& pairvalue, Map_Char_pCell & specialCells) const
{
	if (c == ' ')
		pairvalue = NULL;
	else if (specialCells.getCellAt(c) == NULL)
		throw "Invalid input stream, can`t find the symbol of the pairs of door keys in the field!";
	else
		pairvalue = specialCells.getCellAt(c);
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

/// TO DO delete...

void Board::tempPath()
{
	DLList<Cell*> path = AStar::pathFinder(startCell, endCell, &Cell::getWalkableWithoutWallsAndDoors);


	if (path.isEmpty())
		std::cout << "NO PATH FOUND!" << std::endl;

	for (DLList<Cell*>::Iterator iter = path.begin(); iter != path.end(); ++iter)
	{
		(*iter)->setSymbol('+');
	}
}