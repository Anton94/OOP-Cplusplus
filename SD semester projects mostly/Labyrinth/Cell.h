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
	Board* getOwner() const;
	char getSymbol() const;
private:
	void setDefaultValues();
	Cell* getLeftCell() const;
	Cell* getUpCell() const;
	Cell* getRightCell() const;
	Cell* getDownCell() const;
private:
	int indexRow, indexCol;
	char symbol;
	Board* owner;
	Cell* parent;
	bool opened, closed;
	int h;
};