#pragma once

#include <iostream>
#include "MyString.h"

size_t strLength(const char* str);
void strCopy(char * dest, const char* src);
void getLineFromIStream(std::istream & in, MyString& str);
void getWordFromIStream(std::istream & in, MyString& str);
void getDataFromIStream(std::istream & in, MyString& str, bool(*pFunc)(char ch));
bool checkNewLine(char ch);
bool checkNewWord(char ch);