#pragma once

#include "MySorter.h"

template <class T>
class HeapSort : public MySorter<T>
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
private:
	void Sift(T* data, size_t pos, size_t count) const;
};

template <class T>
inline void HeapSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	if (data != NULL && count > 0)
	{
		size_t i = count / 2;

		while (i--)
		{
			Sift(data, i, count);
		}
		i = count;

		while (--i)
		{
			std::swap(data[0], data[i]);
			Sift(data, 0, i);
		}
	}

	CALC_TIME;
}

template <class T>
void HeapSort<T>::Sift(T* data, size_t pos, size_t count) const
{
	T elem(data[pos]);

	size_t ni = pos;
	size_t si = pos * 2 + 1;

	while (si < count)
	{
		if (si < count - 1 && data[si] > data[si + 1])
			si++;

		if (elem < data[si])
			break;

		data[ni] = data[si];
		ni = si;
		si = si * 2 + 1;
	}

	data[ni] = elem;
}

template <class T>
inline unsigned long long HeapSort<T>::getSortTime() const
{
	return sortTime;
}

template <class T>
inline const char* HeapSort<T>::description() const
{
	return "Heap sort";
}
