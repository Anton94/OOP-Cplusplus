#include "Directions.h"

/// Calculates which direction is right cell, depends on the position of left cell...

char Directions::getDirectionToCell(Cell* left, Cell * right)
{
	if (right->getIndexRow() < left->getIndexRow())
		return Directions_symbol::UP_SYMBOL;

	if (right->getIndexRow() > left->getIndexRow())
		return Directions_symbol::DOWN_SYMBOL;

	if (right->getIndexCol() < left->getIndexCol())
		return Directions_symbol::LEFT_SYMBOL;

	if (right->getIndexCol() > left->getIndexCol())
		return Directions_symbol::RIGHT_SYMBOL;

	return Directions_symbol::INVALID_SYMBOL;
}