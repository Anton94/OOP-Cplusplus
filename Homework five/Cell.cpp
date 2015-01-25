#include <iostream>
#include "Cell.h"

Cell::Cell()
{
	setDefaultValues();
}

Cell::Cell(const Cell& other)
{
	copyFrom(other);
}

Cell& Cell::operator=(const Cell& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
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

/// Copies the values from the other cell and sets the owner to null.

void Cell::copyFrom(const Cell& other)
{
	this->indexRow = other.indexRow;
	this->indexCol = other.indexCol;
	this->height = other.height;
	this->owner = NULL;
	this->water = other.water;
	this->toAdd = other.toAdd;
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
	if (height < this->owner->getMinHeight() || height > this->owner->getMaxHeight())
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

/// Returns the height of the cell.

int Cell::getHeight() const
{
	return height;
}

/// Returns the water level of the cell.

double Cell::getWater() const
{
	return water;
}

/// Returns a pointer to the LEFT cell of the current one. If the cell is outside the bounds of the map->returns NULL;

Cell* Cell::getLeftCell() const
{
	if (!owner)
		return NULL;

	return owner->getCellAt(indexRow, indexCol - 1);
}

/// Returns a pointer to the UP cell of the current one. If the cell is outside the bounds of the map->returns NULL;

Cell* Cell::getUpCell() const
{
	if (!owner)
		return NULL;

	return owner->getCellAt(indexRow - 1, indexCol);
}

/// Returns a pointer to the RIGHT cell of the current one. If the cell is outside the bounds of the map->returns NULL;

Cell* Cell::getRightCell() const
{
	if (!owner)
		return NULL;

	return owner->getCellAt(indexRow, indexCol + 1);
}

/// Returns a pointer to the DOWN cell of the current one. If the cell is outside the bounds of the map->returns NULL;

Cell* Cell::getDownCell() const
{
	if (!owner)
		return NULL;

	return owner->getCellAt(indexRow + 1, indexCol);
}

