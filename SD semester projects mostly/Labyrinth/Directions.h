#pragma once

#include "Cell.h"


enum Directions_symbol
{
	LEFT_SYMBOL = 'L',
	UP_SYMBOL = 'U',
	RIGHT_SYMBOL = 'R',
	DOWN_SYMBOL = 'D',
	INVALID_SYMBOL = ' '
};

class Directions
{
public:
	static char getDirectionToCell(Cell* left, Cell * right);
};