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
	void swiftUp(T * data, size_t index) const;
};

template <class T>
inline void HeapSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	if (data != NULL && count > 0)
	{
		for (size_t i = 1; i < count; ++i) // first is alreade at the top...
		{
			swiftUp(data, i);
		}
	}

	CALC_TIME;
}

template <class T>
inline void HeapSort<T>::swiftUp(T * data, size_t index) const
{
	size_t i = index + 1;
	
	while (i-- > 0)
	{
		if (i > 0)
		{
			i = (i - 1) / 2;
		}
		if (data[i] < data[index])
		{
			std::swap(data[i], data[index]);
			index = i;
		}
	}
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
