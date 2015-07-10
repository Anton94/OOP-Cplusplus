#include <iostream>
#include "SpecialList.h"

// Prints the values of the given list.
template<class T>
void printListValues(const SpecialList<T>& list, std::ostream& out)
{
	out << "List values: ";

	int size = list.getSize();
	for (int i = 1; i <= size; ++i)
		out << list.getAt(i) << " ";
	out << "\n";
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


		SpecialList<int> list2;
		list2.create(250);

		list.merge(list2);
		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);
		list.reverse();
		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);

		std::cout << "checking the merging with same height\n";

		SpecialList<int> list3, list4;
		list3.create(50);
		list4.create(-50);
		list3.merge(list4);
		//list3.reverse();
		printListValues(list3, std::cout);
		printListMinMaxValues(list3, std::cout);

		list.merge(list3);
		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);

		list.reverse();
		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);

		SpecialList<int> list5, list6;
		list5.create(100);
		list6.create(200);
		list5.merge(list6);
		SpecialList<int> list7, list8;
		list7.create(300);
		list8.create(400);
		list7.merge(list8);

		list5.reverse();
		list5.merge(list7);
		

		list.merge(list5);
		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);
		list.reverse();
		printListValues(list, std::cout);
		printListMinMaxValues(list, std::cout);

		vector<int> v;
		v.resize(3, 0);
		v.push_back(100);
		v.pop_back();
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}


	return 0;
}