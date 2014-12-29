#include "Tree.h"
#include "Utility.h"

Tree::Tree()
{
	root = new Tag;
	root->name = "root";
}

void Tree::buildTree(std::istream & in, std::ostream & out)
{
	MyString operation, path;

	while (true)
	{
		out << "Insert operation: ";

		// Get the operation.
		getWordFromIStream(in, operation);

		if (operation == "exit")
			break;

		// Get the path.
		getWordFromIStream(in, path);

		// Generate the array of dirs.
		MyString * dirs = parseThePath(path, '/');
		size_t size = getCountDirectories(path, '/');

		if (operation == "addTag")
		{
			Tag * tag = createTag(in, out);
			
			insertTag(root, tag, dirs, size);
			delete tag;
		}

		delete[] dirs;
	} 
}

// Insert a copy of the tag on every possible possition in the tree.

void Tree::insertTag(Tag * root, Tag * newTag, MyString* path, size_t size)
{
	// path dir is different than the dir, which is in at the moment- do nothing.
	if (size == 0 || root->name != *path)	 
		return;

	// The dir is last. (the name of the searched one and the current one match from above if case)
	if (size == 1)							
	{
		root->sons.push_back(new Tag(*newTag));
	}
	// size >= 2...
	else									
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			// If the child dir matches the name of searched subdir.
			if ((*iter)->name == *(path + 1)) 
				insertTag((*iter), newTag, path + 1, size - 1);
		}
	}
}

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