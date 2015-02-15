#pragma once

#include "String.h"

class CompressString
{
public:
	static String basicCompress(const String& str);
	static String notSoBasicCompress(const String& str);
private:
	static String makeStringFromNumber(int number);
	static int digitsCount(int number);
};