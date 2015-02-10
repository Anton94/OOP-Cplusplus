#include <iostream>
#include <fstream>
#include "Operations.h"

// Get the operations from the file with name - 'fileName'
// The file is with correct content, no need for validation of the file data

void Operations::deserialize(const char* fileName)
{
	Operation op;
	std::ifstream file(fileName);

	if (!file)
		throw "The file cannot be open!";

	while (file)
	{
		file >> op.symbol;
		file >> op.operation;
		file >> op.priority;
		file >> op.associativity;
		if (!file)
			break;
		operations.push(op);
	}

	file.close();
}

// Print the operations...

void Operations::printOperations() const
{
	for (int i = 0; i < operations.getSize(); ++i)
	{
		std::cout << operations[i].symbol << " "
			<< operations[i].operation << " "
			<< operations[i].priority << " "
			<< operations[i].associativity << " "
			<< std::endl;
	}
}

// TO DO getPriorityBySymbol and getOperationBySymbol with pointer to function...

// get`s the operation priority by it`s symbol.
// if the operation is not in the vector of operations - throws exeption.

int Operations::getPriorityBySymbol(char op) const
{
	for (size_t i = 0; i < operations.getSize(); ++i)
	{
		if (operations[i].symbol == op)
			return operations[i].priority;
	}

	throw "Invalid operation!";
}

// get`s the operation priority by it`s symbol.
// if the operation is not in the vector of operations - throws exeption.

char Operations::getOperationBySymbol(char op) const
{
	for (size_t i = 0; i < operations.getSize(); ++i)
	{
		if (operations[i].symbol == op)
			return operations[i].operation;
	}

	throw "Invalid operation!";
}

// get`s the operation associativity by it`s symbol.
// if the operation is not in the vector of operations - throws exeption.

int Operations::getAssociativityBySymbol(char op) const
{
	for (size_t i = 0; i < operations.getSize(); ++i)
	{
		if (operations[i].symbol == op)
			return operations[i].associativity;
	}

	throw "Invalid operation!";
}