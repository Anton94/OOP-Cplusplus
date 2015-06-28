/*
*		
*		Name: Anton Vasilev Dudov
*		FN #: 71488
*
*		Github project: https://github.com/Anton94/OOP-Cplusplus/tree/master/DomainCounter
*
*		Used algorithm: Knuth Morris Pratt
*
*		From the given in our moodle course 'article' with algorithms- http://www-igm.univ-mlv.fr/~lecroq/string/index.html
*
*/

#include <iostream>
#include "DomainCounter.h"
#include "BasicArgumentParser.h"

using std::cout;


int main(int argc, char ** argv)
{
	// Checks for memory leaks.
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		DomainCounter domainCounter;
		BasicArgumentParser::parseTheInputArguments(argc, argv, domainCounter);

		if (!domainCounter.extractTheURLs())
			cout << "Something is wrong with input file :( \n";

		//domainCounter.printDomains(cout);
		//domainCounter.printProtocol(cout);
		//domainCounter.printUrls(cout);
		//cout << "\n\n";

		domainCounter.execute(cout);
	}

	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}

