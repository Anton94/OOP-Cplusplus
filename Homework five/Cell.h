#pragma once

class Cell;

#include "StreetMap.h"

/*
	pourOut : get the water from the last pour and pours the water to the toAdd variable on the neighbours cells with lower height(or pours out of the street map(river)). 
	Because of that it had to make last iteration on the map to update all cells. 


	NOTE:
	copy constructor and operator= will make cells which will be exact copy to the same streetMap(the owener will be the same!).
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
	int getHeight() const;
	double getWater() const;
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