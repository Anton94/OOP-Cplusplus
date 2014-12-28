#include "Tree.h"

Tree::Tree()
{
	root = new Tag;
	root->name = "root";
}

void Tree::print(std::ostream & out) const
{
	print(root, out, 0);
}

void Tree::print(const Tag* root, std::ostream & out, size_t indent) const
{
	printIndent(out, indent);

	out << "<"
		<< root->name
		<< root->attributes;

	if (root->text.isEmpty() && root->sons.isEmpty()) // Empty tag
	{
		out << "/>\n";
	}
	else
	{
		out << ">\n"
			<< root->text
			<< "\n";

		for (DLList<Tag*>::Iterator iter = const_cast<Tag*>(root)->sons.begin(); iter != const_cast<Tag*>(root)->sons.end(); ++iter)
		{
			print(*iter, out, indent + 4);
		}

		out << "</"
			<< root->name
			<< ">\n";
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

Tree::~Tree()
{
	deleteRoot(root);
}