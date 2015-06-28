#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "Utility.h"
#include "KnuthMorrisPratt.h"

using std::ifstream;
using std::ostream;
using std::string;
using std::vector;

class DomainCounter
{
public:
	// Default: constructor, copy constructor, assignment operator and destructor.
public:
	// Sets the input file name.
	void setInputFileName(const string& name);

	// Adds a domain to the vector of domains. I use vector of strings, because they will be at most 20 domains to check.
	void addDomain(const string& domain);

	// Sets the protocol. I use only one variable, because in this homework, we check for only one protocol, if there was more than one, I will use a vector of protocols(strings).
	void setProtocol(const string& p);

	// Writes the urls from the file to the vector of strings.
	// Returns false if the file is broken, or so.
	bool extractTheURLs();

	// Prints to the given ostream the results (number of matches for each given domain) in seperate lines. Pattern: "<domain_name> - <count>"
	void execute(ostream& out) const;

	// Prints the domains to the given ostream.
	void printDomains(ostream& out) const;

	// Prints the protocol to the given ostream.
	void printProtocol(ostream& out) const;

	// Prints the urls to the given ostream.
	void printUrls(ostream& out) const;
private:
	// Compares the given string(char*) if it starts with the proper protocol.
	bool checkForProtocol(const char*& url) const;
private:
	string inputFileName;
	vector<string> domains;
	string protocol;
	vector<string> urls;
};