#pragma once

#include "Attributes.h"
#include "Path.h"

/*

#71488 FMI
Homework four

Github repository: https://github.com/Anton94/OOP-Cplusplus
Github project:	   https://github.com/Anton94/OOP-Cplusplus/tree/master/Homework%20four

TO FIX the const cast with something else, at the moment that`s the 'fix' I can make, so to work.

*/

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
	void printNoSpaces(std::ostream& out) const;
	~Tree();
private:
	bool executeOperation(std::istream & in, std::ostream & out, const MyString& operation);
	void deleteRoot(Tag * root);
	void print(const Tag * root, std::ostream & out, size_t indent) const;
	void printNoSpaces(const Tag * root, std::ostream & out) const;
	void printIndent(std::ostream & out, size_t indent) const;
	void printCloseTag(std::ostream & out, const Tag * root) const;
	bool isEmptyTag(const Tag * root) const;
	void addTag(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount);
	void addTag(Tag * root, Tag * newTag, const MyString* dirs, size_t dirsCount);
	void removeTag(Tag * root, const MyString* dirs, size_t dirsCount);
	void editTag(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount);
	void editTag(Tag * root, const Tag & newTag, const MyString* dirs, size_t dirsCount);
	void addAttribute(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount);
	void addAttribute(Tag * root, Attribute * newAttribute, const MyString* dirs, size_t dirsCount);
	void removeAttribute(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount);
	void removeAttribute(Tag * root, const MyString& newAttribute, const MyString* dirs, size_t dirsCount);
	void editAttribue(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount);
	void editAttribute(Tag * root, const MyString& attrName, const Attribute* newAttribute, const MyString* dirs, size_t dirsCount);
	Tag* createTag(std::istream & in, std::ostream & out) const;
	Attribute* createAttribute(std::istream & in, std::ostream & out) const;
	void editTagValues(Tag & tag, std::istream & in, std::ostream & out);
	Tag * findTag(Tag * root, const MyString* dirs, size_t dirsCount);
private:
	Tag * root;
};