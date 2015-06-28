#include "binomial_heap.h"

int main()
{

	////
	////	SOME STUPID VERY BASIC LAME TESTS...
	////
	////int * a = allocateDegreeArray(100);
	////int * b = allocateDegreeArray(64);

	////mergeTwoDegreesArray(a, b, sizeof(int)*8);

	//BinomialHeap<int> bh;

	//Node<int> * ptr = NULL;

	//const size_t NUMBER_OF_ELEMENTS = 65;
	//const size_t OFFSET = 0;
	//const size_t WHICH_ELEMENT_TO_KEEP = 0 + OFFSET;

	//for (size_t i = OFFSET; i < NUMBER_OF_ELEMENTS + OFFSET; ++i)
	//{
	//	if (i == WHICH_ELEMENT_TO_KEEP)
	//		ptr = bh.push(i);
	//	else
	//		bh.push(i);

	//	std::cout << "Get size = " << bh.getSize() << std::endl;
	//}

	////std::cout << "Get min = " << bh.getMin() << std::endl;
	////std::cout << "ptr->key = " << ptr->key << std::endl;
	////bh.decreaseKey(ptr, 5);
	////std::cout << "After decreasing Get min = " << bh.getMin() << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	////
	////for (size_t i = 0; i < NUMBER_OF_ELEMENTS - 1; ++i)
	////{ 
	////	std::cout << "Extracting the min element... " << bh.extractMin() << std::endl;
	////	std::cout << "The new min is: " << bh.getMin() << std::endl;
	////	std::cout << "Get size = " << bh.getSize() << std::endl;
	////}

	//const size_t ARR_SIZE = 64;

	//int * arr = new int[ARR_SIZE];
	//for (size_t i = 100; i < 100 + ARR_SIZE; ++i)
	//{
	//	arr[i - 100] = i;
	//}

	//BinomialHeap<int> bh2(arr, ARR_SIZE);


	////for (size_t i = 0; i < ARR_SIZE - 1 ; ++i)
	////{
	////	std::cout << "Extracting the min element... bh2 " << bh2.extractMin() << std::endl;
	////	std::cout << "The new min is: " << bh2.getMin() << std::endl;
	////}


	//BinomialHeap<int> bh3(bh2);
	//bh3.unite(bh);
	//std::cout << "Get size = " << bh3.getSize() << std::endl;

	
	return 0;
}