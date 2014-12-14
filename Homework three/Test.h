#pragma once

#include <iostream>
#include "SortTester.h"
#include "Sorter.h"
#include "Utility.h"

#ifndef MACROSES   // DA moga da gi zatvorq, che ne moga da gi gledam! (slagam i vuv funkciite {} za moe udobstvo)
#define MACROSES
#define START_TEST(name, msg)								\
	template <class T>										\
	inline void Test<T>::name(std::ostream & out) const		\
		{													\
		out << msg << "\n"

#define PRINT_ARRAY(arr, size, msg)			\
	out << "    " << msg << ": ";			\
	Utility<T>::printArray(arr, size, out)

#define PRINT_STATUS(arr, size)						\
	if (Utility<T>::checkForSortedArray(arr, size))	\
		out << "    Test status: Passed!\n";		\
	else											\
		out << "    Test status: Failed!\n"			

#define PRINT_TIME(val) \
	out << "    Sorting time: " << val << "!\n"

#define PRINT_DESCR(msg) out << "  " << msg << ":\n"
#define PRINT_SORT_DESCRIPTION(sort)						\
	MySorter<T> * mySorter;									\
	if (mySorter = dynamic_cast<MySorter<T>*>(sort))		\
		PRINT_DESCR(mySorter->description());				\
	else													\
		PRINT_DESCR("Unknown sorting algorithm")	 

#define EXECUTE_FOR_ALL_SORTS						\
	for (int i = 0; i < count; ++i)					\
	{												\
		Utility<T>::copyTo(arr, originalArr, size);	\
		PRINT_SORT_DESCRIPTION(sorters[i]);			\
		PRINT_ARRAY(arr, size, "Array before sort");\
		sorters[i]->sort(arr, size);				\
		PRINT_ARRAY(arr, size, "Array after  sort");\
		PRINT_STATUS(arr, size);					\
		PRINT_TIME(sorters[i]->getSortTime());		\
	}


#define END_TEST out << "\n";	\
	delete[] originalArr;		\
	delete[] arr;				\
}						

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
	void testWithOnyTypeOfElements(std::ostream & out) const;
	void testWithSortedArray(std::ostream & out) const;
	void testWithInvertedSortedArray(std::ostream & out) const;
	void testWithFewTypesOfElements(std::ostream & out) const;
	void testWith20000Elements(std::ostream & out) const;
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

START_TEST(testWithRandomData, "Test with random elements!");
{
	srand(time(NULL));
	size_t size = rand() % 12 + 1;		// [1,30]

	int * originalArr = new int[size];

	for (size_t i = 0; i < size; ++i)
		originalArr[i] = rand() % 1000; // [0,999]

	int * arr = new int[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}

START_TEST(testWithEmptyArray, "Test with empty array!");
{
	T * originalArr = NULL;
	size_t size = 0;

	T * arr = new T[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}

START_TEST(testWithOnyTypeOfElements, "Test with one type of elements!");
{
	size_t size = 10;
	int * originalArr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		originalArr[i] = 42;
	}

	int * arr = new int[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}

START_TEST(testWithSortedArray, "Test with sorted array!");
{
	size_t size = 13;
	int * originalArr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		originalArr[i] = size - i;
	}

	int * arr = new int[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}

START_TEST(testWithInvertedSortedArray, "Test with inverted sorted array!");
{
	size_t size = 15;
	int * originalArr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		originalArr[i] = i;
	}

	int * arr = new int[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}

START_TEST(testWithFewTypesOfElements, "Test with few types of elements!");
{
	size_t size = 20;
	int * originalArr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		originalArr[i] = i % 3; // [0,2]
	}

	int * arr = new int[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}

START_TEST(testWith20000Elements, "Test with 20 000 elements!");
{
	size_t size = 20000;
	int * originalArr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		originalArr[i] = rand() % 1000; // [0,999]
	}

	int * arr = new int[size];

	EXECUTE_FOR_ALL_SORTS;

	END_TEST;
}


template <class T>
inline void Test<T>::getSummary(std::ostream & out)
{
	testWithRandomData(out);
	testWithEmptyArray(out);
	testWithOnyTypeOfElements(out);
	testWithSortedArray(out);
	testWithInvertedSortedArray(out);
	testWithFewTypesOfElements(out);
	// testWith20000Elements(out);
}