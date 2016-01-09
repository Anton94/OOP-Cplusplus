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

int main()
{
	Tree tree1("(5 {(9 {}) (1 {(4 {}) (12 {}) (42 {})})})");
	//tree1.printDFS(std::cout);
	tree1.printBFS(std::cout);
	std::cout << std::endl;

	Tree tree2("(7{(15 {(7 {}) (10 {})}) (3 {(8 {})})})");
	//tree2.printDFS(std::cout);
	tree2.printBFS(std::cout);
	std::cout << std::endl;

	Tree tree3("(5 {(1 {(4 {}) (12 {}) (42 {})}) (9 {})})");
	//tree3.printDFS(std::cout);
	tree3.printBFS(std::cout);
	std::cout << std::endl;

	std::cout << "Isomorphism tree 1 and tree 2 (expects 0)? " << (tree1.isIsomorphWithOtherTree(tree2)) << std::endl;
	std::cout << "Isomorphism tree 1 and tree 3 (expects 1)? " << (tree1.isIsomorphWithOtherTree(tree3)) << std::endl;
	
	return 0;
}