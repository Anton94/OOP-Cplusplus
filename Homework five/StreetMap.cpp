#include <iostream>
#include "StreetMap.h"

StreetMap::StreetMap()
{
	setDefaultValues();
}

StreetMap::StreetMap(const StreetMap& other)
{
	copyFrom(other);
}

StreetMap& StreetMap::operator=(const StreetMap& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

StreetMap::~StreetMap()
{
	free();
}


void StreetMap::copyFrom(const StreetMap& other)
{
	// Allocate the needed memory for the table.
	allocateStreetMapArray(other.rows, other.cols);

	// Sets the table datas(cell datas).
	copyFromStreetMapCells(other);

	// Change the owner of each cell.
	setCellsOwner();
}

/// Copies the cells data from the other streetMap object.

void StreetMap::copyFromStreetMapCells(const StreetMap& other)
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			streetMap[i][j] = other.streetMap[i][j];
		}
	}
}

/// For each cell on the streetmap reset the owner to current object.

void StreetMap::setCellsOwner()
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			streetMap[i][j].setOwner(this);
		}
	}
}

/// Returns the number of rows of the street map.

int StreetMap::getRows() const
{
	return this->rows;
}

/// Returns the number of columns of the street map.

int StreetMap::getCols() const
{
	return this->cols;
}

/// Returns the number of columns of the street map.

double StreetMap::getFlow() const
{
	return this->flow;
}

/// Prints the street map with the heights of the cells.

void StreetMap::printStreetMapWithHeights(std::ostream& out) const
{
	printCellInfo(out, &StreetMap::printCellHeight);
}

/// Prints the street map with the water level of the cells.

void StreetMap::printStreetMapWithWater(std::ostream& out) const
{
	printCellInfo(out, &StreetMap::printCellWater);
}

/// Prints cell info by it`s coords on the map, does not make check for valid coords.

void StreetMap::printCellHeight(std::ostream& out, int i, int j) const
{
	out << this->streetMap[i][j].getHeight();
}

/// Prints cell info by it`s coords on the map, does not make check for valid coords.

void StreetMap::printCellWater(std::ostream& out, int i, int j) const
{
	out << this->streetMap[i][j].getWater();
}

/// Iterates all cells and applies the given function(which will print the cell information).

void StreetMap::printCellInfo(std::ostream& out, void (StreetMap::*printInfo)(std::ostream& out, int i, int j) const) const
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			(*this.*printInfo)(out, i, j);
			out << " ";
		}

		out << "\n";
	}
}

/// Deserialize street map data from istream

void StreetMap::deserialize(std::istream& in)
{
	if (!in)
		throw "Something went wrong with input streem!";

	// Get rows cols and flow capacity.

	int rows, cols;
	double flow;
	in >> rows >> cols >> flow;
	if (!in)
		throw "Something went wrong with input streem when tries to read dementions and flow capacity of the streets!";

	// Allocate the street map (2D array, also sets the sizes).
	allocateStreetMapArray(rows, cols);

	// Set the flow capcity
	setFlow(flow);

	// Get the height values for the table
	deserializeStreetMapHeights(in);

	// TO DO other things...
}

/// Initialize the heights of every point of the street map.

void StreetMap::deserializeStreetMapHeights(std::istream& in)
{
	int tempHeight;

	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			in >> tempHeight;
			if (!in)
				throw "Invalid input data for the heights of the street map!";

			// Set the basic data for the cell. I use function because in the future there may be add more restrictions for the members(like height in some interval and so..)
			this->streetMap[i][j].setOwner(this);
			this->streetMap[i][j].setIndexes(i, j);
			this->streetMap[i][j].setHeight(tempHeight);
		}
	}
}

/// Sets the flow capcity of the 'streets'. If it`s negative number (double) throws exeption.

void StreetMap::setFlow(double flow)
{
	if (flow < 0)
		throw "Invalid value of the flow capacity!";

	this->flow = flow;
}

// Allocates the 2D array for the streetmap with the given rows and cols(and sets the streetmap size(rows, cols) to the given one. If the allocation fails, clears allocated memory if needed and throws exeption.

void StreetMap::allocateStreetMapArray(int rows, int cols)
{
	if (rows < 0 || cols < 0)
		throw "Invalid sizes of the streetMap!";

	this->rows = rows;
	this->cols = cols;

	try
	{
		streetMap = new Cell*[cols];

		// Sets all pointers to null in case of some allocation after that fail-> so the free function can safty delets all the allocated memory.
		for (int i = 0; i < rows; ++i)
		{
			streetMap[i] = NULL;
		}

		for (int i = 0; i < rows; ++i)
		{
			streetMap[i] = new Cell[cols];
		}
	}
	catch (std::bad_alloc& ba)
	{
		free();
		setDefaultValues();
		throw "Bad alloc exeption, can`t allocate memory for the streetMap!";
	}
}

/// Deletes all the dynamic allocated memory (NOTE: dont sets the default values after that!).

void StreetMap::free()
{
	if (!streetMap)
		return;

	for (int i = 0; i < rows; ++i)
		delete streetMap[i];

	delete[] streetMap;
}

/// Sets the default values (empty street map).

void StreetMap::setDefaultValues()
{
	streetMap = NULL;
	rows = cols = 0;
}