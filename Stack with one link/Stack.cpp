#include <iostream>
#include "Stack.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	try
	{
		_CrtMemState s1,s2,s3;
		_CrtMemCheckpoint(&s1);
		std::cout << "One linked stack (next element)\n";
		Stack<int> stack;
		for (int i = 0; i < 6; ++i)
		{
			stack.push(i * 11);
		}

		Stack<int> stackCopy;
		stackCopy = stack;

		while (!stack.isEmpty())
		{
			std::cout << "Peek from stack -> " << stack.peek() << std::endl;
			stack.pop();
		}

		while (!stackCopy.isEmpty())
		{
			std::cout << "Peek from stackCopy -> " << stackCopy.peek() << std::endl;
			stackCopy.pop();
		}		

		_CrtMemCheckpoint(&s2);

		if (_CrtMemDifference(&s3, &s1, &s2))
		{
			std::cout << "Memory leaks...\n";
			_CrtMemDumpStatistics(&s3);
		}
			
	}
	catch (const char* msg)
	{
		std::cerr << "Error: " << msg << std::endl;
	}
	return 0;
}