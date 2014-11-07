#include <iostream>
#include "Tail.h"

int main()
{
	Tail<int> tail;

	for (int i = 0; i < 6; ++i)
	{
		tail.enqueue(i);
		std::cout << "Enqueue(" << i << ")\n";
		std::cout << "Tail size = " << tail.getSize() << std::endl;
	}

	Tail<int> tail2 = tail;

	std::cout << "Tail :" << std::endl;

	for (int i = 0; i < 6; ++i)
	{
		std::cout << "Dequeue = " << tail.dequeue() << std::endl;
		std::cout << "Tail size = " << tail.getSize() << std::endl;
	}

	std::cout << "Tail 2:" << std::endl;

	for (int i = 10; i < 18; ++i)
	{
		tail2.enqueue(i);
		std::cout << "Enqueue(" << i << ")\n";
		std::cout << "Tail size = " << tail2.getSize() << std::endl;
	}

	while(!tail2.isEmpty())
	{
		std::cout << "Dequeue tail 2= " << tail2.dequeue() << std::endl;
		std::cout << "Tail size = " << tail2.getSize() << std::endl;
	}
	

	for (int i = 0; i < 8; ++i)
	{
		tail.enqueue(i);
		std::cout << "Enqueue(" << i << ")\n";
		std::cout << "Tail size = " << tail.getSize() << std::endl;
	}

	for (int i = 0; i < 8; ++i)
	{
		std::cout << "Dequeue = " << tail.dequeue() << std::endl;
		std::cout << "Tail size = " << tail.getSize() << std::endl;
	}

	return 0;
}