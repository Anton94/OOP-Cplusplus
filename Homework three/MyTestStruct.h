#pragma once

#include <iostream>
#include <vector>

// My type for testing, it can be with very big data if it needs... for now it`s only int value for comparation and some load for bad swapping!

struct MyTestStruct
{
	friend std::ostream& operator<<(std::ostream& out, MyTestStruct & val);
public:
	MyTestStruct& operator=(int val);
	bool operator==(const MyTestStruct& other);
	bool operator!=(const MyTestStruct& other);
	bool operator<(const MyTestStruct& other);
	bool operator>(const MyTestStruct& other);
private:
	int data;
	long long load[42];
};