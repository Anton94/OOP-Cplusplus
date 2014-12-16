#pragma once

#include "MySorter.h"

template <class T>
class MergeSort : public MySorter < T >
{
public:
	virtual void sort(T * data, size_t count);
	virtual unsigned long long getSortTime() const;
	virtual const char* description() const;
private:
	void mergeSort(T * data, size_t count, T * buffer) const;
	void mergeArrays(T * left, T * right, size_t leftSize, size_t rightSize,  T* buffer) const;
};

template <class T>
inline void MergeSort<T>::sort(T * data, size_t count)
{
	START_TIME;

	if (data != NULL && count > 1)
	{
		T * buffer = new T[count];

		mergeSort(data, count, buffer);

		delete[] buffer;
	}


	CALC_TIME;
}


template <class T>
inline void MergeSort<T>::mergeSort(T * data, size_t count, T * buffer) const
{
	if (count <= 1)
		return;

	size_t half = count / 2;

	mergeSort(data, half, buffer);
	mergeSort(data + half, count - half, buffer + half);
	mergeArrays(data, data + half, half, count - half, buffer);

	Utility<T>::copyTo(data, buffer, count);
}

template <class T>
inline void MergeSort<T>::mergeArrays(T * left, T * right, size_t leftSize, size_t rightSize, T * buffer) const
{
	int leftI = 0,
		rightI = 0,
		bufferI = 0;

	while (leftI < leftSize && rightI < rightSize)
	{
		buffer[bufferI++] = (left[leftI] > right[rightI] ? left[leftI++] : right[rightI++]);
	}

	while (leftI < leftSize)
	{
		buffer[bufferI++] = left[leftI++];
	}

	while (rightI < rightSize)
	{
		buffer[bufferI++] = right[rightI++];
	}
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