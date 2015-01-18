#pragma once

class Cell;

#include "Map.h"

class Cell
{
private:
	int indexRow;
	int indexCol;
	Map** map;
};