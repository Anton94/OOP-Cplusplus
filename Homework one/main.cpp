#include <iostream>
#include <iomanip>
#include "Calculator.h"

int main(int argc , char * argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid count of arguments!";
		return 1;
	}
		
	const char* expr = argv[2];
	const char* originalExpr = expr;
	const char* fileName = argv[1];

	try
	{
		Calculator calculator;

		std::cout << originalExpr << " = "
			<< std::fixed << std::setprecision(2) 
			<< calculator.calcExpr(fileName, expr) 
			<< std::endl;
	}
	catch (const char* msg)
	{
		std::cout << originalExpr << std::endl;
		if (strstr(msg, "Stack is empty") != NULL)
			std::cout << "Error: Arguments and operators doesn`t match maybe @ \"" << expr << "\"" << std::endl;
		else
			std::cout << "Error: " << msg << " maybe at \"" << expr << "\"" << std::endl;
	}
	return 0;
}