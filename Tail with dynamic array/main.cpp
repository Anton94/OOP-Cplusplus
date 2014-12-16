#include <iostream>
#include "Tail.h"

int main()
{
	Tail<int> tail1;

	std::cout << "Tail1:" << std::endl;

	for (int i = 0; i < 6; ++i)
	{
		tail1.enqueue(i);
		std::cout << "Enqueue(" << i << ")\n";
		std::cout << "Tail size = " << tail1.getSize() << std::endl;
	}

	Tail<int> tail2 = tail1;

	std::cout << "Tail1 :" << std::endl;

	for (int i = 0; i < 6; ++i)
	{
		std::cout << "Dequeue = " << tail1.dequeue() << std::endl;
		std::cout << "Tail size = " << tail1.getSize() << std::endl;
	}

	std::cout << "Tail2:" << std::endl;

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
	
	std::cout << "Tail1 :" << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		tail1.enqueue(i);
		std::cout << "Enqueue(" << i << ")\n";
		std::cout << "Tail size = " << tail1.getSize() << std::endl;
	}

	std::cout << "Tail1 :" << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		std::cout << "Peek() " << tail1.peek() << std::endl;
		std::cout << "Dequeue = " << tail1.dequeue() << std::endl;
		std::cout << "Tail size = " << tail1.getSize() << std::endl;
	}

	return 0;
}