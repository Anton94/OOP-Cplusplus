#pragma once

#include <iostream>
#include "SortTester.h"
#include "Sorter.h"

template<typename T>
class Test : public SortTester<T>
{
public:
	Test(Sorter<T> ** sorters, int count);
	virtual void getSummary(std::ostream & out);
};