#pragma once

#include "Attributes.h"
#include "Path.h"


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
	void buildTree(std::istream & in, std::ostream & out);
	void print(std::ostream & out) const;
	~Tree();
private:
	void print(const Tag * root, std::ostream & out, size_t indent) const;
	void insertTag(Tag * root, Tag * newTag, Path path);
	Tag* createTag(std::istream & in, std::ostream & out); // out to print messages
	void printIndent(std::ostream & out, size_t indent) const;
	void deleteRoot(Tag * root);
	bool checkToAddAttribute(std::istream & in, std::ostream & out) const;
private:
	Tag * root;
};