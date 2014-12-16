/*
	1
	1 1
	2 1
	1 2 1 1
	1 1 1 2 2 1
	3 1 2 2 1 1
	1 3 1 1 2 2 2 1
	1 1 1 3 2 1 3 2 1 1
	................................
	
	one
	one ones
	two ones
	one twos, one ones 
	................................

	By one row and given "n" find the n-th row , starting from the given row

	Use list and add at the end and pop from the front maybe.
*/

#include <iostream>
#include <list>

// the result of the calculations is in the given list.
void printList(std::list<int> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << list.front() << " ";
		list.pop_front();
	}
	
	std::cout << std::endl;
}

void calculate(std::list<int> & list, int n)
{
	int x = list.front() , count = 0;

	list.push_back(0); // push 0 at the back to track the number of rows.

	while (n > 0)
	{
		if (x != list.front())
		{
			list.push_back(count);
			list.push_back(x);
			count = 0;

			if (list.front() == 0)
			{
				
				list.pop_front();
			//	printList(list);
				if (--n == 0)
				{
					break;
				}
				list.push_back(0);
			}
		}

		x = list.front();
		list.pop_front();
		++count;
	}


	std::cout << "BLA";
}

int main()
{
	std::list<int> list;
	list.push_front(1);
	list.push_front(1);

	calculate(list, 4);

	return 0;
}