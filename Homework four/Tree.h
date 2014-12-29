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
	void insertTag(Tag * root, Tag * newTag, const MyString* dirs, size_t dirsCount);
	void removeTag(Tag * root, const MyString* dirs, size_t dirsCount);
	Tag* createTag(std::istream & in, std::ostream & out); // out to print messages
	void printIndent(std::ostream & out, size_t indent) const;
	void deleteRoot(Tag * root);
	bool checkToAddAttribute(std::istream & in, std::ostream & out) const;
	bool isEmptyTag(const Tag * root) const;
	void printCloseTag(std::ostream & out, const Tag * root) const;
	bool executeOperation(std::istream & in, std::ostream & out, const MyString& operation);
	void addTag(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount);
private:
	Tag * root;
};