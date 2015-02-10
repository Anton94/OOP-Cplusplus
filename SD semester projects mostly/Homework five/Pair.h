#pragma once

/*
	Struct Pair->simple for store some info with two values (may be different types).
*/

template <typename T, typename Q>
struct Pair
{
public:
	Pair(){};
	Pair(const T& first, const Q& second);
public:
	T first;
	Q second;
};


template<class T, class Q>
inline Pair<T, Q>::Pair(const T& first, const Q& second)
{
	this->first = first;
	this->second = second;
}