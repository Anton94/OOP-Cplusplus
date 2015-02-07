#pragma once

#include "MySorter.h"

template <class T>
class QuickSort : public MySorter<T>
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
private:
	void quickSort(T * data, size_t count) const; // to get the time I need other function...
	size_t partition(T* data, size_t count) const;
};

template <class T>
inline void QuickSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	if (data != NULL && count > 1)
	{
		quickSort(data, count);
	}

	CALC_TIME;
}

template <class T>
void QuickSort<T>::quickSort(T * data, size_t count) const
{
	if (data != NULL && count > 1) // check again in any case...
	{
		size_t pos = partition(data, count);

		quickSort(data, pos);
		quickSort(data + pos + 1, count - pos - 1);
	}
}

template <class T>
size_t QuickSort<T>::partition(T* data, size_t count) const
{
	if (count == 2)
	{
		swapif(data[0], data[1]);
		return 1;
	}

	size_t middle = count / 2;
	swapif(data[0], data[middle]);
	swapif(data[0], data[count - 1]);
	swapif(data[middle], data[count - 1]);

	std::swap(data[middle], data[count - 2]);

	T& partitioningElement = data[count - 2];

	size_t left = 0;
	size_t right = count - 2;

	while (true)
	{
		while (data[++left] > partitioningElement)
			;

		while (data[--right] < partitioningElement)
		{
			if (left == right)
				break;
		}

		if (left >= right)
			break;

		std::swap(data[left], data[right]);
	}

	std::swap(data[left], partitioningElement);

	return left;
}


template <class T>
void swapif(T& a, T& b)
{
	if (b > a)
	{
		T temp(a);
		a = b;
		b = temp;
	}
}

template <class T>
inline unsigned long long QuickSort<T>::getSortTime() const
{
	return sortTime;
}

template <class T>
inline const char* QuickSort<T>::description() const
{
	return "Quick sort";
}
