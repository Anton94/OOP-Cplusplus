#pragma once

#include "String.h"

class CompressString
{
public:
	static String basicCompress(const String& str);
	static String makeStringFromNumber(int number);
private:
	static int digitsCount(int number);
};