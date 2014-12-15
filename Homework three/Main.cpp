#include <iostream>
#include "Test.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "MyTestStruct.h"

int main()
{
	InsertionSort<MyTestStruct> insertionSort;
	MergeSort<MyTestStruct> mergeSort;

	Sorter<MyTestStruct> ** sorters = new Sorter<MyTestStruct>*[5];

	sorters[0] = &insertionSort;
	sorters[1] = &mergeSort;
	Test<MyTestStruct> test(sorters, 2);
	test.getSummary(std::cout);

	delete [] sorters;

	return 0;
}