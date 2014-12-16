/*

	#71488 FMI 
	Homework three

	Github repository: https://github.com/Anton94/OOP-Cplusplus
	Github project:	   https://github.com/Anton94/OOP-Cplusplus/tree/master/Homework%20three

*/

#include <iostream>
#include <fstream>
#include "MyTestStruct.h"
#include "Test.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"


int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		std::ofstream testFile("Test.txt");
		if (!testFile)
			std::cerr << "Something bad happened! Can`t open the file!\n";

		testFile << "The test class generates my own data which is one int value for comparation and load, which of array with 42 double values.\n"
			<< "In the following data, you can see how bad or good are the algorithms!\n"
			<< "(I don`t know if I need to say this algorithm is with O(n*logN) and etc..."
			<< "I suppose you need only the output data)\n"
			<< "If you want to make the test arrays smaller or bigger you can modify all of them with the #macros SIZE in 'Test.h'!\n\n\n";

		InsertionSort<MyTestStruct> insertionSort;
		MergeSort<MyTestStruct> mergeSort;
		HeapSort<MyTestStruct> heapSort;
		QuickSort<MyTestStruct> quickSort;
		SelectionSort<MyTestStruct> selectionSort;
		ShakerSort<MyTestStruct> shakerSort;

		Sorter<MyTestStruct> ** sorters = new Sorter<MyTestStruct>*[6];

		sorters[0] = &insertionSort;
		sorters[1] = &mergeSort;
		sorters[2] = &heapSort;
		sorters[3] = &quickSort;
		sorters[4] = &selectionSort;
		sorters[5] = &shakerSort;
		Test<MyTestStruct> test(sorters, 6);
		test.getSummary(testFile);

		delete[] sorters;
		testFile.close();
	}


	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}