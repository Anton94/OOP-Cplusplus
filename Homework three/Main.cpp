#include <iostream>
#include "Test.h"
#include "InsertionSort.h"

int main()
{
	InsertionSort<int> insertionSort;

	Sorter<int> ** sorters = new Sorter<int>*[3];

	sorters[0] = &insertionSort;
	sorters[1] = &insertionSort;
	Test<int> test(sorters, 2);
	test.getSummary(std::cout);

	delete [] sorters;

	return 0;
}