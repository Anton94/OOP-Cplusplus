#pragma once

#include "Sorter.h"

template <class T>
class InsertionSort : public Sorter<T>
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
};