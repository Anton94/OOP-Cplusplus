#include <iostream>
#include "Stack.h"

int main()
{
	try
	{
		Stack <double> stack;
		for (int i = 0; i < 24; ++i)
		{
			stack.push(i * 2.14);
		}

		Stack <double> copy(stack);

		while (!stack.isEmpty())
		{
			std::cout << "From stack: " << stack.pop() << std::endl;
		}

		copy.push(666.66);

		while (!copy.isEmpty())
		{
			std::cout << "From copy: " << copy.pop() << std::endl;
		}
	}
	catch (const char* msg)
	{
		std::cerr << "Error: " << msg << std::endl;
	}
	

	return 0;
}