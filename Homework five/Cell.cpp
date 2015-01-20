#include "Cell.h"

Cell::Cell(int indexRow, int indexCol, double height, StreetMap * owner)
{
	if (!owner)
		throw "Can`t construct object type Cell with NULL pointer to StreetMap!";

	this->indexRow = indexRow;
	this->indexCol = indexCol;
	this->height = height;
	this->owner = owner;
	this->water = 0.0;
	this->toAdd = 0.0;
}

void Cell::setWater(double water)
{
	if (water < 0.0)
		throw "Can`t add negative value for the water level!";

	this->water = water;
}