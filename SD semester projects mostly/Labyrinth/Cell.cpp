#include <iostream>
#include "Cell.h"

/// Default constructor.

Cell::Cell()
{
	setDefaultValues();
}

void Cell::setDefaultValues()
{
	indexRow = indexCol = 0;
	symbol = ' ';
	visited = false;
	owner = NULL;	
	parent = NULL;
	opened = closed = false;
	h = 0;
}


/// Validation for the indexes more than ziro and if the cell has owner-> validation for the indexes inside the bounds of the map.

void Cell::setIndexes(int indexRow, int indexCol)
{
	if (owner && (indexRow >= owner->getRows() || indexCol >= owner->getCols() || indexRow < 0 || indexCol < 0))
		throw "Invalid indexes of the cell!";

	this->indexRow = indexRow;
	this->indexCol = indexCol;
}

/// Sets the owner of the cell.

void Cell::setOwner(Board* owner)
{
	this->owner = owner;
}

/// Sets the symbol of the cell.

void Cell::setSymbol(char symbol)
{
	this->symbol = symbol;
}

void Cell::setParent(Cell* parent)
{
	this->parent = parent;
}

void Cell::setOpened(bool opened)
{
	this->opened = opened;
}

void Cell::setClosed(bool closed)
{
	this->closed = closed;
}

void Cell::setVisited(bool visited)
{
	this->visited = visited;
}

void Cell::setH(int h)
{
	this->h = h;
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

/// Returns the owner of the cell.

Board* Cell::getOwner() const
{
	return owner;
}

/// Returns the symbol of the cell.

char Cell::getSymbol() const
{
	return symbol;
}

Cell* Cell::getParent() const
{
	return parent;
}

bool Cell::getOpened() const
{
	return opened;
}

bool Cell::getClosed() const
{
	return closed;
}

bool Cell::getVisited() const
{
	return visited;
}

int Cell::getH() const
{
	return h;
}

/// Checks only if the cell is not board wall...

bool Cell::getWalkableWithoutWalls() const
{
	if (!owner)
		return true;

	return symbol != owner->boardSymbols.wall;
}

/// Checks only if the cell is not board wall or some kind of door.

bool Cell::getWalkableWithoutWallsAndDoors() const
{
	if (!owner)
		return true;

	// Check if the symbol is some of the door symbols and return false if so...
	if (owner->doors.getCellAt(symbol))
		return false;

	// Check if its wall...
	return getWalkableWithoutWalls();
}

/// Calculates the distance to the target cell.

void Cell::computeH(Cell* targerCell)
{
	h = (std::abs(targerCell->indexRow - indexRow) + std::abs(targerCell->indexCol - indexCol));
}