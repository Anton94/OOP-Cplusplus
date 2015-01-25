#include <iostream>
#include "StreetMap.h"

/*
///
*/

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

/// Sets the default values (empty street map).

void StreetMap::setDefaultValues()
{
	streetMap = NULL;
	rows = cols = minHeight = maxHeight = 0;
}

void StreetMap::copyFrom(const StreetMap& other)
{
	// Allocate the needed memory for the table.
	allocateStreetMapArray(other.rows, other.cols);

	// Sets the table datas(cell datas).
	copyFromStreetMapCells(other);

	// Change the owner of each cell.
	setCellsOwner();

	// Calculate the cells neighbours.
	calculateEveryCellNeighbours();

	// Sets the bounds of the heights, the flow capacity and iterations.
	this->minHeight = other.minHeight;
	this->maxHeight = other.maxHeight;
	this->flow = other.flow;
	
	this->iterations = other.iterations;
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

/// Deletes all the dynamic allocated memory (NOTE: dont sets the default values after that!).

void StreetMap::free()
{
	if (!streetMap)
		return;

	for (int i = 0; i < rows; ++i)
		delete[] streetMap[i];

	delete[] streetMap;
}

/// Goes throw every cell and sets the neighbours.

void StreetMap::calculateEveryCellNeighbours()
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			streetMap[i][j].calculateCellNeighbours();
		}
	}
}


/*
///
*/


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

/// Returns the minimum height of the street map.

int StreetMap::getMinHeight() const
{
	return this->minHeight;
}

/// Returns the maximum height of the street map.

int StreetMap::getMaxHeight() const
{
	return this->maxHeight;
}

/// Returns the number of columns of the street map.

double StreetMap::getFlow() const
{
	return this->flow;
}

/// Checks if the height bounds are correct and sets them. Doesnt make recheck for the current height of the cells!

void StreetMap::setHeightBounds(int minHeight, int maxHeight)
{
	if (minHeight > maxHeight)
		throw "Invalid values for the height bounds of the street map!";

	this->minHeight = minHeight;
	this->maxHeight = maxHeight;
}

/// Sets the flow capcity of the 'streets'. If it`s negative number (double) throws exeption.

void StreetMap::setFlow(double flow)
{
	if (flow < 0)
		throw "Invalid value of the flow capacity!";

	this->flow = flow;
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

/// Prints the iterations , loaded from the istream.

void StreetMap::printIterations(std::ostream& out)
{
	foreachIteration(out, &StreetMap::printIterationData);
}

/// Deserialize street map data from istream

void StreetMap::deserialize(std::istream& in)
{
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

	// Calculate the street map cells neighbours
	calculateEveryCellNeighbours();

	// Get the iterations(how many 'rains' and how many iterations has to make).
	deserializeIterations(in);
}

/// Initialize the heights of every point of the street map.

void StreetMap::deserializeIterations(std::istream& in)
{
	// Get the number of iterations.
	int numberOfIterations;
	in >> numberOfIterations;
	if (!in)
		throw "Invalid value for the number of iterations!";

	double numberOfLiters;
	int numberOfSteps;

	// Get iterations (one by one).
	for (int i = 0; i < numberOfIterations; ++i)
	{
		in >> numberOfLiters >> numberOfSteps;
		if (numberOfLiters < 0 || numberOfSteps < 0)
			throw "Invalid information for the iteration!";

		iterations.enqueue(Pair<double, int>(numberOfLiters, numberOfSteps));
	}
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

/// Execute each iteration with the current streetmap values.

void StreetMap::executeIterations(std::ostream& out)
{
	foreachIteration(out, &StreetMap::executeAIteration);
}

/// Goes through each iteration and applies some action (pointer to void function, takes istream and makes copy of the given iteration).

void StreetMap::foreachIteration(std::ostream& out, void (StreetMap::*action)(std::ostream& out, Pair<double, int> iteration))
{
	size_t numberOfIterations = iterations.getSize();
	Pair<double, int> current;

	for (size_t i = 0; i < numberOfIterations; ++i)
	{
		current = iterations.dequeue();
		(*this.*action)(out, current);
		iterations.enqueue(current);
	}
}

/// Prints iteration data.

void StreetMap::printIterationData(std::ostream& out, Pair<double, int> iteration)
{
	out << iteration.first << " " << iteration.second << "\n";
}

/// Make simulation with the given iteration and the current streetmap values.

void StreetMap::executeAIteration(std::ostream& out, Pair<double, int> iteration)
{
	// Resets all cells (water levels and so..)
	resetEveryCell();

	// Sets the water from the given iteration.
	setWaterlevelToEveryCell(iteration.first);

	bool flag = true; // For stable streetMap

	// Pours out the water from each cell given amount of times(iteration.second value).
	while (iteration.second-- > 0 && flag)
	{
		flag = false;

		for (int i = 0; i < this->rows; ++i)
		{
			for (int j = 0; j < this->cols; ++j)
			{
				if (streetMap[i][j].pourOut())
					flag = true;
			}
		}

		updateEveryCell();
	}

	//out << "Iterations left: " << iteration.second + 1 << "\n";
	printStreetMapWithWater(out);
	out << "\n";
}

/// Returns a pointer to the cell, with the given coords. If the cell is outside the bounds of the map->returns NULL;

Cell* StreetMap::getCellAt(int i, int j)
{
	if (i < 0 || j < 0 || i >= this->rows || j >= this->cols)
		return NULL;

	return &streetMap[i][j];
}

/// TO DO: MAY BE ADD FOREACH CELL FUNCTION BUT IT HAS TO BE WITH DIFF POINTERS SO..

/// Goes throw every cell and update it`s water status(adds 'toAdd' value to the water from the last iteration on the streetmap).

void StreetMap::updateEveryCell()
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			streetMap[i][j].updateCell();
		}
	}
}

/// Goes throw every cell and sets the water level of the cell with the given one as parameter.

void StreetMap::setWaterlevelToEveryCell(double water)
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			streetMap[i][j].setWater(water);
		}
	}
}

/// Goes throw every cell and resets it`s water levels.

void StreetMap::resetEveryCell()
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			streetMap[i][j].resetWaterLevel();
		}
	}
}