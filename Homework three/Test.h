#pragma once

#include <iostream>
#include "SortTester.h"
#include "Sorter.h"
#include "Utility.h"

#ifndef MACROSES   // DA moga da gi zatvorq, che ne moga da 
#define MACROSES
#define START_TEST(msg) out << msg << "\n"; \
	srand(time(NULL))

#define PRINT_ARRAY(arr, size, msg)			\
	out << "    " << msg << ": ";			\
	Utility<T>::printArray(arr, size, out)

#define PRINT_STATUS(arr, size)						\
	if (Utility<T>::checkForSortedArray(arr, size))	\
		out << "    Test status: Passed!\n";		\
	else											\
		out << "    Test status: Failed!\n"

#define PRINT_DESCR(msg) out << "  " << msg << ":\n"
#define PRINT_SORT_DESCRIPTION(sort)						\
	MySorter<T> * mySorter;									\
	if (mySorter = dynamic_cast<MySorter<T>*>(sort))		\
		PRINT_DESCR(mySorter->description());				\
	else													\
		PRINT_DESCR("Unknown sorting algorithm")

#define END_TEST out << "\n"

#endif

template<typename T>
class Test : public SortTester<T>
{
public:
	Test(Sorter<T> ** sorters, int count);
	virtual void getSummary(std::ostream & out);
protected:
	void testWithRandomData(std::ostream & out) const;
	void testWithEmptyArray(std::ostream & out) const;
protected:
	Sorter<T> ** sorters;
	int count;
};

template <class T>
inline Test<T>::Test(Sorter<T> ** sorters, int count) : SortTester<T>(sorters, count)
{
	if (sorters != NULL && count > 0)
	{
		this->sorters = new Sorter<T>*[count];
		for (int i = 0; i < count; ++i)
		{
			this->sorters[i] = sorters[i];
		}
	}
	else
	{
		this->sorters = NULL;
	}

	this->count = count;
}

template <class T>
inline void Test<T>::testWithRandomData(std::ostream & out) const
{
	START_TEST("Test with random elements!");

	size_t size = rand() % 12 + 1; // [1,30]

	T * originalArr = new T[size];

	for (size_t i = 0; i < size; ++i)
		originalArr[i] = rand() % 1000; // [0,999]

	T * arr = new T[size];	

	for (int i = 0; i < count; ++i)
	{
		Utility<T>::copyTo(arr, originalArr, size);

		PRINT_SORT_DESCRIPTION(sorters[i]);

		PRINT_ARRAY(arr, size, "Array before sort");

		sorters[i]->sort(arr, size);

		PRINT_ARRAY(arr, size, "Array after  sort");

		PRINT_STATUS(arr, size);
	}

	delete[] originalArr;
	delete[] arr;

	END_TEST;
}

template <class T>
inline void Test<T>::testWithEmptyArray(std::ostream & out) const
{
	START_TEST("Test with empty array!");
	T * arr = NULL;
	size_t size = 0;

	for (int i = 0; i < count; ++i)
	{
		PRINT_SORT_DESCRIPTION(sorters[i]);

		PRINT_ARRAY(arr, size, "Array before sort");

		sorters[i]->sort(arr, size);

		PRINT_ARRAY(arr, size, "Array after  sort");

		PRINT_STATUS(arr, size);
	}

	END_TEST;
}

template <class T>
inline void Test<T>::getSummary(std::ostream & out)
{
	testWithRandomData(out);
	testWithEmptyArray(out);
}