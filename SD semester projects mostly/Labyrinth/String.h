#pragma once

#include <iostream>

class String
{
	friend std::ostream& operator<<(std::ostream& out, const String& string);
public:
	String();
	String(int capacitySize);
	String(const char* other);
	String(const String& other);
	String& operator=(const String& other);
	String& operator=(const char* other);
	String& operator+=(const String& other);
	String& operator+=(const char* other);
	String& operator+=(char ch);
	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;
	char operator[](int index) const;
	size_t getLength() const;
	char* getString();
	bool isEmpty() const;
	~String();
private:
	void setDefaultValues();
	bool full() const;
	void resize(size_t newCapacity);
	void initialResize(int newCapacity);
	void copyFrom(const char* other);
	void copyFrom(const String& other);
	void addFrom(size_t newSize, const char* other);
private:
	char * string;
	size_t size;
	size_t capacity;
};

