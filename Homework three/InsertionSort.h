#pragma once

#include "MySorter.h"

template <class T>
class InsertionSort : public MySorter<T>
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
};

template <class T>
inline void InsertionSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	///**/
	//std::cout << "Sorting with 'Insertion sort...'" << std::endl;
	//MySorter<T>::printArray(data, count, std::cout);
	///**/

	for (size_t i = 1; i < count; ++i)
	{
		for (int j = i - 1; j >= 0 && data[j] < data[j + 1]; --j)
		{
			std::swap(data[j], data[j + 1]);
		}

		///**/
		//MySorter<T>::printArray(data, count, std::cout);
		///**/
	}

	CALC_TIME;

	///**/
	//std::cout << "Time: " << sortTime << std::endl;
	///**/
}

template <class T>
inline unsigned long long InsertionSort<T>::getSortTime() const
{
	return sortTime;
}

template <class T>
inline const char* InsertionSort<T>::description() const
{
	return "Insertion sort";
}
