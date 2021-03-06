#include "Attributes.h"

std::ostream& operator<<(std::ostream& out, const Attributes& val)
{
	for (DLList<Attribute*>::Iterator iter = const_cast<Attributes&>(val).attributes.begin(); iter != const_cast<Attributes&>(val).attributes.end(); ++iter)
	{
		out << " " << **iter;
	}

	return out;
}	

Attributes::Attributes(const Attributes& other)
{
	for (DLList<Attribute*>::Iterator iter = const_cast<Attributes&>(other).attributes.begin(); iter != const_cast<Attributes&>(other).attributes.end(); ++iter)
	{
		addAttribute((*iter)->getName(), (*iter)->getValue());
	}
}

void Attributes::addAttribute(const MyString& name, const MyString& value)
{
	attributes.push_back(new Attribute(name, value));
}

// Removes first match of attribute by it`s name (if exist) (one unique tag basicly, but...)

void Attributes::removeAttribute(const MyString& name)
{
	for (DLList<Attribute*>::Iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		if ((*iter)->getName() == name)
		{
			delete *iter;
			attributes.removeAt(iter);
			break;
		}
	}
}

// Edits first match of attribute by it`s name (if exist)(one unique tag basicly, but...)

void Attributes::editAttribute(const MyString& name, const MyString& newName, const MyString& newValue) 
{
	for (DLList<Attribute*>::Iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		if ((*iter)->getName() == name)
		{
			(*iter)->setName(newName);
			(*iter)->setValue(newValue);
			break;
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
