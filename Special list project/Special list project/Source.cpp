#include <iostream>
#include "SpecialList.h"

// Prints the values of the given list.
template<class T>
void printListValues(const SpecialList<T>& list, std::ostream& out)
{
	out << "List values: ";
	list.printValues(std::cout);
}

// Prints the min and max values of the given list.
template<class T>
void printListMinMaxValues(const SpecialList<T>& list, std::ostream& out)
{
	if (list.isEmpty())
		return;

	out << "Min value = " << list.getMin() << "\n";
	out << "Max value = " << list.getMax() << "\n";
}

int main()
{
	// Memory leaks cheching...
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		SpecialList<int> list;

		std::cout << "List is empty ? " << list.isEmpty() << std::endl;
		list.create(150);

		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);

		std::cout << "List is empty ? " << list.isEmpty() << std::endl;
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}


	return 0;
}