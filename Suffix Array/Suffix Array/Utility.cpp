

// Counts the number of same characters from the start of the two strings(given start).
unsigned numOfMatchesChars(const char* s1, const char* s2)
{
	//unsigned count = 0;
	const char * keepS1 = s1;
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		//++count;
		++s1;
		++s2;
	}

	return s1 - keepS1;
}