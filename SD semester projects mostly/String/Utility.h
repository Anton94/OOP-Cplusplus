#pragma once

#include <iostream>
#include "String.h"

size_t strLength(const char* str);
void strCopy(char * dest, const char* src);
void getLineFromIStream(std::istream & in, String& str);
void getWordFromIStream(std::istream & in, String& str);
void getDataFromIStream(std::istream & in, String& str, bool(*pFunc)(char ch));
bool checkNewLine(char ch);
bool checkNewWord(char ch);
String* parseThePath(const String& path, char delim, size_t size);
size_t getCountDirectories(const String& path, char delim);
bool checkForAction(std::istream & in, std::ostream & out, const String& msg);