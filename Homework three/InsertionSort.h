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
	
	if (data != NULL && count > 1)
	{
		for (size_t i = 1; i < count; ++i)
		{
			for (size_t j = i; j > 0 && data[j - 1] < data[j]; --j)
			{
				std::swap(data[j], data[j - 1]);
			}
		}
	}
	CALC_TIME;
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
