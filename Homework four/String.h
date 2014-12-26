#ifndef STRING_H
#define STRING_H

#include <fstream>

class String
{
	friend std::ostream& operator<<(std::ostream& out, const String& string);
public:
	String();
	String(const char* str);
	String(const String& other);
	String& operator=(const String& other);
	String& operator=(const char* str);
	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;
	char operator[](int index) const;
	size_t getLength() const;
	void free();
	~String();
private:
	void setDefaultValues();
	bool full() const;
	void resize();
	void copyFrom(const char* other);
	void copyFrom(const String& other);
private:
	char * string;
	size_t size;
	size_t capacity;
};

#endif

