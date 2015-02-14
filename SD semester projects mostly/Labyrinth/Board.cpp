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

	// Makes a graph with edges paths between special cells, if there are any...
	generateMapOfSpecialCells();

	///
	/* testing stuff */
	///

	Map_Char_pCell bannedCells;
	
	
	/*bannedCells.setCellAt('%', keys.getCellAt('%'));
	bannedCells.setCellAt('2', doors.getCellAt('2'));
	bannedCells.setCellAt(endCell->getSymbol(), endCell);*/


	DLList<DLList<Cell*>> allPaths = mapOfSpecialCells->AllPathsBetweenCellsWithBannedCells(startCell, endCell, bannedCells);

	for (DLList<DLList<Cell*>>::Iterator iter = allPaths.begin(); iter != allPaths.end(); ++iter)
	{
		printPath(*iter);
	}

	mapOfSpecialCells->print(std::cout);

	///
	/* end testing stuff */
	///
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

			// Now adds the key for the door, if the door is not space. On the position of the door, sets the pointer to the key cell!
			if (currPair.first)
				keyForDoor.setCellAt(currPair.first->getSymbol(), currPair.second);

			// Now adds the door for the key, if the key is not space. On the position of the door, sets the pointer to the door cell!
			if (currPair.second)
				doorForKey.setCellAt(currPair.second->getSymbol(), currPair.first);
		}

	}

	if (specialCells.hasElementDiferentThan(NULL))
		throw "Invalid input data, not every special cell has description.";

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


	specialCells.setCellAt(c, NULL); // makes the symbol in special cells to NULL, used one ...
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

/// Starts BFS with no target cell, and if it goes through other special cell, adds the edge to the map of special cells.(graph).

void Board::BFS(Cell * start)
{
	if (!start)
		return;

	Queue<Cell*> queue;

	queue.enqueue(start);
	start->setVisited(true);

	while (!queue.isEmpty())
	{
		Cell* currentCell = queue.dequeue();

		BFSAddNeighbour(start, currentCell, currentCell->getLeftCell(), queue);
		BFSAddNeighbour(start, currentCell, currentCell->getUpCell(), queue);
		BFSAddNeighbour(start, currentCell, currentCell->getRightCell(), queue);
		BFSAddNeighbour(start, currentCell, currentCell->getDownCell(), queue);
	}

	BFSResetCellsNeededInfo();
}

/// Checks if the neihbour is special cell, and if it`s not visited yet, if so, makes the path from the start (given start cell) to that cell, and addes a edge in the graph(mapOfSpecialCells)

void Board::BFSAddNeighbour(Cell* start, Cell* current, Cell* neighbour, Queue<Cell*>& queue)
{
	// If the neighbour cell is outside of the map, or it`s wall, return...
	if (!neighbour || !neighbour->getWalkableWithoutWalls())
		return;

	// If the neighbour is not visited. 
	if (neighbour->getVisited() == false)
	{
		// If the neighbour cell is special one (door or key) we add it as a EDGE to the graph and we assume that it`s not walkable field.
		if (isSpecialCell(neighbour))
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

		// Mark it as visited, so I don`t go there if there is other way to that cell...(if the cell is special one...).
		neighbour->setVisited(true);
	}
}

/// Gets the path by its parents...
/// Retursn the path from cell to cell, using the parent pointer. A save the path in the given one, so It dont make more copies... I Use current and neighbour so I dont add the neighbour because I don`t want to go throuh special cells, only paths without special cells.

void Board::BFSResolveThaPath(Cell* current, Cell* neighbour, Cell* start, DLList<Cell*> & path)
{
	//// Adds the ending cell.
	//path.push_front(neighbour);

	while (current && current->getParent() && current != start)
	{
		path.push_front(current);
		current = current->getParent();
	}

	// Adds the starting cell.
	path.push_front(start);
}

/// Goes through every cell and sets visited variable to false.

void Board::BFSResetCellsNeededInfo()
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

char * Board::findPathFromStartToEnd()
{	
	// This path contains only the special cells.
	DLList<Cell*> pathOfSpecialCells = findPath(startCell, endCell);

	// Extract the full path from the special cells (as direct paths between them). Returns it.
	DLList<Cell* > fullPath = mapOfSpecialCells->getFullPathFromSpecialCells(pathOfSpecialCells);

	return convertCellsToDirectionSymbols(fullPath);
}

/// Converst a list of cells to direction symbols. 

char * Board::convertCellsToDirectionSymbols(DLList<Cell*> & path)
{
	char * stringPath = new char[path.getSize()]; // from start to the end, but not start, so getSize() - 1 + 1('\0');
	char * pStringPath = stringPath;
	Cell* prevCell = path.peek_front();

	// ++path to skip the first symbol.
	for (DLList<Cell*>::Iterator iterCell = ++path.begin(); iterCell != path.end(); ++iterCell)
	{
	//	(*iterCell)->setSymbol('+');
		*pStringPath = Directions::getDirectionToCell(prevCell, *iterCell);
		++pStringPath;
		prevCell = *iterCell;
	}

	*pStringPath = '\0';

	return stringPath;
}

/*
	Gets all posible variants from start cell, to the end cell. If in the path has the keys for the doors, the path is valid one. This algorithm is not good for some cases...
	Returns only the special cells, not whole paths, for faster iteration on the paths.

	returns first found... (if someday I can make working one...)
*/

DLList<Cell*> Board::findPath(Cell * start, Cell* end)
{
	// Gets all paths from the start to the end cell.
	DLList<DLList<Cell*>> allPaths = mapOfSpecialCells->AllPathsBetweenCells(start, end);

	// Goes through every path and checks if the path contains the keys, before the door.
	// Makes a map with the found keys to this moment.
	for (DLList<DLList<Cell*>>::Iterator currentPath = allPaths.begin(); currentPath != allPaths.end(); ++currentPath)
	{
		// Map with the found keys to this moment.
		Map_Char_pCell foundKeys;
		bool hasPath = true;

		// Goes through every cell of the map.
		for (DLList<Cell*>::Iterator currentCell = (*currentPath).begin(); currentCell != (*currentPath).end(); ++currentCell)
		{
			char currentCellSymbol = (*currentCell)->getSymbol();
			
			// If the current symbol is key, adds it to the map of found keys.
			if (keys.getCellAt(currentCellSymbol))
			{
				foundKeys.setCellAt(currentCellSymbol, *currentCell);
			}
			// If the cell is a door and the key for that door is NOT already in the path , this path is wrong and sets the bool field hasPath to false, breaks the cycle...
			else if (doors.getCellAt(currentCellSymbol))
			{
				// If the key for the door is not in the path.
				if (!foundKeys.getCellAt(getKeyForTheDoor(*currentCell)->getSymbol()))
				{
					hasPath = false;
					break;
				}
			}
		}

		// If the current one.
		if (hasPath)
			return *currentPath;
	}

	// If it goes to here, that means that it can`t find the path.
	throw "Path not found!";
}

/// Returns the key needed to open the given door.

Cell* Board::getKeyForTheDoor(Cell* door)
{
	return keyForDoor.getCellAt(door->getSymbol());
}

/// Checks if the given cell is special one(door, key, start , end).

bool Board::isSpecialCell(Cell * cell)
{
	if (doors.getCellAt(cell->getSymbol()) || keys.getCellAt(cell->getSymbol()) || cell == startCell || cell == endCell)
	{
		return true;
	}

	return false;
}































/// TO DO : DELETE THIS ONE.
/// Goest through every cell and prints it.

void printPath(DLList<Cell*> & path)
{
	if (path.isEmpty())
		return;

	std::cout << path.peek_front()->getSymbol() << " to " << path.peek_back()->getSymbol() << ": ";

	for (DLList<Cell*>::Iterator iter = path.begin(); iter != path.end(); ++iter)
	{
		if ((*iter) != NULL)
			//std::cout << "(" << (*iter)->getIndexRow() << ", " << (*iter)->getIndexCol() << ") ";
			std::cout << (*iter)->getSymbol() << " ";
	}

	std::cout << "\n";
}



//
///// TO DO delete...
//
//void Board::tempPath()
//{
//	DLList<Cell*> path = AStar::pathFinder(startCell, endCell, &Cell::getWalkableWithoutWallsAndDoors);
//
//
//	if (path.isEmpty())
//		std::cout << "NO PATH FOUND!" << std::endl;
//
//	for (DLList<Cell*>::Iterator iter = path.begin(); iter != path.end(); ++iter)
//	{
//		(*iter)->setSymbol('+');
//	}
//}


/// TO DO : DELETES IT




///// Checks if the key is already in the path.
//
//bool Board::cellIsAlreadyInThePath(Cell* cell, DLList<Cell*> & path)
//{
//	for (DLList<Cell*>::Iterator iter = path.begin(); iter != path.end(); ++iter)
//	{
//		if ((*iter) == cell)
//			return true;
//	}
//
//	return false;
//}


//DLList<Cell*> Board::findPath(Cell * start, Cell* end, DLList<Cell*> & pathToThisMoment, Map_Char_pCell & bannedCells)
//{
//	std::cout << "Trying to find a path between : " << start->getSymbol() << " and " << end->getSymbol() << std::endl;
//	system("Pause");
//
//	// TO DO: returns only cells.
//	if (mapOfSpecialCells->getPathBetweenTwoNodes(start, end).getSize() > 1)
//	{
//		DLList<Cell*> path;
//		path.push_back(start);
//		path.push_back(end);
//		return path;
//	}
//
//	// Get all posible variants from the start cell to the end cell.
//	DLList<DLList<Cell*>> allPaths = mapOfSpecialCells->AllPathsBetweenCells(start, end, bannedCells);
//
//	// Check each one if it contains doors, without the keys have been taken yet.
//	for (DLList<DLList<Cell*>>::Iterator currentPath = allPaths.begin(); currentPath != allPaths.end(); ++currentPath)
//	{
//		try
//		{
//			// Adds to the banned cells all doors. (new list, if there is no path from first given one, can searche on second on so on... TO DO: other solution maybe, too many copies..
//			Map_Char_pCell currBanedCells = bannedCells;
//			addToBannedCellsIfDoor(*currentPath, currBanedCells);
//
//			// The clean path.
//			DLList<Cell*> path;
//
//			//  Goes through every cell of the path and checks if there is a door, and no key taken for it.
//			DLList<Cell*>::Iterator nextIterOnCurrentPath = (*currentPath).begin();
//			DLList<Cell*>::Iterator iterOnCurrentPath = (*currentPath).begin();
//			++nextIterOnCurrentPath;
//			
//			while (nextIterOnCurrentPath != (*currentPath).end())
//			{
//				// If the cell is a door.
//				if (doors.getCellAt((*nextIterOnCurrentPath)->getSymbol()))
//				{
//					// If there is no key for that door.
//					if (!keyForDoor.getCellAt((*nextIterOnCurrentPath)->getSymbol()))
//					{
//						throw "Cant find the path";
//					}
//			
//					// If the key is not already in the path. Searches for the cell before the door, to the key for that door.  O(broq na kletkite v putq, LOSHO!)
//					if (!cellIsAlreadyInThePath(keyForDoor.getCellAt((*nextIterOnCurrentPath)->getSymbol()), pathToThisMoment))
//					{
//						//// deletes the symbol before the door.
//						//path.pop_back();
//			
//						DLList<Cell*> pathToTheKey;
//						// If there is no path between the start and end point it will throw exeption.
//						pathToTheKey = findPath(*iterOnCurrentPath, keyForDoor.getCellAt((*nextIterOnCurrentPath)->getSymbol()), path, bannedCells);
//			
//						//// Pops the start point, I dont go there.
//						//pathToTheKey.pop_front();
//			
//						//// Adds the path to the key to the current one, and adds the reversed path so it can go back...
//						//path += pathToTheKey;
//			
//						//pathToTheKey.pop_back();
//						path.push_back_reversed_list(pathToTheKey);
//					}
//				}
//				currBanedCells.setCellAt(doors.getCellAt((*nextIterOnCurrentPath)->getSymbol())->getSymbol(), doors.getCellAt((*nextIterOnCurrentPath)->getSymbol()));
//			
//				//	if (path.peek_front() != *nextIterOnCurrentPath)
//				path.push_back(*nextIterOnCurrentPath);
//			
//				printPath(path);
//			
//			
//				++iterOnCurrentPath;
//				++nextIterOnCurrentPath;
//			}
//			
//			return path;
//		}
//		catch (const char * msg)
//		{
//			// NO PATH FOUND
//		}
//	}
//
//
//	throw "Cant find the path!";
//}
//
//
//void Board::addToBannedCellsIfDoor(DLList<Cell*>& path, Map_Char_pCell& bannedCells)
//{
//	for (DLList<Cell*>::Iterator iter = path.begin(); iter != path.end(); ++iter)
//	{
//		if (doors.getCellAt((*iter)->getSymbol()))
//			bannedCells.setCellAt((*iter)->getSymbol(), doors.getCellAt((*iter)->getSymbol()));
//	}
//}


//DLList<Cell*> path;
//path.push_back(start);
//
//bool hasPath = false;
//
//// Get all posible variants from the start cell to the end cell.
//DLList<DLList<Cell*>> allPaths = mapOfSpecialCells->AllPathsBetweenCells(start, end);
//
//// Check each one if it contains doors, without the keys have been taken yet.
//for (DLList<DLList<Cell*>>::Iterator currenPath = allPaths.begin(); currenPath != allPaths.end(); ++currenPath)
//{
//	/*	std::cout << "Maybe path: ";
//	printPath(*currenPath);*/
//	try
//	{
//		// Goes through every cell of the path and checks if there is a door, and no key taken for it.
//		DLList<Cell*>::Iterator nextIterOnCurrentPath = (*currenPath).begin();
//		DLList<Cell*>::Iterator iterOnCurrentPath = (*currenPath).begin();
//		++nextIterOnCurrentPath;
//
//		Cell * startingPoint = start;
//
//
//		while (nextIterOnCurrentPath != (*currenPath).end())
//		{
//
//			// If the cell is a door and the key for that door.
//			if (doors.getCellAt((*nextIterOnCurrentPath)->getSymbol()))
//			{
//				// If there is no key for that door.
//				if (!keyForDoor.getCellAt((*nextIterOnCurrentPath)->getSymbol()))
//				{
//					throw "Cant find the path";
//				}
//
//				// If the key is not already in the path. Searches for the cell before the door, to the key for that door.  O(broq na kletkite v putq, LOSHO!)
//				if (!cellIsAlreadyInThePath((*nextIterOnCurrentPath), pathToThisMoment))
//				{
//					//// deletes the symbol before the door.
//					//path.pop_back();
//
//
//					DLList<Cell*> pathToTheKey;
//					// If there is no path between the start and end point it will throw exeption.
//					pathToTheKey = findPath(*nextIterOnCurrentPath, keyForDoor.getCellAt((*nextIterOnCurrentPath)->getSymbol()), path);
//
//					// Pops the start point, I dont go there.
//					pathToTheKey.pop_front();
//
//					// Adds the path to the key to the current one, and adds the reversed path so it can go back...
//					path += pathToTheKey;
//
//					//pathToTheKey.pop_back();
//					path.push_back_reversed_list(pathToTheKey);
//				}
//			}
//
//			//				if (path.peek_front() != *nextIterOnCurrentPath)
//			path.push_back(*nextIterOnCurrentPath);
//
//			//	printPath(path);
//
//
//			++iterOnCurrentPath;
//			++nextIterOnCurrentPath;
//		}
//
//		hasPath = true;
//		break;
//	}
//	catch (const char* msg)
//	{
//		// invalid path...
//	}
//}
//
//if (!hasPath)
//{
//	throw "Cant find the path!";
//}
//
//return path;



	//			DLList<Cell*> pathToThatKey;

	//			// Goes through all combinations of paths to find one. Recursive finds the path and gets the needed keys for to get the needed one.
	//			for (DLList<DLList<Cell*>>::Iterator currPathToThatDoor = allPathsToThatKey.begin(); currPathToThatDoor != allPathsToThatKey.end(); ++currPathToThatDoor)
	//			{
	//				try
	//				{
	//					// If there is no path between the start and end point(no key for some of the doors) it will throw exeption.
	//					pathToThatKey = findPath(*currPathToThatDoor);
	//					pathToThatDoorFound = true;
	//					break;
	//				}
	//				catch (const char * msg)
	//				{
	//					// invalid path...
	//				}
	//			}

	//			if (!pathToThatDoorFound)
	//				throw "Can`t find a path to that door(cant found the key for the door)";


	//			// Adds the path to that door to the aready existing one.
	//			pathWithTheKeys += pathToThatKey;

	//			//// Make the current cell as the key.
	//			//currentCell = keyForThatDoor;





	//DLList<Cell*> pathWithTheKeys;

	//// Goes throuh every cell in the path. Uses 2 iterator, current position and next position.
	//Cell* currentCell = path.peek_front();
	//DLList<Cell*>::Iterator nextCell = path.begin();
	//++nextCell;

	//while (nextCell != path.end())
	//{
	//	// If the nextCell is a door. Finds a path, from the current cell, to the key to that door. 
	//	if (doors.getCellAt((*nextCell)->getSymbol()) != NULL)
	//	{			
	//		// Get all posible variant from the cell, to that door key...		
	//		Cell* keyForThatDoor = getKeyForTheDoor(*nextCell);
	//	
	//		// Checks if the key is already in the path, so dont search it again.
	//		if (!cellIsAlreadyInThePath(keyForThatDoor, path))
	//		{
	//			DLList<DLList<Cell*>> allPathsToThatKey = mapOfSpecialCells->AllPathsBetweenCells(currentCell, keyForThatDoor);

	//			bool pathToThatDoorFound = false;
	//			DLList<Cell*> pathToThatKey;

	//			// Goes through all combinations of paths to find one. Recursive finds the path and gets the needed keys for to get the needed one.
	//			for (DLList<DLList<Cell*>>::Iterator currPathToThatDoor = allPathsToThatKey.begin(); currPathToThatDoor != allPathsToThatKey.end(); ++currPathToThatDoor)
	//			{
	//				try
	//				{
	//					// If there is no path between the start and end point(no key for some of the doors) it will throw exeption.
	//					pathToThatKey = findPath(*currPathToThatDoor);
	//					pathToThatDoorFound = true;
	//					break;
	//				}
	//				catch (const char * msg)
	//				{
	//					// invalid path...
	//				}
	//			}

	//			if (!pathToThatDoorFound)
	//				throw "Can`t find a path to that door(cant found the key for the door)";


	//			// Adds the path to that door to the aready existing one.
	//			pathWithTheKeys += pathToThatKey;

	//			//// Make the current cell as the key.
	//			//currentCell = keyForThatDoor;
	//		}			
	//	}
	//	else
	//	{
	//		pathWithTheKeys.push_back(*nextCell);
	//	}
	//	currentCell = (*nextCell);
	//	++nextCell;
	//}

	//return pathWithTheKeys;
