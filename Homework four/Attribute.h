#pragma once

#include <iostream>
#include "MyString.h"

class Attribute
{
	friend std::ostream& operator<<(std::ostream& out, const Attribute & attribute);
public:
	Attribute(const MyString& name, const MyString& value);
	void setName(const MyString& str);
	void setValue(const MyString& str);
	const MyString& getName() const;
	const MyString& getValue() const;
private:
	MyString name;
	MyString value;
};