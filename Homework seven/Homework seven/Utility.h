#pragma once

#include <fstream>
using std::ifstream;


/*
Returns the number of lines in the input stream.
If the last row (or rows) is empty in the input file , it will count them, but it`s ok...
*/
size_t getNumberOfWords(ifstream& in);

/*
Get the length of next word in the input stream given as argument @in.
*/
size_t getLengthOfTheWord(ifstream& in);

/*
	Extracts a word from the in, creates the array and puts the data in it.
*/
bool getWord(ifstream& in, char *& word);

/*
	Gives the i-th bit of the given string (as char*).
*/
int getIthBitOfString(const char* word, int bit);

/*
Gives the i-th bit of the given char.
*/
int getIthBitOfSymbol(char ch, int bit);