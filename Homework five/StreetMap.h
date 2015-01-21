#pragma once

// have declaration to make posible map in cell, and cell in map , some fucked up shits...
class StreetMap;

#include "Cell.h"


class StreetMap
{
public:
	StreetMap();
	StreetMap(const StreetMap& other);
	StreetMap& operator=(const StreetMap& other);
	~StreetMap();
	int getRows() const;
	int getCols() const;
	void deserialize(std::istream& in);
	void setFlow(double flow);
private:
	void setDefaultValues();
	void copyFrom(const StreetMap& other);
	void free();

	void deserializeTheRowsAndCols(std::istream& in);
	void allocateStreetMapArray(int rows, int cols);
private:
	Cell ** streetMap;
	int rows;
	int cols;
	double flow; // constant c...
};