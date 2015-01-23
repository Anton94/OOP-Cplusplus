#include <iostream>
#include "Cell.h"

Cell::Cell()
{
	setDefaultValues();
}

/// Sets the default values of the cell.

void Cell::setDefaultValues()
{
	this->indexRow = 0;
	this->indexCol = 0;
	this->height = 0;
	this->owner = NULL;
	this->water = 0.0;
	this->toAdd = 0.0;
}

/// Validation for the indexes more than ziro and if the cell has owner-> validation for the indexes inside the bounds of the map.

void Cell::setIndexes(int indexRow, int indexCol)
{
	if (indexRow < 0 || indexCol < 0 || (owner && (indexRow >= owner->getRows() || indexCol >= owner->getCols())))
		throw "Invalid indexes of the cell!";

	this->indexRow = indexRow;
	this->indexCol = indexCol;
}

/// Sets the heighr [-100;1000] otherwise throws exeption

void Cell::setHeight(int height)
{
	if (height < -100 || height > 1000)
	{
		throw "Invalid value for the height";
	}

	this->height = height;
}

/// Sets the owner of the cell.

void Cell::setOwner(StreetMap* owner)
{
	this->owner = owner;
}

/// Sets the water level for the cell, if the given water level is negative- throws exeption.

void Cell::setWater(double water)
{
	if (water < 0.0)
		throw "Can`t add negative value for the water level!";

	this->water = water;
}