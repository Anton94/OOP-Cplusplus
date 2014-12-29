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
		operation = path = "";
		getWordFromIStream(in, operation);

		if (operation == "exit")
			break;

		getWordFromIStream(in, path);

		if (operation == "addTag")
		{
			Tag * tag = createTag(in, out);

			insertTag(root, tag, Path(path));
			delete tag;
		}
	} 
}

// Insert a copy of the tag on every possible possition in the tree.

void Tree::insertTag(Tag * root, Tag * newTag, Path path)
{
	if (root->name != path.getCurrent()) // if the path is invalid ("") or the path dir is different than the dir , which is in at the moment- do nothing.
		return;

	path.increment();
	if (!path.hasNext())
	{
		root->sons.push_back(new Tag(*newTag));
	}
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			insertTag((*iter), newTag, path);
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

	if (root->text.isEmpty() && root->sons.isEmpty()) // Empty tag
	{
		out << "/>";
		return;
	}
	
	// Print the text.

	out << ">"
		<< root->text;


	if (!root->text.isEmpty() && root->sons.isEmpty())
	{
		out << "</"
			<< root->name
			<< ">";
	}
	else
	{
		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			out << "\n";
			print(*iter, out, indent + 4);
		}

		// close tag

		out << "\n";
		printIndent(out, indent);

		out << "</"
			<< root->name
			<< ">";
	}

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