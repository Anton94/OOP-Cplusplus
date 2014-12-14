#include <iostream>
#include "Test.h"
#include "InsertionSort.h"

int main()
{
	InsertionSort<int> insertionSort;

	Sorter<int> ** sorters = new Sorter<int>*[3];

	sorters[0] = &insertionSort;
	Test<int> test(sorters, 1);
	test.getSummary(std::cout);

	return 0;
}