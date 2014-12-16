#pragma once

#include "MySorter.h"

template <class T>
class ShakerSort : public MySorter<T>
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
};

template <class T>
inline void ShakerSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	if (data != NULL && count > 1)
	{
		size_t left = 0;
		size_t right = count - 1;

		while (left < right)
		{
			for (size_t r = right; r > left; r--)
				if (data[r - 1] < data[r])
					std::swap(data[r - 1], data[r]);

			left++; // r - 1 so the left element will rotated...

			for (size_t l = left + 1; l <= right; l++)
				if (data[l - 1] < data[l])
					std::swap(data[l - 1], data[l]);

			right--;
		}
	}

	CALC_TIME;
}

template <class T>
inline unsigned long long ShakerSort<T>::getSortTime() const
{
	return sortTime;
}

template <class T>
inline const char* ShakerSort<T>::description() const
{
	return "Shaker sort";
}
