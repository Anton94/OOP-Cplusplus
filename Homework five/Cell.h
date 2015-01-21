#pragma once

class Cell;

#include "StreetMap.h"

/*
	pourOut : get the water from the last pour and pours the water to the toAdd variable on the neighbours cells with lower height(or pours out of the street map(river)). 
	Because of that it had to make last iteration on the map to update all cells. 
*/

class Cell
{
	friend class StreetMap;
public:
	Cell();
	void setIndexes(int indexRow, int indexCol);
	void setHeight(int height);
	void setOwner(StreetMap* owner);
	void setWater(double water);
	bool pourOut();
	void updateAll(); // adds toAdd value to the water value.
private:
	void setDefaultValues();
private:
	int indexRow;
	int indexCol;
	int height;
	StreetMap* owner;
	double water;
	double toAdd;
};