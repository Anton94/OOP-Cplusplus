#include <iostream>
#include "PersistentVector.h"


void testGetAt(int k, const PersistentVector<int>& v)
{
	std::cout << "vector.operator[" << k << "] = " << v[k] << std::endl;
}

void multipleTestsForGetAt(const PersistentVector<int>& v)
{
	testGetAt(0, v);
	testGetAt(16, v);
	testGetAt(31, v);
	testGetAt(32, v);
	testGetAt(567, v);
	testGetAt(1024, v);
	testGetAt(1021, v);
	testGetAt(1048, v);
	testGetAt(1056, v);
	testGetAt(31245, v);
}

int main()
{
	PersistentVector<int> pv1;
	PersistentVector<int> pv2 = pv1.append(5);
	PersistentVector<int> pv3 = pv1.append(15);
	PersistentVector<int> pv4 = pv3.append(35);

	testGetAt(0, pv2);
	pv2 = pv2.update(0, 101);
	testGetAt(0, pv2);
	/*pv1.print(std::cout);
	pv2.print(std::cout);
	pv3.print(std::cout);
	pv4.print(std::cout);*/

	const int COUNT = 32*33*32 + 1 + 1; // from 0 to 35  (so + 1 element for 0, and +1 for empty vector).

	// NOTE the first vector is empty one. so valus from 0 to count - 2 (count - 1 but the first one is empty)
	PersistentVector<int> arr[COUNT];

	for (int i = 0; i < COUNT - 1; ++i)
	{
		arr[i + 1] = arr[i].append(i);
	}

	//arr[COUNT - 1].print(std::cout);
	PersistentVector<int>  temp = arr[COUNT - 1];


	PersistentVector<int> updatedVector = temp.update(1024, 666);

	multipleTestsForGetAt(temp);
	multipleTestsForGetAt(updatedVector);


	return 0;
}

