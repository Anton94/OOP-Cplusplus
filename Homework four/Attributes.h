#pragma once

#include "Attribute.h"
#include "../Double linked list/DLList.h"

class Attributes
{
	friend std::ostream& operator<<(std::ostream& out, Attributes& attributes);
public:
	void addAttribute(const MyString& name, const MyString& value);
	void removeAttribute(const MyString& name);
	~Attributes();
private:
	DLList<Attribute*> attributes;
};