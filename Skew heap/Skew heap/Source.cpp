#include <iostream>
#include <crtdbg.h>
#include "SkewHeap.h"

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		// Some tests....
		SkewHeap<int> sh;

		for (int i = 0; i < 8; ++i)
		{
			sh.add(i);
		}

		std::cout << "Sh 1 : " << std::endl;

		sh.printInOrder();

		SkewHeap<int> shh;
		shh.add(8);
		shh.add(7);
		shh.add(90);
		std::cout << "Shh 2 : " << std::endl;
		shh.printInOrder();

		//sh.add(5);
		//sh.add(10);
		//sh.add(124);
		//sh.printInOrder();

		std::cout << "Merging..." << std::endl;

		sh.merge(shh);

		sh.printInOrder();

		std::cout << "Removes the min element" << std::endl;
		sh.removeMin();
		sh.printInOrder();
		
		/*
		// Other test... 
		SkewHeap<int> sk1;
		sk1.add(1);
		sk1.add(20);

		SkewHeap<int> sk2;
		sk2.add(201);

		SkewHeap<int> sk3;
		sk3.add(33);

		std::cout << "Sk 1: " << std::endl;
		sk1.printInOrder();
		std::cout << "Sk 2: " << std::endl;
		sk2.printInOrder();
		std::cout << "Sk 3: " << std::endl;
		sk3.printInOrder();


		std::cout << "\n\n\n Merge sk1.merge(sk2) " << std::endl;
		sk1.merge(sk2);

		std::cout << "Sk 1: " << std::endl;
		sk1.printInOrder();
		std::cout << "Sk 2: " << std::endl;
		sk2.printInOrder();
		std::cout << "Sk 3: " << std::endl;
		sk3.printInOrder();


		std::cout << "\n\n\n Merge sk2.merge(sk3) " << std::endl;
		sk2.merge(sk3);

		std::cout << "Sk 1: " << std::endl;
		sk1.printInOrder();
		std::cout << "Sk 2: " << std::endl;
		sk2.printInOrder();
		std::cout << "Sk 3: " << std::endl;
		sk3.printInOrder();



		std::cout << "\n\n\n Merge sk1.merge(sk3) " << std::endl;
		sk1.merge(sk3);

		std::cout << "Sk 1: " << std::endl;
		sk1.printInOrder();
		std::cout << "Sk 2: " << std::endl;
		sk2.printInOrder();
		std::cout << "Sk 3: " << std::endl;
		sk3.printInOrder();*/
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	else
	{
		std::cout << "Everything with the memory is OK!" << std::endl;
	}

	return 0;
}
