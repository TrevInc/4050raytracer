#include "String.h"

String::String() : string('\0'), length(0) {}

String::~String() {delete [] string;}

String::String(const String &s) : length(s.length) {
	string = new char[length + 1];
	strcpy(string, s.string);
}

String::String(const char *s) : length(strlen(s)) {
	string = new char[length + 1];
	strcpy(string, s);
}

String::String(const char s) : length(strlen(&s)) {
	string = new char[length + 1];
	strcpy(string, &s);
}

String &String::operator=(const String &s) {
	if (this == &s) return *this;
	length = s.length;
	delete [] string;
	string = new char[length + 1];
	strcpy(string, s.string);
	return *this;
}

String &String::operator=(const char *s) {
	length = strlen(s);
	delete [] string;
	string = new char[length + 1];
	strcpy(string, s);
	return *this;
}

String &String::operator+=(const String &s) {
	if (this == &s) return *this;
	if (string == '\0') return *this = s;
	length = length + s.length;
	char buff[length + 1];
	strcpy(buff, string);
	strcat(buff, s.string);
	delete [] string;
	string = new char[length + 1];
	strcpy(string, buff);
	return *this;
}

String String::operator+(const String &s) const {
	String string(*this);
	string += s;
	return string;
}
		
bool String::operator==(const String &s) const {
	if (strcmp(string, s.string)) return false;
	return true;
}

bool String::operator==(const char *s) const {
	if (strcmp(string, s)) return false;
	return true;
}
			
bool String::operator!=(const String &s) const {
	if (strcmp(string, s.string)) return true;
	return false;
}

bool String::operator!=(const char *s) const {
	if (strcmp(string, s)) return true;
	return false;
}

std::ostream &operator<<(std::ostream &os, const String &s) {
	os << s.string;
	return os;
}

char *String::getString() {return string;}

float String::toFloat() {return atof(string);}

int String::toInt() {return atoi(string);}
