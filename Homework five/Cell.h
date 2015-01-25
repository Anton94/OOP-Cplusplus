#pragma once

#include "../Double linked list/DLList.h"

class Cell;

#include "StreetMap.h"

/*
	pourOut : get the water from the last pour and pours the water to the toAdd variable on the neighbours cells with lower height(or pours out of the street map(river)). 
	Because of that it had to make last iteration on the map to update all cells. 


	NOTE:
	copy constructor and operator= will make cells which will be exact copy but the owner will be null!
*/

class Cell
{
public:
	Cell();
	Cell(const Cell& other);
	Cell& operator=(const Cell& other);
	void setIndexes(int indexRow, int indexCol);
	void setHeight(int height);
	void setOwner(StreetMap* owner);
	void setWater(double water);
	int getHeight() const;
	double getWater() const;
	bool pourOut();
	void updateCell();
	void resetWaterLevel();
private:
	void setDefaultValues();
	void copyFrom(const Cell& other);
	Cell* getLeftCell() const;
	Cell* getUpCell() const;
	Cell* getRightCell() const;
	Cell* getDownCell() const;
	void getCellNeighbours(DLList<Cell*>& neighbours) const;
	void getCellNeighboursWithLessHeight(DLList<Cell*>& neighbours, DLList<Cell*>& neighboursWithLessHeight) const;
	void getCellNeighboursRiver(DLList<Cell*>& neighbours, DLList<Cell*>& neighboursRiver) const;
	void pourOutToTheNeightboursWithLessHeight(DLList<Cell*>& neighboursWithLessHeight, double amount);
private:
	int indexRow;
	int indexCol;
	int height;
	StreetMap* owner;
	double water;
	double toAdd;
};