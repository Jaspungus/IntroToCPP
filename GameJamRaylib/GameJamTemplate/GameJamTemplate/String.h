#pragma once
#include <iostream>

class String
{
public:
	String();
	String(const char* string);
	String(const size_t a_size);

	String(const String& other);

	~String();

public:
	size_t Length() const;

	char& CharacterAt(size_t index);
	const char& CharacterAt(size_t index) const;

	bool EqualTo(const String& str) const;

	String& Append(const String& str);
	String& Prepend(const String& str);
	String Substring(const size_t start, const size_t end);

	const char* CStr() const;

	String ToLower() const;
	String ToUpper() const;

	int Find(const String& findString) const;
	int Find(const int startIndex, const String& findString) const;

	String& Replace(const String& findString, const String& replaceString);


	String& ReadFromConsole();
	String& WriteToConsole();

public:
	static String IntToString(const int& other);
	static String IntToASCII(const int& other);

public:
	bool operator == (const String& other);
	bool operator != (const String& other);

	bool operator > (const String& other);
	bool operator < (const String& other);
	bool operator >= (const String& other);
	bool operator <= (const String& other);

	String& operator = (const String& other);


	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	const String operator+(const String& other) const;

	String& operator+=(const String& other);

private:
	size_t m_length = 1;
	char* m_string = nullptr;

};

