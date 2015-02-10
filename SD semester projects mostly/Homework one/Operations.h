#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include "Vector.h"

class Operations
{
public:
	void deserialize(const char* fileName);
	int getPriorityBySymbol(char op) const;
	char getOperationBySymbol(char op) const;
	int getAssociativityBySymbol(char op) const;
	void printOperations() const;
private:
	struct Operation
	{
		char symbol, operation;
		int priority, associativity;
	};
	Vector<Operation> operations;
};


#endif

