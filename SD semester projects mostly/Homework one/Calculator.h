#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "Stack.h"
#include "Operations.h"

class Calculator
{
public:
	double calcExpr(const char* fileName, const char*& expr);
private:
	bool isOpen(char c) const;
	bool isOper(char c) const;
	double calc(double y, double x, char op) const;
	int getInt(const char*& str) const;
private:
	Stack<char> stOper;
	Stack<double> stNum;
	Operations operations;
};


#endif

