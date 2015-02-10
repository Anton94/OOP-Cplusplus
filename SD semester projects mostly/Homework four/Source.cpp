#include <iostream>
#include "MyString.h"
#include "Attributes.h"
#include "Tree.h"
#include "Utility.h"
#include <fstream>

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		std::ifstream in("testing.txt");
		std::ofstream out("output.txt");
		Tree tree;
		tree.buildTree(in, out);

		/*MyString * dirs = parseThePath("root/person", '/');
		size_t size = getCountDirectories("root/person", '/');

		for (size_t i = 0; i < size; ++i)
		{
			std::cout << dirs[i] << std::endl;
		}

		delete[] dirs;*/

		/*Attributes attributes;
		attributes.addAttribute("Tony", "Montana");
		attributes.addAttribute("Tony", "Montana");
		attributes.addAttribute("Tony", "Montana");
		out << attributes << "\n";*/

		in.close();
		out.close();
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}