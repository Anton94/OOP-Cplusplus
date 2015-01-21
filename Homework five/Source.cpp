#include <iostream>
#include "StreetMap.h"



int main()
{
	StreetMap map;

	Cell cell(0, 0, 10, &map);
	Cell cell2 = cell;

	cell2 = cell2;

	return 0;
}