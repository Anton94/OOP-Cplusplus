#include <iostream>
#include "Stack.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	//		lHighWaterCount	3435973836	unsigned int

	try
	{
		_CrtMemState s1;
		_CrtMemCheckpoint(&s1);
		{
			std::cout << "One linked stack (next element)\n";
			Stack<int> stack;
			for (int i = 0; i < 12; ++i)
			{
				stack.push(i * 11);
			}

			Stack<int> stackCopy(stack);

			for (int i = 0; i < 12; ++i)
			{
				std::cout << "Peek from stack -> " << stack.peek() << std::endl;
				stack.pop();
			}

			for (int i = 0; i < 12; ++i)
			{
				std::cout << "Peek from stackCopy -> " << stackCopy.peek() << std::endl;
				stackCopy.pop();
			}
		}
		_CrtMemDumpStatistics(&s1);
	}
	catch (const char* msg)
	{
		std::cerr << "Error: " << msg << std::endl;
	}
	return 0;
}