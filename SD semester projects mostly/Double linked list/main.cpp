#include <iostream>
#include "DLList.h"

void testing()
{
	DLList<int> list;
	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	list.push_back(10);
	list.push_back(15);
	list.push_front(-20);
	list.push_front(-550);
	list.push_back(25);
	list.push_back(30);

	list += list;

	DLList<int> list2;
	list2 += list2;

	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	while (!list.isEmpty())
	{
		std::cout << "list.peek_front() = " << list.peek_front() << std::endl;
		std::cout << "list.pop_front() = " << list.pop_front() << std::endl;
		std::cout << "list.getSize() = " << list.getSize() << std::endl;
	}
	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	std::cout << std::endl;


	std::cout << "List2 is empty? = " << list2.isEmpty() << std::endl;
	while (!list2.isEmpty())
	{
		std::cout << "list2.peek_front() = " << list2.peek_front() << std::endl;
		std::cout << "list2.pop_front() = " << list2.pop_front() << std::endl;
		std::cout << "list2.getSize() = " << list2.getSize() << std::endl;
	}
	std::cout << "List2 is empty? = " << list2.isEmpty() << std::endl;
	std::cout << std::endl;


	list.push_front(10);
	list.push_front(15);
	list.push_front(20);
	list.push_back(25);
	list.push_back(30);

	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	while (!list.isEmpty())
	{
		std::cout << "list.peek_back() = " << list.peek_back() << std::endl;
		std::cout << "list.pop_back() = " << list.pop_back() << std::endl;
		std::cout << "list.getSize() = " << list.getSize() << std::endl;
	}
	std::cout << "List is empty? = " << list.isEmpty() << std::endl;

	std::cout << "Try to removeAt with iterator from empty list!" << std::endl;

	try
	{
		DLList<int>::Iterator it = list.begin();
		list.removeAt(it);
	}
	catch (const char* msg)
	{
		std::cout << "Catched error: " << msg << std::endl;
	}

	list.push_front(10);
	list.push_front(15);
	list.push_front(20);
	list.push_back(25);
	list.push_back(30);

	for (DLList<int>::Iterator it = list.begin(); it; ++it)
	{
		if (*it == 10)
			list.removeAt(it);

		std::cout << "list.getSize() = " << list.getSize() << std::endl;
	}

	for (DLList<int>::Iterator it = list.begin(); it; ++it)
	{
		std::cout << "El = " << *it << std::endl;
	}

	std::cout << "Try to removeAt with iterator from other list!" << std::endl;

	try
	{
		DLList<int>::Iterator it = list.begin();
		list2.removeAt(it);
	}
	catch (const char* msg)
	{
		std::cout << "Catched error: " << msg << std::endl;
	}
	std::cout << "PUSH BACK REVERSED" << std::endl;


	DLList<int> listForPushBackReversed;
	listForPushBackReversed.push_back(1);
	listForPushBackReversed.push_back(2);
	listForPushBackReversed.push_back(3);
	listForPushBackReversed.push_back(4); 
	DLList<int> listForPushBackReversed2;
	listForPushBackReversed2.push_back(10);
	listForPushBackReversed2.push_back(20);
	listForPushBackReversed2.push_back(30);

	listForPushBackReversed.push_back_reversed_list(listForPushBackReversed2);
	for (DLList<int>::Iterator it = listForPushBackReversed.begin(); it != listForPushBackReversed.end(); ++it)
	{
		std::cout << "El = " << *it << std::endl;
	}

	/// TESTS operator+= and iterator stuff...

	std::cout << "Test operator += and iterator stuff." << std::endl;

	DLList<char> tempArray;
	tempArray.push_back('a');
	tempArray.push_back('b');
	tempArray.push_back('c');
	tempArray.push_back('d');
	tempArray.push_back('e');
	tempArray.push_back('f');
	tempArray.push_back('g');

	DLList<char> tempArray2;
	DLList<char> tempArray3;
	tempArray2.push_back('z');
	tempArray2.push_back('w');

	for (DLList<char>::Iterator iter = tempArray.begin(); iter != tempArray.end(); ++iter)
	{
		if (*iter == 'c')
			tempArray3 += tempArray2;
		else
			tempArray3.push_back(*iter);
	}

	for (DLList<char>::Iterator iter = tempArray3.begin(); iter != tempArray3.end(); ++iter)
	{
		std::cout << (*iter) << " ";

	}


	std::cout << std::endl;
}
int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		
		testing();

	}


	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}