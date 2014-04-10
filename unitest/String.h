#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <cstddef>
#include <iostream>
#include <cstdio>
#include <cstdlib>

class String {
	private:
		char *string;
		unsigned short int length;
	public:
		String();
		~String();
		String(const String &s);
		String(const char s);
		String(const char *s);
		String &operator=(const String &s);
		String &operator=(const char *s);
		String &operator+=(const String &s);
		String operator+(const String &s) const;
		bool operator==(const String &s) const;
		bool operator==(const char *s) const;
		bool operator!=(const String &s) const;
		friend std::ostream &operator<<(std::ostream &os, const String &s);
		char *getString();
		float toFloat();
		int toInt();
};

#endif
