#pragma once

#include "MyString.h"
#include "Vector.h"

class Path
{
public:
	Path(const MyString& str);
	MyString getCurrent();
	void increment();
	bool hasNext() const;
private:
	size_t current;
	Vector<MyString> path;
};