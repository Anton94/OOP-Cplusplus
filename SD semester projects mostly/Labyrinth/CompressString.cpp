#include "CompressString.h"
#include "../Double linked list/DLList.h"
#include "Pair.h"


/*
	The idea is not to use the basic basic stuff like pointer and so... a little more SD.
	Use one DLList with the number of matches and the symbol. (list<int, char>)
	Look at it as a stack. Push the first symbol(1 matches). every move, looks whats on the top and fixed its matches if the next symbol is the top one.
	After that goes through the list as queues. From the back to the beginning and makes the compressed string.
	A not very clever solution, but it`s not just pointer and 2 strings... I don`t know, its something...
*/

String CompressString::basicCompress(const String& str)
{
	if (str.getLength() <= 1)
		return str;

	DLList<Pair<int, char>> list;

	const char * pStr = str.getString();

	// insert the first symbol data.
	list.push_back(Pair<int, char>(1, *pStr));

	// Goes to the second symbol.
	++pStr;

	// Makes variable to store the current pair....

	Pair<int, char> currentPair;

	while (*pStr)
	{
		currentPair = list.pop_back();
		
		// If last pushed symbol is the same as current one.
		if (currentPair.second == *pStr)
		{
			// Increments the count of the symbol by 1.
			currentPair.first += 1;

			// Adds it to the list
			list.push_back(currentPair);
		}
		// The symbol is diferent.
		else
		{
			// Adds the last symbol (and its count(pair)) to the list.
			list.push_back(currentPair);


			// Inserts the new symbol and it`s current count of 1.
			list.push_back(Pair<int, char>(1, *pStr));
		}

		++pStr;
	}

	// TO DO: double and so on digits.

	String compressedString(str.getLength()); // Default length, so it don`t resize...

	// Look at the lists as queue, start pop-ing from the front and pushes the chars in the result compressed list.
	while (!list.isEmpty())
	{
		currentPair = list.pop_front();

		// If the count is 1, don`t write it.
		if (currentPair.first > 1)
		{
			compressedString += CompressString::makeStringFromNumber(currentPair.first);
			//compressedString += '0' + currentPair.first;
		}

		// Writes the representing symbol.
		compressedString += currentPair.second;
	}

	return compressedString;
}

/// Returns a string, representing the given number, if it`s negative, it will be positive!
/// This is a little ugli, I use String only not to take care for deleting the memory aftar that.

String CompressString::makeStringFromNumber(int number)
{
	// I don`t care for negative numbers!
	if (number < 0)
		number = -number;

	int digitsCount = CompressString::digitsCount(number);
	
	char * pStringNumber = new char[digitsCount + 1];
	
	// moves the pointer to the end and writes term zero.
	pStringNumber += digitsCount;
	*pStringNumber = '\0';

	while (number)
	{
		*(--pStringNumber) = (number % 10) + '0';
		number /= 10;
	}


	String stringNumber = pStringNumber;

	delete[] pStringNumber;

	return stringNumber;
}

/// Returns the number of digits.

int CompressString::digitsCount(int number)
{
	int count = 1;

	if (number < 0)
		number = -number;

	while (number >= 10)
	{
		++count;
		number /= 10;
	}

	return count;
}



/*
	Here I use a pointers, search matches, bigest one and so on...
	(we will see what will come out of this...)
*/

/// For now one iteration only, we will seee....

String CompressString::notSoBasicCompress(const String& str)
{
	// More lenghth in worse case is UPUP -> 2(UP) which is 20% , so I make this size array. (for now twice array size)
	//	char * strAsArray = new char[str.getLength() + (str.getLength() < 5) ? 1 : (str.getLength() / 5) + 1]; // + 20% bat case + '\0'.
	char * pOriginalStr = new char[str.getLength() * 2];

	char * pStr = pOriginalStr;

	char * pStart = pStr;
	char * pStartIter = pStr;

	int partitionLength = 0;

	/// Goes to the 2nd symbol.
	++pStr;

	while (*pStr)
	{
		// Checks if the current symbol and the start pattition symbol matches.
		if (*pStartIter == *pStr)
		{
			// Goes to see w
		}
	}

	return pOriginalStr;
}