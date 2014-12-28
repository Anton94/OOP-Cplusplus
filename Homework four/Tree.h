#pragma once

#include "Attributes.h"


class Tree
{
	struct Tag
	{
	public:
		MyString name;
		Attributes attributes;
		MyString text;
		DLList<Tag*> sons;
	};
public:
	Tree();
	void addTag(std::istream & in);
	void print(std::ostream & out) const;
	~Tree();
private:
	void print(const Tag * root, std::ostream & out, size_t indent) const;
	void printIndent(std::ostream & out, size_t indent) const;
	void deleteRoot(Tag * root);
private:
	Tag * root;
};