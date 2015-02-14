#include <iostream>
#include "String.h"
#include "Utility.h"

std::ostream& operator<<(std::ostream& out, const String& string)
{
	if (string.string != NULL)
		out << string.string;

	return out;
}

String::String()
{
	setDefaultValues();
}

String::String(const char* other)
{
	copyFrom(other);
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const char* other)
{
	delete[] string;
	copyFrom(other);

	return *this;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		delete[] string;
		copyFrom(other);
	}

	return *this;
}

// Adds other char string to the end of existing one.

String& String::operator+=(const char* other)
{
	addFrom(getLength() + strLength(other) + 1, other); // + '\0'

	return *this;
}

// Adds other String to the end of existing one.

String& String::operator+=(const String& other)
{
	addFrom(getLength() + other.size + 1, other.string); // + '\0'

	return *this;
}

// Adds other char to the end of existing string.

String& String::operator+=(char ch)
{
	if (full())
		resize(capacity * 2);

	string[size - 1] = ch;
	string[size++] = '\0';

	return *this;
}

// Check of the strings have the same symbols.

bool String::operator==(const String& other) const
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

bool String::operator!=(const String& other) const
{
	return  !(*this == other);
}

// Returns a copy of the char element at the 'index' possition or throws exeption of the index is outside of the bounds of the array.

char String::operator[](int index) const
{
	if (index < 0 || index >= (int)size)
		throw "Invalid index of the string!";

	return string[index];
}

// Returns a pointer to the buffer in the memory.

const char* String::getString() const
{
	return string;
}

// Returns the length of the string

size_t String::getLength() const
{
	return size - 1;
}

bool String::isEmpty() const
{
	return size <= 1;
}

// Deletes the allocated memory.

String::~String()
{
	delete[] string;
}

// Sets the string to empty one.

void String::setDefaultValues()
{
	copyFrom(""); // Empty string.
}


bool String::full() const
{
	return size == capacity;
}

// Creates new char array for the data with the given capacity and copies the symbols there.

void String::resize(size_t newCapacity)
{
	char * temp = new char[capacity = newCapacity];
	strCopy(temp, string);
	delete[] string;
	string = temp;
}

// Creates a string from char* string.. if the pointer is null , creates a valid (empty) string.
// The capacity will be exacly the size of the needed string, maybe the string wont be changed in the feature, and it will be perfect world!

void String::copyFrom(const char * other)
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

void String::copyFrom(const String& other)
{
	size = other.size;
	capacity = other.capacity;
	string = new char[other.capacity];

	strCopy(string, other.string);
}

// Adds othe char string to the end of the existing one. If the buffer of existing has not enough space- creates new buffer with enough space.

void String::addFrom(size_t newSize, const char* other)
{
	if (newSize > capacity)
		resize((capacity * 2 > newSize) ? capacity * 2 : newSize); // resize the buffer with the bigger of: twice capacity and the newSize

	strCopy(string + getLength(), other);

	size = newSize;
}