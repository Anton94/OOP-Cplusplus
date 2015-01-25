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

/// Copies the values from the other cell and sets the owner to null and the cells wont have any neighbours!

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

/// Gets the water from the last iteration and pours out water from the cell in his neighbours 'toAdd' values.
/// If the cell dont have owner -> can`t pours anything so returns false.
/// If the cell dont pour out some water returns false, otherwise returns true.

bool Cell::pourOut()
{
	// If there is no water to pour or there is no owner->returns false.
	if (!owner || water <= 0.0)
		return false;

	// Calculate what quantity of water that can be pour out. If there is no water to pour(the neighbours are with heights more than current one and no rivers) returns false.
	double flow = owner->getFlow();
	double maxWaterToPour = neighboursWithLessHeight.getSize() * flow + neighboursRiver.getSize() * flow * 2;
	if (maxWaterToPour <= 0.0)
		return false;

	// If the maximum flow (waterToPour) is less than the water in the cell, pours in every neighbour (with less height) the maximum flow capacity.
	if (maxWaterToPour <= water)
	{
		pourOutToTheNeightboursWithLessHeight(flow);

		// Removes the poured water. (dont pour to the rivers for now.. the pointers are null).
		water -= maxWaterToPour;
	}
	else
	{
		// If the water in the cell can pour in each neighbour cell in equal amounts (flow of the street map is the max portion). (dont pour to the rivers for now.. the pointers are null).
		double maxWaterToPourWithSameFlow = neighboursWithLessHeight.getSize() * flow + neighboursRiver.getSize() * flow;
		if (maxWaterToPourWithSameFlow > water)
		{
			double waterPortion = water / (neighboursWithLessHeight.getSize() + neighboursRiver.getSize());
			pourOutToTheNeightboursWithLessHeight(waterPortion);
			water = 0.0;			
		}
		// The water in the cell can pour out with the flow capacity to the neighbour cells and more than flow capacity but less than 2*flow capacity to the rivers.
		else
		{
			pourOutToTheNeightboursWithLessHeight(flow);
			water = 0.0;
		}
	}

	return true;
}

/// Pour out water to the neighbours with less height (given amount).

void Cell::pourOutToTheNeightboursWithLessHeight(double amount)
{
	for (DLList<Cell*>::Iterator iter = neighboursWithLessHeight.begin(); iter != neighboursWithLessHeight.end(); ++iter)
	{
		(*iter)->toAdd += amount;
	}
}

/// Gets the cell neighbours and push them into the given list. In our case there are four neighbours. If there is no owner-> dont make any neighbours.

void Cell::getCellNeighbours(DLList<Cell*>& neighbours)
{
	if (!owner)
		return;
	neighbours.push_back(getLeftCell());
	neighbours.push_back(getUpCell());
	neighbours.push_back(getRightCell());
	neighbours.push_back(getDownCell());
}

void Cell::calculateCellNeighbours()
{
	// Get all neighbour cells in double linked list.
	DLList<Cell*> neighbours;
	getCellNeighbours(neighbours);

	// Get the cells with less height and river once from all neighbours.
	getCellNeighboursWithLessHeight(neighbours);
	getCellNeighboursRiver(neighbours);// neighbours river is with null pointers but in the future may be something different(like river cells some kind or ...), so maybe it`s better like that.
}

/// TO DO CONST ITERATOR.

/// Pushes in the second list (neighboursWithLessHeight) the cells from neighbours which have less height.

void Cell::getCellNeighboursWithLessHeight(DLList<Cell*>& neighbours)
{
	for (DLList<Cell*>::Iterator iter = neighbours.begin(); iter != neighbours.end(); ++iter)
	{
		if ((*iter) && (*iter)->getHeight() < height)
			neighboursWithLessHeight.push_back(*iter);
	}
}

/// Pushes in the second list (neighboursRiver) the cells from neighbours which are "river"(NULL).

void Cell::getCellNeighboursRiver(DLList<Cell*>& neighbours)
{
	for (DLList<Cell*>::Iterator iter = neighbours.begin(); iter != neighbours.end(); ++iter)
	{
		if (!(*iter))
			neighboursRiver.push_back(*iter);
	}
}


/// Adds 'toAdd' value to the water value.

void Cell::updateCell()
{
	water += toAdd;
	toAdd = 0.0;
}

///  Sets water level and toAdd variable to 0.0

void Cell::resetWaterLevel()
{
	water = toAdd = 0.0;
}