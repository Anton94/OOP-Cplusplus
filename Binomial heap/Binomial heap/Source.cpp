#include "binomial_heap.h"

int main()
{
	//int * a = allocateDegreeArray(100);
	//int * b = allocateDegreeArray(64);

	//mergeTwoDegreesArray(a, b, sizeof(int)*8);

	BinomialHeap<int> bh;

	Node<int> * ptr = NULL;

	for (size_t i = 20; i < 147; ++i)
	{
		if (i == 123)
			ptr = bh.push(i);
		else
			bh.push(i);
		
	}


	std::cout << "Get min = " << bh.getMin() << std::endl;
	std::cout << "ptr->key = " << ptr->key << std::endl;
	bh.decreaseKey(ptr, 10);
	std::cout << "After decreasing Get min = " << bh.getMin() << std::endl;
	return 0;
}