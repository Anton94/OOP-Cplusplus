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

		while (!stack.isEmpty())
		{
			std::cout << stack.pop() << std::endl;
		}
	}
	catch (const char* msg)
	{
		std::cerr << "Error: " << msg << std::endl;
	}
	

	return 0;
}