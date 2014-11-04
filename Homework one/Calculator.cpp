#include <iostream>
#include "Calculator.h"

// check if the symbol is open bracket

bool Calculator::isOpen(char c) const
{
	return strchr("(", c) != NULL;
}

// check if the symbol is valid operation

bool Calculator::isOper(char op) const
{
	if (op != ' ' && op != '(' && op != ')') // getOperationBySymbol will throw exeption if the argument is not a valid operation
		return strchr("+-*/", operations.getOperationBySymbol(op)) != NULL;
	else
		return false;
}

// calculates the result of two numbers by the operation, passed as argument

double Calculator::calc(double y, double x, char op) const
{
	switch (op)
	{
	case '+': return x + y;
	case '-': return x - y;
	case '*': return x * y;
	case '/':
		if (y == 0)
			throw "Devision by zero!";
		else
			return x / y;
	}

	throw "Invalid operation!";
}

// gets the string, reads it and the original string starts with the last digit of the int

int Calculator::getInt(const char*& str) const
{
	const char* start = str;

	if (!(*str == '-' || (*str >= '0' && *str <= '9')))
	{
		throw "Wrong expression, expected int value!";
	}
	bool negative = false;
	int value = 0;

	if (*str == '-')
	{
		negative = true;
		++str;
	}

	while (*str != ' ' && *str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			throw "Wrong expression, expected int value!";

		value *= 10;
		value += *str - '0';

		++str;
	}

	if (start != str)
		--str; // back to last digit if the pointer is moved from the start possition

	if (negative)
		return -value;
	else
		return value;
}

// calculate the expression

double Calculator::calcExpr(const char* fileName, const char*& expr)
{
	const char* start = expr;
	operations.deserialize(fileName);

	while (*expr)
	{
		if ((*expr == '-' && *(expr + 1) != ' ') || (*expr >= '0' && *expr <= '9'))
		{
			stNum.push(getInt(expr));
		}
		else if (isOper(*expr))
		{
			while (!stOper.isEmpty())
			{
				char op = stOper.peek();
				if (op == '(')
					break;

				if (operations.getPriorityBySymbol(*expr) == operations.getPriorityBySymbol(op) && operations.getAssociativityBySymbol(op) != operations.getAssociativityBySymbol(*expr))
					throw "Right associativity and left associativity operations can`t be!";

				if (operations.getAssociativityBySymbol(*expr) == 1 && operations.getPriorityBySymbol(*expr) >= operations.getPriorityBySymbol(op))
				{
					break;
				}
				else if (operations.getAssociativityBySymbol(*expr) == 0 && operations.getPriorityBySymbol(*expr) > operations.getPriorityBySymbol(op))
				{
					break;
				}
				else
				{
					double y = stNum.pop();
					double x = stNum.pop();
					stNum.push(calc(y, x, operations.getOperationBySymbol(stOper.pop())));
				}
			}

			stOper.push(*expr);
		}
		else if (*expr == '(')
		{
			stOper.push(*expr);
		}
		else if (*expr == ')')
		{
			char c = stOper.pop();
			while (c != '(')
			{

				double y = stNum.pop();
				double x = stNum.pop();
				stNum.push(calc(y, x, operations.getOperationBySymbol(c)));
				c = stOper.pop();
			}

		}

		++expr;
	}

	while (!stOper.isEmpty())
	{
		double y = stNum.pop();
		double x = stNum.pop();
		stNum.push(calc(y, x, operations.getOperationBySymbol(stOper.pop())));
	}
	return stNum.pop();
}