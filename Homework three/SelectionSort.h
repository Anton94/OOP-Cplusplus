#pragma once

#include "MySorter.h"

template <class T>
class SelectionSort : public MySorter<T>
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
};

template <class T>
inline void SelectionSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	if (data != NULL && count > 1)
	{
		size_t maxLen = count - 1; // no need for last iteration

		for (size_t i = 0, maxIndex; i < maxLen; ++i)
		{
			maxIndex = i;
			for (size_t j = i + 1; j < count; ++j)
			{
				if (data[maxIndex] < data[j])
				{
					maxIndex = j;
				}
			}

			if (maxIndex != i)
				std::swap(data[maxIndex], data[i]);
		}
	}

	CALC_TIME;
}

template <class T>
inline unsigned long long SelectionSort<T>::getSortTime() const
{
	return sortTime;
}

template <class T>
inline const char* SelectionSort<T>::description() const
{
	return "Selection sort";
}
