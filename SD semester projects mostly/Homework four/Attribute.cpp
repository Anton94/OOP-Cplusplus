#include <iostream>
#include "Attribute.h"

std::ostream& operator<<(std::ostream& out, const Attribute& attribute)
{
	out << attribute.name
		<< " = \""
		<< attribute.value
		<< "\"";

	return out;
}

Attribute::Attribute(const MyString& name, const MyString& value)
{
	setName(name);
	setValue(value);
}

void Attribute::setName(const MyString& str)
{
	name = str;
}

void Attribute::setValue(const MyString& str)
{
	value = str;
}

// Returns a const referecne to the name.

const MyString& Attribute::getName() const
{
	return name;
}

// Returns a const referecne to the value.

const MyString& Attribute::getValue() const
{
	return value;
}