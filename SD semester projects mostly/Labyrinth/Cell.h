#pragma once

class Cell;


#include "Board.h"
#include "Map_Char_pCell.h"

/// OR USING ENUM -> CELL.CPP

//#define LEFT_SYMBOL 'L'
//#define UP_SYMBOL 'U'
//#define RIGHT_SYMBOL 'R'
//#define DOWN_SYMBOL 'D'
//#define INVALID_SYMBOL ' '


class Cell
{
public:
	Cell();
	// Default copy constructor, operator=...
public:
	void setIndexes(int indexRow, int indexCol);
	void setOwner(Board* owner);
	void setSymbol(char symbol);
	void setParent(Cell* parent);
	void setOpened(bool opened);
	void setClosed(bool closed);
	void setVisited(bool visited);
	void setH(int h);
	int getIndexRow() const;
	int getIndexCol() const;
	Board* getOwner() const;
	char getSymbol() const;
	Cell* getParent() const;
	bool getOpened() const;
	bool getClosed() const;
	bool getVisited() const;
	int getH() const;

	bool getWalkableWithoutWalls() const;
	bool getWalkableWithoutWallsAndDoors() const;
	void computeH(Cell* targerCell);

	Cell* getLeftCell() const;
	Cell* getUpCell() const;
	Cell* getRightCell() const;
	Cell* getDownCell() const;


private:
	void setDefaultValues();
private:
	int indexRow, indexCol;
	char symbol;
	bool visited;
	Board* owner;
	Cell* parent;
	bool opened, closed;
	int h;
};