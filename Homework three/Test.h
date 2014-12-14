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
protected:
	bool checkForSortedArray(T * data, size_t count) const;
	void testWithRandomData(std::ostream & out) const;
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
	out << "Test with random elements!" << "\n";

	T arr[10] = { 1, 2, 3, 5, 88, 0, -2, 3, 7, 1 };
	

	for (int i = 0; i < count; ++i)
	{
		MySorter<T> * mySorter;
		if (mySorter = dynamic_cast<MySorter<T>*>(sorters[i]))
		{
			out << "  " << mySorter->description() << "->\n";
		}
		else
		{
			out << "  " << "Unknown sorting algorithm" << "\n";
		}

		out << "    " << "Array before sort: ";
		MySorter<T>::printArray(arr, 10, std::cout);

		sorters[i]->sort(arr, 10);

		out << "    " << "Array after  sort: ";
		MySorter<T>::printArray(arr, 10, std::cout);

		if (checkForSortedArray(arr, 10))
			out << "    " << "Test status: Passed!" << "\n";
		else
			out << "    " << "Test status: Failed!" << "\n";
	}
}


template <class T>
inline bool Test<T>::checkForSortedArray(T * data, size_t count) const
{
	for (size_t i = 1; i < count; ++i)
	{
		if (data[i] > data[i - 1])
			return false;
	}

	return true;
}

template <class T>
inline void Test<T>::getSummary(std::ostream & out)
{
	testWithRandomData(out);
}