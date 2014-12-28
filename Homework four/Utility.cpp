#include "Utility.h"

// Returns the length of the char string.

size_t strLength(const char* str)
{
	size_t length = 0;

	while (*str++)
	{
		++length;
	}

	return length;
}


void strCopy(char * dest, const char* src)
{
	if (dest && src)
	{
		do
		{
			*dest++ = *src;
		} while (*src++); // including '\0'

	}
}