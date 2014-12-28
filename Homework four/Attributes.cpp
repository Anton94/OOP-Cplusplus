#include "Attributes.h"

std::ostream& operator<<(std::ostream& out, Attributes& val) // to fix this TO DO
{
	for (DLList<Attribute*>::Iterator iter = val.attributes.begin(); iter != val.attributes.end(); ++iter)
	{
		out << " " << **iter;
	}

	return out;
}

void Attributes::addAttribute(const MyString& name, const MyString& value)
{
	attributes.push_back(new Attribute(name, value));
}
void Attributes::removeAttribute(const MyString& name) // Removes first match of attribute by it`s name (if exist)
{
	for (DLList<Attribute*>::Iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		if ((*iter)->getName() == name)
		{
			delete *iter;
			attributes.removeAt(iter);
		}
	}
}

Attributes::~Attributes()
{
	for (DLList<Attribute*>::Iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		delete *iter;
	}
}
