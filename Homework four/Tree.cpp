#include "Tree.h"
#include "Utility.h"

Tree::Tree()
{
	root = new Tag;
	root->name = "root";
}

void Tree::buildTree(std::istream & in, std::ostream & out)
{
	MyString operation;

	do
	{
		out << "Insert operation: ";

		// Get the operation.
		getWordFromIStream(in, operation);

	} while (executeOperation(in, out, operation));
}

// Print the info with no spaces and formating

void Tree::printNoSpaces(std::ostream& out) const
{
	printNoSpaces(root, out);
	out << "\n";
}

// Print the tree from the root (some kind of in ordered).

void Tree::print(std::ostream & out) const
{
	print(root, out, 0);
	out << "\n";
}

Tree::~Tree()
{
	deleteRoot(root);
}

// Execute the given operation, if it is "exit" returns false, otherwise returns true.

bool Tree::executeOperation(std::istream & in, std::ostream & out, const MyString& operation)
{
	if (operation == "exit")
		return false;

	if (operation == "print")
	{
		print(std::cout); // TO DO
		return true;
	}

	// Get the path.
	MyString path;
	getWordFromIStream(in, path);

	// Parse the path to array of dirs.
	size_t dirsCount = getCountDirectories(path, '/');
	MyString * dirs = parseThePath(path, '/', dirsCount);

	if (operation == "addTag")
		addTag(in, out, dirs, dirsCount);
	else if (operation == "removeTag")
		removeTag(root, dirs, dirsCount);
	else if (operation == "editTag")
		editTag(in, out, dirs, dirsCount);
	else if (operation == "addAttribute")
		addAttribute(in, out, dirs, dirsCount);
	else if (operation == "removeAttribute")
		removeAttribute(in, out, dirs, dirsCount);
	else if (operation == "editAttribute")
		editAttribue(in, out, dirs, dirsCount);

	delete[] dirs;

	return true;
}

// Deletes the sons and after that deletes the memory , taken of the root.

void Tree::deleteRoot(Tag * root)
{
	for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
	{
		deleteRoot(*iter);
	}

	delete root;
}

// Prints the content of the tree with no indent and formating.

void Tree::print(const Tag* root, std::ostream & out, size_t indent) const
{
	printIndent(out, indent);

	out << "<"
		<< root->name
		<< root->attributes;

	if (isEmptyTag(root))
	{
		out << "/>";
		return;
	}

	out << ">"
		<< root->text;

	if (root->sons.isEmpty())
	{
		// close tag on same line.
		printCloseTag(out, root);
	}
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			out << "\n";
			print(*iter, out, indent + 4);
		}

		// close tag on new line.

		out << "\n";
		printIndent(out, indent);

		printCloseTag(out, root);
	}
}

// Print the info with no spaces and formating

void Tree::printNoSpaces(const Tag* root, std::ostream & out) const
{
	out << "<"
		<< root->name
		<< root->attributes;

	if (isEmptyTag(root))
	{
		out << "/>";
		return;
	}

	out << ">"
		<< root->text;

	if (root->sons.isEmpty())
	{
		// close tag on same line.
		printCloseTag(out, root);
	}
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			printNoSpaces(*iter, out);
		}

		// close tag on new line.

		printCloseTag(out, root);
	}
}

// Prints ('indent') blank spaces 

void Tree::printIndent(std::ostream & out, size_t indent) const
{
	while (indent--)
		out << " ";
}

// Prints close tag for the Tag.

void Tree::printCloseTag(std::ostream & out, const Tag * root) const
{
	out << "</"
		<< root->name
		<< ">";
}

// Checks if the tag is empty.

bool Tree::isEmptyTag(const Tag * root) const
{
	return root->text.isEmpty() && root->sons.isEmpty();
}

// Creates a new tag with needed data and insert it in every possible position.

void Tree::addTag(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount)
{
	Tag * tag = createTag(in, out);

	addTag(root, tag, dirs, dirsCount);

	delete tag;

}

// Insert a copy of the tag on every possible possition in the tree.

void Tree::addTag(Tag * root, Tag * newTag, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount == 0 || root->name != *dirs)
		return;

	// The dir is last. (the name of the searched one and the current one match from above if case)
	if (dirsCount == 1)
	{
		root->sons.push_back(new Tag(*newTag));
	}
	// size >= 2...
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			// If the child dir matches the name of searched subdir.
			if ((*iter)->name == *(dirs + 1))
				addTag((*iter), newTag, dirs + 1, dirsCount - 1);
		}
	}
}

// Insert a copy of the tag on every possible possition in the tree.

void Tree::removeTag(Tag * root, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount <= 1 || root->name != *dirs) // <= 1 can`t delete the root.
		return;

	for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
	{
		// If the child dir matches the name of searched subdir.
		if ((*iter)->name == *(dirs + 1))
		{
			if (dirsCount == 2) // this is the searched dir and search again for other match (a little ineffective for now). TO DO
			{
				deleteRoot((*iter));
				root->sons.removeAt(iter);
				removeTag(root, dirs, dirsCount);
				break;
			}
			else
			{
				removeTag((*iter), dirs + 1, dirsCount - 1);
			}
		}
	}
}

// Get the tag data and creates a new tag, changes the name or the text if it needs to and apply the changest to all tags that matches the path.

void Tree::editTag(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount)
{
	Tag tag;

	editTagValues(tag, in, out);

	editTag(root, tag, dirs, dirsCount);
}

// Edit every tag that match the path with the new 'name' and 'text'.

void Tree::editTag(Tag * root, const Tag & newTag, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount == 0 || root->name != *dirs)
		return;

	// The dir is last. (the name of the searched one and the current one match from above 'if case') Sets the new values if they are different.
	if (dirsCount == 1)
	{
		root->name = newTag.name;
		root->text = newTag.text;
	}
	// size >= 2...
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			// If the child dir matches the name of searched subdir.
			if ((*iter)->name == *(dirs + 1))
				editTag((*iter), newTag, dirs + 1, dirsCount - 1);
		}
	}
}

// Creates a new attribute with needed data and insert it in every possible position(every tag, on the given path).

void Tree::addAttribute(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount)
{
	Attribute * attribute = createAttribute(in, out);

	addAttribute(root, attribute, dirs, dirsCount);

	delete attribute;
}

// Insert the attribute in every tag with the given path.

void Tree::addAttribute(Tag * root, Attribute * newAttribute, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount == 0 || root->name != *dirs)
		return;

	// The dir is last. (the name of the searched one and the current one match from above if case)
	if (dirsCount == 1)
	{
		root->attributes.addAttribute(newAttribute->getName(), newAttribute->getValue());
	}
	// size >= 2...
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			// If the child dir matches the name of searched subdir.
			if ((*iter)->name == *(dirs + 1))
				addAttribute((*iter), newAttribute, dirs + 1, dirsCount - 1);
		}
	}
}

// Edits a attribute for every possible position(every tag, on the given path).

void Tree::editAttribue(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount)
{
	// Get the name of the attribute for change.
	MyString attrName;
	out << "Enter attribute name: ";
	getLineFromIStream(in, attrName);

	Attribute * newAttribute = createAttribute(in, out);
	editAttribute(root, attrName, newAttribute, dirs, dirsCount);
	delete newAttribute;
}

// Edits the attribute for every tag on the given path.

void Tree::editAttribute(Tag * root, const MyString& attrName, const Attribute* newAttribute, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount == 0 || root->name != *dirs)
		return;

	// The dir is last. (the name of the searched one and the current one match from above if case)
	if (dirsCount == 1)
	{
		root->attributes.editAttribute(attrName, newAttribute->getName(), newAttribute->getValue());
	}
	// size >= 2...
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			// If the child dir matches the name of searched subdir.
			if ((*iter)->name == *(dirs + 1))
				editAttribute((*iter), attrName, newAttribute, dirs + 1, dirsCount - 1);
		}
	}
}

// Delete a attribute from every possible position(every tag, on the given path).

void Tree::removeAttribute(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount)
{
	MyString attrName;
	out << "Enter attribute name: ";
	getLineFromIStream(in, attrName);
	removeAttribute(root, attrName, dirs, dirsCount);
}

// Removes the attribute from every tag on the given path.

void Tree::removeAttribute(Tag * root, const MyString& attrName, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount == 0 || root->name != *dirs)
		return;

	// The dir is last. (the name of the searched one and the current one match from above if case)
	if (dirsCount == 1)
	{
		root->attributes.removeAttribute(attrName);
	}
	// size >= 2...
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			// If the child dir matches the name of searched subdir.
			if ((*iter)->name == *(dirs + 1))
				removeAttribute((*iter), attrName, dirs + 1, dirsCount - 1);
		}
	}
}

// Creates new Tag and returns a pointer to the tag (dynamic one). 

Tree::Tag* Tree::createTag(std::istream & in, std::ostream & out) const
{
	Tag * root = new Tag;
	out << "Enter tag name: ";
	getLineFromIStream(in, root->name);

	while ((checkForAction(in, out, "Add attribute")))
	{
		MyString attrName, attrValue;
		out << "Enter attribute name: ";
		getLineFromIStream(in, attrName);
		out << "Enter attribute value: ";
		getLineFromIStream(in, attrValue);
		root->attributes.addAttribute(attrName, attrValue);
	}

	out << "Enter text: ";
	getLineFromIStream(in, root->text);

	return root;
}

// Creates new Attribute and returns a pointer to the attribute (dynamic one). 

Attribute* Tree::createAttribute(std::istream & in, std::ostream & out) const
{
	// It also can make with function in Attribute where it takes tha data itself
	// But this attributes can be from some precreated table of attributes and just a pointers to them, or something like that in the future, so I choose that way.
	MyString attrName, attrValue;
	out << "Enter attribute name: ";
	getLineFromIStream(in, attrName);
	out << "Enter attribute value: ";
	getLineFromIStream(in, attrValue);

	return new Attribute(attrName, attrValue);
}

// If the user want`s, sets new values for the name / text of the given tag.
// It can ask if whan`t to change the name and/or the text or neither in the future

void Tree::editTagValues(Tag & tag, std::istream & in, std::ostream & out)
{
	out << "Enter the new tag name: ";
	getLineFromIStream(in, tag.name);

	out << "Enter the new tag text: ";
	getLineFromIStream(in, tag.text);
}

// Returns the first match of tag on the given path. The search is based on the name of the tag, only the name (it can be based and on the attributes and text, but it will be ineffective to search, so only the name).

Tree::Tag * Tree::findTag(Tag * root, const MyString* dirs, size_t dirsCount)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (dirsCount <= 1 || root->name != *dirs) // <= 1 touch the root.
		return NULL;

	for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
	{
		// If the child dir matches the name of searched subdir.
		if ((*iter)->name == *(dirs + 1))
		{
			if (dirsCount == 2) // this is the searched dir - returns only the first match of the given tag name
				return *iter;
			else
				return findTag((*iter), dirs + 1, dirsCount - 1);
		}
	}
}
