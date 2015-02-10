#include <iostream>
#include "Tree.h"

void executeExpr(const char* expr)
{
	std::cout << "Expression: " << expr << std::endl;
	Tree tree(expr);

	std::cout << "Tree printed in order: ";
	tree.printInOrder();
	std::cout << std::endl;
	std::cout << "Calc post order: " << tree.calcPostOrder() << std::endl;
	std::cout << "Calc in   order: " << tree.calcInOrder() << std::endl;
	std::cout << std::endl;
}

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{   
		executeExpr("2 3 4 + * 4 + 6 /");
		executeExpr("2 3 4 + * 4 + 6 / 1 + 2 -");
		executeExpr("2 3 4 + *");
		executeExpr("5 3 * 2 - 1 +");
	}


	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}