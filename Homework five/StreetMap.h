#pragma once

class StreetMap;

#include "Cell.h"

class StreetMap
{
public:
	StreetMap();
	StreetMap(const StreetMap& other);
	StreetMap& operator=(const StreetMap& other);
	~StreetMap();
public:
	int getRows() const;
	int getCols() const;
	double getFlow() const;
	void deserialize(std::istream& in);
	void setFlow(double flow);
	void printStreetMapWithHeights(std::ostream& out) const;
	void printStreetMapWithWater(std::ostream& out) const;
private:
	void setDefaultValues();
	void copyFrom(const StreetMap& other);
	void free();
	void allocateStreetMapArray(int rows, int cols);
	void initializeStreetMapHeights(std::istream& in);
	void printCellHeight(std::ostream& out, int i, int j) const;
	void printCellWater(std::ostream& out, int i, int j) const;
	void printCellInfo(std::ostream& out, void (StreetMap::*printInfo)(std::ostream& out, int i, int j) const) const;
private:
	Cell ** streetMap;
	int rows;
	int cols;
	double flow; // constant c...
};