/*
*		
*		Name: Anton Vasilev Dudov
*		FN #: 71488
*
*		Github project: https://github.com/Anton94/OOP-Cplusplus/tree/master/DomainCounter
*
*		Used algorithm: Knuth-Morris-Pratt
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
	DomainCounter domainCounter;
	BasicArgumentParser::parseTheInputArguments(argc, argv, domainCounter);

	domainCounter.ectractTheURLs();
	domainCounter.printDomains(cout);
	domainCounter.printProtocol(cout);
	domainCounter.printUrls(cout);
	cout << "\n\n";

	domainCounter.execute(cout);
	return 0;
}

