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
bool DomainCounter::extractTheURLs()
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
	size_t domainsSize = domains.size();
	size_t urlsSize = urls.size();
	KnuthMorrisPratt kmp;
	
	for (size_t i = 0; i < domainsSize; ++i)
	{
		out << domains[i] << " - ";

		kmp.setDomain(domains[i]);

		size_t count = 0;
		for (size_t j = 0; j < urlsSize; ++j)
		{
			const char * url = urls[j].c_str();
			if (checkForProtocol(url))
			{
				if (kmp.searchInUrl(url, urls[j].length()))
					++count;
			}
		}

		out << count << "\n";
	}
}

// Prints the domains to the given ostream.
void DomainCounter::printDomains(ostream& out) const
{
	out << "The domains are: \n";
	size_t count = domains.size();

	for (size_t i = 0; i < count; ++i)
		out << domains[i] << "\n";
}

// Prints the protocol to the given ostream.
void DomainCounter::printProtocol(ostream& out) const
{
	out << "The protocol is: \n";
	out << protocol << "\n";
}

// Prints the urls to the given ostream.
void DomainCounter::printUrls(ostream& out) const
{
	out << "The urls are: \n";
	size_t count = urls.size();

	for (size_t i = 0; i < count; ++i)
		out << urls[i] << "\n";
}

// Compares the given string(char*) if it starts with the proper protocol. CHANGES THE POSITION OF THE GIVEN URL, if it has compared the protocol, it will start the compare of the domain.
// If there is no protocol seted, it will start from the beginning but it`s ok.(A little tiny optimization to move the next 3 symbols "://", but for now Its OK)
bool DomainCounter::checkForProtocol(const char*& url) const
{
	if (protocol.length() <= 0)
		return true;

	const char * protocol = this->protocol.c_str();

	while (*protocol != '\0' && *url != '\0')
	{
		if (*protocol != *url)
			return false;
		++protocol;
		++url;
	}
	if (*url != ':')
		return false;

	return true;
}