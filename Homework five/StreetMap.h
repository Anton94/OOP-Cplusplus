#pragma once

class StreetMap;

#include "Cell.h"
#include "../Queue with one link/Queue.h"
#include "Pair.h"

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
	int getMinHeight() const;
	int getMaxHeight() const;
	double getFlow() const;
	void setHeightBounds(int minHeight, int maxHeight);
	void setFlow(double flow);
	void deserialize(std::istream& in);
	void printStreetMapWithHeights(std::ostream& out) const;
	void printStreetMapWithWater(std::ostream& out) const;
	void printIterations(std::ostream& out);
	void executeIterations(std::ostream& out);
private:
	void setDefaultValues();
	void copyFrom(const StreetMap& other);
	void copyFromStreetMapCells(const StreetMap& other);
	void setCellsOwner();
	void free();
	void allocateStreetMapArray(int rows, int cols);
	void deserializeStreetMapHeights(std::istream& in);
	void deserializeIterations(std::istream& in);
	void printCellHeight(std::ostream& out, int i, int j) const;
	void printCellWater(std::ostream& out, int i, int j) const;
	void printCellInfo(std::ostream& out, void (StreetMap::*printInfo)(std::ostream& out, int i, int j) const) const;
	void printIterationData(std::ostream& out, Pair<double, int> iteration);
	void foreachIteration(std::ostream& out, void (StreetMap::*action)(std::ostream& out, Pair<double, int> iteration));
	void executeAIteration(std::ostream& out, Pair<double, int> iteration);
private:
	Cell ** streetMap;
	int rows;
	int cols;
	int minHeight;
	int maxHeight;
	double flow; // constant c...
	Queue<Pair<double, int>> iterations;
};