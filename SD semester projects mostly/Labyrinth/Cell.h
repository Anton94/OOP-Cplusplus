#pragma once

class Cell;

#include "Board.h"

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
	void setH(int h);
	Board* getOwner() const;
	char getSymbol() const;
	Cell* getParent() const;
	bool getOpened() const;
	bool getClosed() const;
	int getH() const;

	bool getWalkable() const;
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
	Board* owner;
	Cell* parent;
	bool opened, closed;
	int h;
};