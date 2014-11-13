#include <iostream>
#include <iomanip>
#include <vector>
#include "../Queue with one link/Queue.h"

/*
All the testing functions are in the vector of functions and all of them return a bool value and has no arguments.
macro #  -> makes the parameter to string.
macro ## -> concatenates two arguments with no blank space between them.
*/

#define BEGIN(FNAME) bool FNAME(){ \
	std::cout << "Running test: " << #FNAME << "() . . . \n\t";

#define END() }

#define ADD(FNAME) Testing::functions.push_back(FNAME);

// this class may be in testing.h but ...
class Testing
{
public:
	static void executeTheTests();
public:
	static std::vector<bool(*)()> functions;
};

std::vector<bool(*)()> Testing::functions;

void Testing::executeTheTests()
{
	size_t size = functions.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (functions[i]())
			std::cout << "Succsess!\n" << std::endl;
		else
			std::cout << "Fail!\n" << std::endl;
	}
}

BEGIN(checkPeekAndEnqueAndDequeSequence)
	Queue<int> tail;

	for (int i = 0; i < 30; ++i)
	{
		tail.enqueue(i);
	}

	for (int i = 0; i < 30; ++i)
	{
		if (i != tail.peek())
			return false;

		if (i != tail.dequeue())
			return false;	
	}

	return true;
END()



BEGIN(checkCopyConstructorAndTheOperator)
	Queue<int> tail1;
	for (int i = 0; i < 30; ++i)
	{
		tail1.enqueue(i);
	}

	Queue<int> tail2 = tail1;
	Queue<int> tail3;
	tail3 = tail1;

	for (int i = 0; i < 30; ++i)
	{
		tail1.dequeue();
	}

	for (int i = 0; i < 30; ++i)
	{
		if (i != tail2.peek())
			return false;
		
		if (tail2.getSize() != 30 - i)
			return false;

		if (i != tail2.dequeue())
			return false;
	}

	for (int i = 0; i < 30; ++i)
	{
		if (i != tail3.peek())
			return false;

		if (tail3.getSize() != 30 - i)
			return false;

		if (i != tail3.dequeue())
			return false;
	}

	return true;

END()


BEGIN(checkQueueSize)
	Queue<int> tail;

	for (int i = 0; i < 30; ++i)
	{
		tail.enqueue(i);
	}

	if (tail.getSize() != 30)
		return false;

	for (int i = 29; i >= 0; --i)
	{
		tail.dequeue();

		if (tail.getSize() != i)
			return false;
	}
	return true;
END()


BEGIN(checkWith1mElements)
	Queue<int> tail;
	for (int i = 0; i < 1000000; ++i)
	{
		tail.enqueue(i);
	}

	for (int i = 0; i < 1000000; ++i)
	{
		if (i != tail.dequeue())
			return false;
	}

	return true;
END()

BEGIN(checkPeekFromEmptyQueue)
	Queue<int> tail;
	try
	{
		tail.peek();
	}
	catch (const char* msg)
	{
		std::cout << "Error catched: [" << msg << "] \n\t";
		return true;
	}

	return false;
END()

BEGIN(checkDequeueFromEmptyQueue)
	Queue<int> tail;
	try
	{
		tail.dequeue();
	}
	catch (const char* msg)
	{
		std::cout << "Error catched: [" << msg << "] \n\t";
		return true;
	}

	return false;
END()

BEGIN(checkIterator)
	Queue<int> tail;
	for (int k = 0; k < 10; ++k)
	{
		tail.enqueue(k);
	}

	int i = 0;

	for (Queue<int>::Iterator it = tail.begin(); it; ++it, ++i)
	{
		if (i != *it)
			return false;
	}

	return true;
END()


int main()
{
	ADD(checkPeekAndEnqueAndDequeSequence);
	ADD(checkCopyConstructorAndTheOperator);
	ADD(checkQueueSize);
	ADD(checkWith1mElements);
	ADD(checkPeekFromEmptyQueue);
	ADD(checkDequeueFromEmptyQueue);
	ADD(checkIterator);

	Testing::executeTheTests();
	
	/*
	using namespace std;
	const size_t rows = 9;

	//set first row
	for (int i = 0; i < rows * 2; ++i)
	{
		cout << ((i % 2 == 0) ? "*" : " ");
	}
	cout << endl;

	for (int i = 2; i < rows; ++i)
	{
		cout << setw(i)  << "*" << setw(rows * 2 - i * 2) << "*" << endl;
	}

	// set last row
	cout << setw(rows) << "*" << endl;
	*/


	return 0;
}