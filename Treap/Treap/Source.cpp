#include <iostream>
#include "Treap.h"
#include <time.h>

#define NUMBER_OF_VALUES 20000


int main()
{
	// Memory leaks cheching...
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		//srand(time(NULL));
		Treap treap;
	
		for (int i = 0; i < NUMBER_OF_VALUES; ++i)
		{
			treap.insert(rand());
		}

		/*std::cout << "Printing the treap:" << std::endl;
		treap.print(std::cout);*/

		std::cout << std::endl;
		std::cout << "Valid heap ? " << treap.checkPriorities() << std::endl;
		std::cout << "Valid BST ? " << treap.checkKeys() << std::endl;
		std::cout << "Search for element 25667 ? " << treap.containsKey(25667) << std::endl;
		std::cout << "Search for element 123 ? " << treap.containsKey(123) << std::endl;
		std::cout << "Removes element 25667 and 123 " << std::endl;
		treap.remove(25667);
		treap.remove(123);

		std::cout << std::endl;
		/*std::cout << "Printing the treap:" << std::endl;
		treap.print(std::cout); */
		std::cout << std::endl;
		std::cout << "Valid heap ? " << treap.checkPriorities() << std::endl;
		std::cout << "Valid BST ? " << treap.checkKeys() << std::endl;
		std::cout << "Search for element 25667 ? " << treap.containsKey(25667) << std::endl;
		std::cout << "Search for element 123 ? " << treap.containsKey(123) << std::endl;
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}


	return 0;
}