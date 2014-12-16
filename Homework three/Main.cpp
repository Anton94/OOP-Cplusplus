#include <iostream>
#include "MyTestStruct.h"
#include "Test.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "HeapSort.h"

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		InsertionSort<MyTestStruct> insertionSort;
		MergeSort<MyTestStruct> mergeSort;
		HeapSort<MyTestStruct> heapSort;

		Sorter<MyTestStruct> ** sorters = new Sorter<MyTestStruct>*[3];

		sorters[0] = &insertionSort;
		sorters[1] = &mergeSort;
		sorters[2] = &heapSort;
		Test<MyTestStruct> test(sorters, 3);
		test.getSummary(std::cout);

		delete[] sorters;
	}


	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}