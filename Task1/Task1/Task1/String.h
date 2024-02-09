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
	
	bool EqualTo(const String str);

	String& Append(const String str);
	String& Prepend(String str);
	String& ConcatAt(String str, size_t index);
	//String& DeleteRange(size_t start, size_t end);
	String Substring(size_t start, size_t end);

	const char* CStr() const;
	
	String ToLower();
	String ToUpper();
	
	size_t Find(const String findString);
	size_t Find(const int startIndex, const String findString);
	
	String& Replace(const String findString, const String replaceString);
	String& Replace(const String findString, const String replaceString, size_t startIndex);


	String& ReadFromConsole();
	String& WriteToConsole();

	
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
	char* m_string;
	 
};

