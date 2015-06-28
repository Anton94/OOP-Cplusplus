#include "binomial_heap.h"

int main()
{
	//int * a = allocateDegreeArray(100);
	//int * b = allocateDegreeArray(64);

	//mergeTwoDegreesArray(a, b, sizeof(int)*8);

	BinomialHeap<int> bh;

	for (size_t i = 0; i < 130; ++i)
		bh.push(i);

	return 0;
}