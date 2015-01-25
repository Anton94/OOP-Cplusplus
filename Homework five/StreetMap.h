#pragma once
/*

#71488 FMI
Homework five

Github repository: https://github.com/Anton94/OOP-Cplusplus
Github project:	   https://github.com/Anton94/OOP-Cplusplus/tree/master/Homework%20five

*/
class StreetMap;

#include "Cell.h"
#include "../Queue with one link/Queue.h"
#include "../Double linked list/DLList.h"
#include "Pair.h"

class StreetMap
{
	friend class Cell;
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
	void printStreetMapWithHeights(std::ostream& out) const;
	void printStreetMapWithWater(std::ostream& out) const;
	void printIterations(std::ostream& out);
	void deserialize(std::istream& in);
	void executeIterations(std::ostream& out);
private:
	void setDefaultValues();
	void allocateStreetMapArray(int rows, int cols);
	void copyFrom(const StreetMap& other);
	void copyFromStreetMapCells(const StreetMap& other);
	void setCellsOwner();
	void calculateEveryCellNeighbours();
	void free();
	void deserializeStreetMapHeights(std::istream& in);
	void deserializeIterations(std::istream& in);
	void printCellHeight(std::ostream& out, int i, int j) const;
	void printCellWater(std::ostream& out, int i, int j) const;
	void printCellInfo(std::ostream& out, void (StreetMap::*printInfo)(std::ostream& out, int i, int j) const) const;
	void printIterationData(std::ostream& out, Pair<double, int> iteration);
	void foreachIteration(std::ostream& out, void (StreetMap::*action)(std::ostream& out, Pair<double, int> iteration));
	void executeAIteration(std::ostream& out, Pair<double, int> iteration);
	Cell* getCellAt(int i, int j);
	void updateEveryCell();
	void setWaterlevelToEveryCell(double water);
	void resetEveryCell();
private:
	Cell ** streetMap;
	int rows;
	int cols;
	int minHeight;
	int maxHeight;
	double flow;
	Queue<Pair<double, int>> iterations;
};