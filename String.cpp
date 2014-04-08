#include "String.h"

String::String() : string('\0'), length(0) {}

String::~String() {delete this->string;}

String::String(const String &s) : length(s.length) {
	this->string = new char[this->length + 1];
	memcpy(this->string, s.string, this->length);
	*(this->string + this->length) = '\0';
}

String::String(const char *s) : length(strlen(s)) {
	this->string = new char[this->length + 1];
	memcpy(this->string, s, this->length);
	*(this->string + this->length) = '\0';
}

String::String(const char s) : length(strlen(&s)) {
	this->string = new char[this->length + 1];
	memcpy(this->string, &s, this->length);
	*(this->string + this->length) = '\0';
}

String &String::operator=(const String &s) {
	if (&s == this) return *this;
	this->length = s.length;
	delete this->string;
	this->string = new char[this->length + 1];
	strcpy(this->string, s.string);
	return *this;
}

String &String::operator=(const char *s) {
	this->length = strlen(s);
	delete this->string;
	this->string = new char[this->length + 1];
	strcpy(this->string, s);
	return *this;
}

String &String::operator+=(const String &s) {
	this->length = this->length + s.length;
	char buff[this->length + 1];
	strcpy(buff, this->string);
	strcat(buff, s.string);
	delete this->string;
	strcpy(this->string, buff);
	return *this;
}

String String::operator+(const String &s) const {
	String newString(*this);
	newString += s;
	return newString;
}
		
bool String::operator==(const String &s) const {
	if (strcmp(this->string, s.string)) return false;
	return true;
}

bool String::operator==(const char *s) const {
	if (strcmp(this->string, s)) return false;
	return true;
}
			
bool String::operator!=(const String &s) const {
	if (strcmp(this->string, s.string)) return true;
	return false;
}

bool String::operator!=(const char *s) const {
	if (strcmp(this->string, s)) return true;
	return false;
}

std::ostream &operator<<(std::ostream &os, const String &s) {
	os << s.string;
	return os;
}

char *String::getString() {return this->string;}

float String::toFloat() {return atof(this->string);}

int String::toInt() {return atoi(this->string);}
