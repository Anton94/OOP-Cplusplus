#include "DomainCounter.h"

// Sets the input file name.
void DomainCounter::setInputFileName(const string& name)
{
	inputFileName = name;
}

// Adds a domain to the vector of domains. I use vector of strings, because they will be at most 20 domains to check.
void DomainCounter::addDomain(const string& domain)
{
	domains.push_back(domain);
}
// Sets the protocol. I use only one variable, because in this homework, we check for only one protocol, if there was more than one, I will use a vector of protocols(strings).
void DomainCounter::setProtocol(const string& p)
{
	protocol = p;
}

// Writes the urls from the file to the vector of strings.
// Returns false if the file is broken, or so.
bool DomainCounter::ectractTheURLs()
{
	// Resize the vector with needed lines.
	size_t urlsSize = getNumberOfLinesFromFile(inputFileName);
	urls.resize(urlsSize);

	ifstream in(inputFileName);
	if (!in)
		return false;

	string url;

	for (size_t i = 0; i < urlsSize && in.good(); ++i)
	{
		getline(in, url, '\n'); // Each line has at most 1024 symbols, so the string is good enough for this purposes.
		if (!in)
			break;

		urls[i] = url;
	}

	in.close();
	return true;
}

// Prints to the given ostream the results (number of matches for each given domain) in seperate lines. Pattern: "<domain_name> - <count>"
void DomainCounter::execute(ostream& out) const
{

}

// Prints the urls to the given ostream.
void DomainCounter::printUrls(ostream& out) const
{
	size_t count = urls.size();

	for (size_t i = 0; i < count; ++i)
		out << urls[i] << "\n";
}