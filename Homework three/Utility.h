#pragma once

template <class T>
class Utility
{
public:
	static bool checkForSortedArray(T * data, size_t count);
	static void printArray(T * data, size_t count, std::ostream & out);
	static void copyTo(T * dest, T * source, size_t count);
};

template <class T>
inline bool Utility<T>::checkForSortedArray(T * data, size_t count)
{
	for (size_t i = 1; i < count; ++i)
	{
		if (data[i] > data[i - 1])
			return false;
	}

	return true;
}

template <class T>
inline void Utility<T>::printArray(T * data, size_t count, std::ostream & out)
{
	for (size_t i = 0; i < count; ++i)
		out << data[i] << " ";

	out << "\n";
}

// No guarantee for size and etc... If the world explode -> your fault!

template <class T>
inline void Utility<T>::copyTo(T * dest, T * source, size_t count)
{
	for (int i = 0; i < count; ++i)
		dest[i] = source[i];
}