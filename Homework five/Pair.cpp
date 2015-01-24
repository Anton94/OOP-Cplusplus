#include "Pair.h"


template<class T, class Q>
Pair::Pair(const T& first, const Q& second)
{
	this->first = first;
	this->second = second;
}