#pragma once

#include "Attribute.h"
#include "../Double linked list/DLList.h"

class Attributes
{
	friend std::ostream& operator<<(std::ostream& out, const Attributes& attributes);
public:
	Attributes(){}
	Attributes(const Attributes& other);
	void addAttribute(const MyString& name, const MyString& value);
	void removeAttribute(const MyString& name);
	void editAttribute(const MyString& name, const MyString& newName, const MyString& newValue);
	~Attributes();
private:
	DLList<Attribute*> attributes;
};