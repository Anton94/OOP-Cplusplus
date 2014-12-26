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
	free();
	copyFrom(other);

	return *this;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

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

// Returns the length of the string

size_t String::getLength() const
{
	return size - 1;
}

// Deletes the allocated memory and sets the string to empty one.

void String::free()
{
	delete[] string;
	setDefaultValues();
}

// Deletes the allocated memory.

String::~String()
{
	delete[] string;
}

// Sets the string to empty one.

void String::setDefaultValues()
{
	copyFrom("");
}

// Check if the the string is taken the all spots of the char dynamic char array.

bool String::full() const
{
	return size == capacity;
}

// Resize the char array (twice capacity).

void String::resize()
{
	capacity *= 2;
	char * temp = new char[capacity];

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
		copyFrom("");
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