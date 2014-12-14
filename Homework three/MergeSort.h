#pragma once

#include "MySorter.h"

template <class T>
class MergeSort : public MySorter < T >
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
};



template <class T>
inline void MergeSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	CALC_TIME;
}

template <class T>
inline unsigned long long MergeSort<T>::getSortTime() const
{
	return sortTime;
}

template <class T>
inline const char* MergeSort<T>::description() const
{
	return "Merge sort";
}