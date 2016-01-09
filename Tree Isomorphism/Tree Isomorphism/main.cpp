/*
 *
 *	Anton Vasilev Dudov
 *	Tree isomorphism 
 *	
 *
 *	
 *	The input tree is given with string like: (5 {(9 {}) (1 {(4 {}) (12 {}) (42 {})})})
 *	where the nedes are: (<value> { <children> })
 *	The given example is a root 5 with two children: left 9 and right 1. Right (1) has three children: 4, 12 and 42.
 */

#include <iostream>
#include "Tree.h"

void testFromTheTaskExamples()
{
	// From the taks file examples:
	Tree tree1("(5 {(9 {}) (1 {(4 {}) (12 {}) (42 {})})})");
	//tree1.printDFS(std::cout);
	tree1.printBFS(std::cout);
	std::cout << std::endl;

	Tree tree2("(7{(15 {(7 {}) (10 {}) (8 {})}) (3 {})})");
	//tree2.printDFS(std::cout);
	tree2.printBFS(std::cout);
	std::cout << std::endl;

	Tree tree3("(5 {(9 {}) (1 {(4 {}) (12 {}) (42 {})})})");
	//tree3.printDFS(std::cout);
	tree3.printBFS(std::cout);
	std::cout << std::endl;

	Tree tree4("(7{(15 {(7 {}) (10 {})}) (3 {(8 {})})})");
	//tree4.printDFS(std::cout);
	tree4.printBFS(std::cout);
	std::cout << std::endl;


	std::cout << "Isomorphism tree 1 and tree 2 (expects 1)? " << (tree1.isIsomorphWithOtherTree(tree2)) << std::endl;
	std::cout << "Isomorphism tree 3 and tree 4 (expects 0)? " << (tree3.isIsomorphWithOtherTree(tree4)) << std::endl;
}

int main()
{
	// Checks for memory leaks. Works only in VS (for example) the memory check.
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		testFromTheTaskExamples();
	}

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}