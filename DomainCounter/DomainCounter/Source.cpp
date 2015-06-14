
/*		Name: Anton Vasilev Dudov
*		FN:   71488
*		Github project: 
*
*
*
*
*
*
*/

#include <iostream>
#include "DomainCounter.h"

using std::cout;


void parseTheInputArguments(int argc, char**argv, DomainCounter& domainCounter);

int main(int argc, char ** argv)
{
	DomainCounter domainCounter;


	// TO DO sets the variables.
	domainCounter.setInputFileName("urls.txt");
	domainCounter.ectractTheURLs();
	domainCounter.printUrls(cout);

	return 0;
}




// VERY BASIC parse the arguments. This works with the homework type of arguments, were the command is like: "-<command_letter>" for example "-i","-d","-p"
// If the input is wrong, stops and works with the valid once.
void parseTheInputArguments(int argc, char**argv, DomainCounter& domainCounter)
{
	for (size_t i = 1; i < argc; ++i)
	{
		if (std::strlen(argv[i]) <= 1 && argv[i][0] == '-') // Wrong input argument.
			return;

		switch (argv[i][1]) // First one is '-', if the string is 1 long, this will be term null.
		{
		case 'i':
		{
			if (i + 1 < argc)
				domainCounter.setInputFileName(argv[i + 1]);
			break;
		}
		case 'd':
		{
			if (i + 1 < argc)
				domainCounter.addDomain(argv[i + 1]);
			break;
		}
		case 'p':
		{
			if (i + 1 < argc)
				domainCounter.setProtocol(argv[i + 1]);
			break;
		}
		default: // If the input argument is wrong, stops
			return;
		}
	}
}