#pragma once

class Cell;

#include "StreetMap.h"

/*
	Default copy constructor and default operator= 

	pourOut : get the water from the last pour and pours the water to the toAdd variable on the neighbours cells. 
	Because of that it had to make last iteration on the map to update all cells. 
*/

class Cell
{
	friend class StreetMap;
public:
	Cell(int indexRow, int indexCol, double height, StreetMap * owner);
	void setWater(double water);
	bool pourOut();
	void updateAll(); // adds toAdd value to the water value.
private:
	int indexRow;
	int indexCol;
	double height;
	StreetMap* owner;
	double water;
	double toAdd;
};