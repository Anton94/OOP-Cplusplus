#include <iostream>

#include <list>

int main()
{
	std::list<int> list;
	list.push_back(5);
	std::list<int>::iterator it = list.begin();
	std::cout << *it;
	return 0;
}