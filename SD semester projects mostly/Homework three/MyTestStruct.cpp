#include "MyTestStruct.h"

std::ostream& operator<<(std::ostream& out, MyTestStruct & val)
{
	out << val.data;

	return out;
}

MyTestStruct& MyTestStruct::operator= (int val)
{
	data = val;

	return *this;
}

bool MyTestStruct::operator==(const MyTestStruct& other)
{
	return data = other.data;
}

bool MyTestStruct::operator!=(const MyTestStruct& other)
{
	return !operator==(other);
}

bool MyTestStruct::operator<(const MyTestStruct& other)
{
	return data < other.data;
}

bool MyTestStruct::operator>(const MyTestStruct& other)
{
	return data > other.data;
}