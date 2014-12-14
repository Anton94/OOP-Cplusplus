#include <iostream>
#include "Test.h"
#include "InsertionSort.h"
#include "MergeSort.h"

int main()
{
	InsertionSort<int> insertionSort;
	MergeSort<int> mergeSort;

	Sorter<int> ** sorters = new Sorter<int>*[5];

	sorters[0] = &insertionSort;
	sorters[1] = &mergeSort;
	Test<int> test(sorters, 2);
	test.getSummary(std::cout);

	delete [] sorters;

	return 0;
}