#pragma once

class Board;

#include <iostream>
#include "Cell.h"
#include "../Vector/Vector.h"
#include "../Double linked list/DLList.h"
#include "../Queue with one link/Queue.h"
#include "Pair.h"
#include "AStar.h"
#include "Map_Char_pCell.h"
#include "Graph.h"
#include "Directions.h" 
#include "String.h"


class Board
{
	friend class Cell;
	friend class Graph;

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
	void printBoard(std::ostream& out) const; 
	void printDoorKeyPairs(std::ostream& out) const;
	void clear();
	void freeAllPathStrings();
	void deserialize(std::istream& in);
	void findPathFromStartToEnd();
	String generateTheWholePath();
	~Board();
private:
	DLList<Cell*> findPath(Cell * startCell, Cell* endCell);
	void convertCellsToDirectionSymbols(DLList<Cell*> & path);
	Cell* getKeyForTheDoor(Cell* door);
	bool isSpecialCell(Cell * cell);
	Cell* getCellAt(int i, int j);
	void getDimensions(std::istream& in, int& rows, int& cols) const;
	void allocateBoard(int rows, int cols);
	void initializeBoardCells(std::istream& in, Map_Char_pCell& specialCells);
	void makeDoorKeyPairs(std::istream& in, Map_Char_pCell & specialCells);
	void setPairValue(char c, Cell*& pairvalue, Map_Char_pCell & specialCells) const;
	void generateMapOfSpecialCells();
	void BFS(Cell * start);
	void BFSAddNeighbour(Cell* start, Cell* current, Cell* neighbour, Queue<Cell*>& queue);
	void BFSResolveThaPath(Cell* current, Cell* neighbour, Cell* start, DLList<Cell*> & path);
	void BFSResetCellsNeededInfo();
	void clearMaps();
private:
	BoardSymbols boardSymbols;
	Vector<Vector<Cell>> board;
	Cell* startCell;
	Cell* endCell;
	DLList<Pair<Cell*, Cell*>> doorKeyPairs;
	Map_Char_pCell keyForDoor;
	Map_Char_pCell doorForKey;
	Map_Char_pCell doors;
	Map_Char_pCell keys;
	DLList<char*> allPathsInStrings;
	int allPathsLength;
	Graph * mapOfSpecialCells;
private:
	Board(const Board& board);
	Board& operator=(const Board& board);
};
void printPath(DLList<Cell*> & path);