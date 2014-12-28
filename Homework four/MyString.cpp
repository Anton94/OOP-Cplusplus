#include <iostream>
#include "MyString.h"
#include "Utility.h"

std::ostream& operator<<(std::ostream& out, const MyString& string)
{
	if (string.string != NULL)
		out << string.string;

	return out;
}

MyString::MyString()
{
	setDefaultValues();
}

MyString::MyString(const char* other)
{
	copyFrom(other);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const char* other)
{
	free();
	copyFrom(other);

	return *this;
}

// Adds other char string to the end of existing one.

MyString& MyString::operator+=(const char* other)
{
	addFrom(getLength() + strLength(other) + 1, other); // + '\0'

	return *this;
}

// Adds other MyString to the end of existing one.

MyString& MyString::operator+=(const MyString& other)
{
	addFrom(getLength() + other.size + 1, other.string); // + '\0'
	
	return *this;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

// Check of the strings have the same symbols.

bool MyString::operator==(const MyString& other) const
{
	if (size != other.size)
		return false;

	const char * left = string;
	const char * right = other.string;

	while (*left == *right++ && *left++ != '\0')
	{
	}

	return *--left == '\0';
}

bool MyString::operator!=(const MyString& other) const
{
	return  !(*this == other);
}

// Returns a copy of the char element at the 'index' possition or throws exeption of the index is outside of the bounds of the array.

char MyString::operator[](int index) const
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index of the string!";

	return string[index];
}

// Returns the length of the string

size_t MyString::getLength() const
{
	return size - 1;
}

// Deletes the allocated memory and sets the string to empty one.

void MyString::free()
{
	delete[] string;
	setDefaultValues();
}

bool MyString::isEmpty() const
{
	return size == 1;
}

// Deletes the allocated memory.

MyString::~MyString()
{
	delete[] string;
}

// Sets the string to empty one.

void MyString::setDefaultValues()
{
	size = capacity = 1;
	string = '\0';
}

// Creates new char array for the data with the given capacity and copies the symbols there.

void MyString::resize(size_t newCapacity)
{
	char * temp = new char[capacity = newCapacity];
	strCopy(temp, string);
	delete[] string;
	string = temp;
}

// Creates a string from char* string.. if the pointer is null , creates a valid (empty) string.
// The capacity will be exacly the size of the needed string, maybe the string wont be changed in the feature, and it will be perfect world!

void MyString::copyFrom(const char * other)
{
	if (!other)
	{
		setDefaultValues();
	}
	else
	{
		capacity = size = strLength(other) + 1; // + '\0'
		string = new char[capacity];
		strCopy(string, other);
	}
}

// Creates a copy of the given other string.

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	capacity = other.capacity;
	string = new char[other.capacity];

	strCopy(string, other.string);
}

// Adds othe char string to the end of the existing one. If the buffer of existing has not enough space- creates new buffer with enough space.

void MyString::addFrom(size_t newSize, const char* other)
{
	if (newSize > capacity)
		resize((capacity * 2 > newSize) ? capacity * 2 : newSize); // resize the buffer with the bigger of: twice capacity and the newSize

	strCopy(string + getLength(), other);
}