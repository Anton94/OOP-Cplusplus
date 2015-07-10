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
		//try
		{

			SpecialList<int> list;

			std::cout << "List is empty ? " << list.isEmpty() << std::endl;
			list.create(150);

			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);

			std::cout << "List is empty ? " << list.isEmpty() << std::endl;


			SpecialList<int> list2;
			list2.create(250);

			std::cout << "Add 250" << "\n";
			list.merge(list2);
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);
			std::cout << "Reverse" << "\n";
			list.reverse();
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);

			std::cout << "checking the merging with same height\n";

			SpecialList<int> list3, list4;
			list3.create(50);
			list4.create(-50);
			list3.merge(list4);
			list3.reverse();

			std::cout << "Add -50 50" << "\n";
			list.merge(list3);
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);

			std::cout << "Reverse" << "\n";
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

			std::cout << "Add 200 100 300 400" << "\n";

			list.merge(list5);
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);
			std::cout << "Reverse" << "\n";
			list.reverse();
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);

			SpecialList<int> list9;
			list9.create(-144);
			std::cout << "Reverse" << "\n";
			list.reverse();
			std::cout << "Add -144" << "\n";
			list.merge(list9);
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);

			SpecialList<int> list10;
			list10.create(450);

			std::cout << "Add 450" << "\n";
			list.merge(list10);
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);


			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);
			printListValues(list3, std::cout);
			printListMinMaxValues(list3, std::cout);

			for (int i = -5; i < 5; ++i)
			{
				list2.create(i);
				list3.merge(list2);
			}


			printListValues(list3, std::cout);
			printListMinMaxValues(list3, std::cout);

			list.merge(list3);

			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);
			std::cout << "Reverse" << "\n";
			list.reverse();
			printListValues(list, std::cout);
			printListMinMaxValues(list, std::cout);


		}
		//catch (const char* msg)
		{
		//	std::cerr << "Error: " << msg << "\n";
		}
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}


	return 0;
}