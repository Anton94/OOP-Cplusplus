#include <iostream>
#include "Stack.h"

int main()
{
	try
	{
		std::cout << "One linked stack (next element)\n";
		Stack<int> stack;
		for (int i = 0; i < 12; ++i)
		{
			stack.push(i * 11);
		}

		for (int i = 0; i < 12; ++i)
		{
			std::cout << "Peek -> " << stack.peek() << std::endl;
			stack.pop();
		}
	}
	catch (const char* msg)
	{
		std::cerr << "Error: " << msg << std::endl;
	}
	return 0;
}