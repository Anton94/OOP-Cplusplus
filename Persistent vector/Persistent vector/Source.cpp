#include <iostream>
#include "PersistentVector.h"


int main()
{
	PersistentVector<int> pv1;
	PersistentVector<int> pv2 = pv1.append(5);
	PersistentVector<int> pv3 = pv1.append(15);
	PersistentVector<int> pv4 = pv3.append(35);
	pv1.print(std::cout);
	pv2.print(std::cout);
	pv3.print(std::cout);
	pv4.print(std::cout);

	const int COUNT = 32*32*32;

	// NOTE the first vector is empty one. so valus from 0 to count - 2 (count - 1 but the first one is empty)
	PersistentVector<int> arr[COUNT];

	for (int i = 0; i < COUNT - 1; ++i)
	{
		arr[i + 1] = arr[i].append(i);
	}

	arr[COUNT - 1].print(std::cout);

	return 0;
}