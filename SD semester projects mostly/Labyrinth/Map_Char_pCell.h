#pragma once

class Map_Char_pCell;

#include "Cell.h"
#include "../Vector/Vector.h"

/*
	A basic map of valid 256 char symbols and pointers to cells.
	I have a table, where I can get the pointer to the cell and sets it with constant time. This is some basic very basic map, only for char symbols and pointers to cell.
*/


// The valid symbols for this task are 256.
#define NUMBER_OF_ELEMENTS_IN_CHAR 256

class Map_Char_pCell
{
public:
	Map_Char_pCell()
	{
		vector.resize(NUMBER_OF_ELEMENTS_IN_CHAR);
		vector.makeAllElements(NULL);
	}

	/// TO DO OTHER OPTION IS: I can make getAt which returns reference to the pointer and manipulate this ...

	void setCellAt(char c, Cell* cell)
	{
		vector[c] = cell;
	}

	Cell* getCellAt(char c)
	{
		return vector[c];
	}

	int size() const
	{
		return vector.getSize();
	}

	bool hasElementDiferentThan(const Cell* elem)
	{
		for (int i = 0; i < vector.getSize(); ++i)
		{
			if (vector[i] != elem)
				return true;
		}

		return false;
	}
private:
	Vector<Cell*> vector;
};