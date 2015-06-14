#pragma once

#include <string>
using std::string;

/*
	Knuth-Morris-Pratt algorithm but with a specify checks for domains validation.
*/

class KnuthMorrisPratt
{
public:
	KnuthMorrisPratt();

	// Sets the preprocessing for the matching word(domain).
	void setDomain(const string& d);

	// The searching for the domain in the given url, returns true if it`s in the url, otherwise returns false.
	bool searchInUrl(const char* url, size_t urlLength);

	~KnuthMorrisPratt();
private:
	// Sets the default values.
	void setDefaultValues();

	// Allocates the memory for the domain and the domain length.
	void setDomainValues(const string& d);

	// Deletes the allocated memory. NOTE: does not set the default values.
	void free();
private:
	char* domain;
	size_t domainLength;
	int * kmpNext;
private:
	// In this homework I don`t need to copy this object, so I 'ban' the copy constructor and assignment operator.
	KnuthMorrisPratt(const KnuthMorrisPratt& other);
	KnuthMorrisPratt& operator=(const KnuthMorrisPratt& other);
};