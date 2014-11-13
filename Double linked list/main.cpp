#include <iostream>
#include "DLList.h"


int main()
{
	/*
	DLList<int> list;
	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	list.push_back(10);
	list.push_back(15);
	list.push_front(20);
	list.push_back(25);
	list.push_back(30);

	DLList<int> list2;
	list2 = list;

	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	while (!list.isEmpty())
	{
	std::cout << "list.peek_front() = " << list.peek_front() << std::endl;
	std::cout << "list.pop_front() = " << list.pop_front() << std::endl;
	}
	std::cout << "List is empty? = " << list.isEmpty() << std::endl;
	std::cout << std::endl;


	std::cout << "List2 is empty? = " << list2.isEmpty() << std::endl;
	while (!list2.isEmpty())
	{
	std::cout << "list2.peek_front() = " << list2.peek_front() << std::endl;
	std::cout << "list2.pop_front() = " << list2.pop_front() << std::endl;
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
	}
	std::cout << "List is empty? = " << list.isEmpty() << std::endl;*
	*/

	DLList<int> list;
	list.push_front(10);
	list.push_front(15);
	list.push_front(20);
	list.push_back(25);
	list.push_back(30);
	
	for (DLList<int>::Iterator it = list.begin(); it; ++it)
	{
		if (*it == 10)
			list.removeAt(it);
	}

	

	for (DLList<int>::Iterator it = list.begin(); it; ++it)
	{
		std::cout << "El = " << *it << std::endl;
	}

	return 0;
}