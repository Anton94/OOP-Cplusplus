#include <iostream>
#include <vector>

/*
All the testing functions are in the vector of functions and all of them return a bool value and has no arguments.
macro #  -> makes the parameter to string.
macro ## -> concatenates two arguments with no blank space between them.
*/

#include <iostream>
#include <vector>
#include "../Tail with one link/Tail.h"

#define BEGIN(FNAME) bool FNAME(){ \
	std::cout << "Running test function: \n\t" << #FNAME << "() . . . ";

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
			std::cout << "succsess!\n" << std::endl;
		else
			std::cout << "fail!\n" << std::endl;
	}
}

BEGIN(checkPeekAndEnqueAndDequeSequence)
Tail<int> tail;

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
Tail<int> tail1;
for (int i = 0; i < 30; ++i)
{
	tail1.enqueue(i);
}

Tail<int> tail2 = tail1;
Tail<int> tail3;
tail3 = tail1;

for (int i = 0; i < 30; ++i)
{
	tail1.dequeue();
}

for (int i = 0; i < 30; ++i)
{
	if (i != tail2.peek())
		return false;

	if (i != tail2.dequeue())
		return false;
}

for (int i = 0; i < 30; ++i)
{
	if (i != tail3.peek())
		return false;

	if (i != tail3.dequeue())
		return false;
}

return true;

END()



BEGIN(checkTailSize)
Tail<int> tail;

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

END()


int main()
{
	ADD(checkPeekAndEnqueAndDequeSequence);
	ADD(checkCopyConstructorAndTheOperator);
	ADD(checkTailSize);

	Testing::executeTheTests();
	return 0;
}