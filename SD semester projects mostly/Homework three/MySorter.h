#pragma once

#include "Sorter.h"
#include <ctime>

#define START_TIME sortTime = time(NULL)
#define CALC_TIME  sortTime = time(NULL) - sortTime

template <class T>
class MySorter : public Sorter<T>
{
public:
	virtual void sort(T * data, size_t count) = 0;
	virtual unsigned long long getSortTime() const = 0;
	virtual const char* description() const = 0;
protected:
	unsigned long long sortTime;
};