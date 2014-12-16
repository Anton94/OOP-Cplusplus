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
