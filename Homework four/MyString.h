#pragma once

#include <iostream>

class MyString
{
	friend std::ostream& operator<<(std::ostream& out, const MyString& string);
public:
	MyString();
	MyString(const char* other);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	MyString& operator=(const char* other);
	MyString& operator+=(const MyString& other);
	MyString& operator+=(const char* other);
	MyString& operator+=(char ch);
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	char operator[](int index) const;
	size_t getLength() const;
	const char* getString() const;
	void free();
	bool isEmpty() const;
	~MyString();
private:
	void setDefaultValues();
	bool full() const;
	void resize(size_t newCapacity);
	void copyFrom(const char* other);
	void copyFrom(const MyString& other);
	void addFrom(size_t newSize, const char* other);
private:
	char * string;
	size_t size;
	size_t capacity;
};

