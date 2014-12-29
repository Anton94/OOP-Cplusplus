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

	delete[] dirs;

	return true;
}

// Creates a new tag with needed data and insert it in every possible position.

void Tree::addTag(std::istream & in, std::ostream & out, const MyString* dirs, size_t dirsCount)
{
	// 
	Tag * tag = createTag(in, out);

	insertTag(root, tag, dirs, dirsCount);

	delete tag;

}

// Insert a copy of the tag on every possible possition in the tree.

void Tree::insertTag(Tag * root, Tag * newTag, const MyString* dirs, size_t dirsCount)
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
				insertTag((*iter), newTag, dirs + 1, dirsCount - 1);
		}
	}
}

// Creates new Tag and returns a pointer to the tag (dynamic one). 

Tree::Tag* Tree::createTag(std::istream & in, std::ostream & out)
{
	Tag * root = new Tag;
	out << "Enter tag name: ";
	getLineFromIStream(in, root->name);

	while ((checkToAddAttribute(in, out)))
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

// Print the tree from the root (some kind of in ordered).

void Tree::print(std::ostream & out) const
{
	print(root, out, 0);
	out << "\n";
}

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

// Prints ('indent') blank spaces 

void Tree::printIndent(std::ostream & out, size_t indent) const
{
	while (indent--)
		out << " ";
}

void Tree::deleteRoot(Tag * root)
{
	for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
	{
		deleteRoot(*iter);
	}

	delete root;
}

// Check if the use whant`s to add attribute. If he enter "y" or "Y" returns true, in any other case returns false.

bool Tree::checkToAddAttribute(std::istream & in, std::ostream & out) const
{
	out << "Add attribute? (y?) ";

	MyString str;

	getLineFromIStream(in, str);
	
	return str == "y" || str == "Y";
}

Tree::~Tree()
{
	deleteRoot(root);
}