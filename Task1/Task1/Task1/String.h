#pragma once
#include <iostream>

class String
{
public:
	String();
	String(const char* string);

	String(const String& other);

	~String();

public:
	size_t Length() const;
	char& CharacterAt(size_t index);
	bool EqualTo(String str);
	void Append(String str);
	void Prepend(String str);
	const char* CStr();
	void ToLower();
	void ToUpper();
	size_t Find(String findString);
	size_t Find(int startIndex, String findString);
	void Replace(String findString, String replaceString);
	void ReadFromConsole();
	void WriteToConsole();

	
public:
	bool operator == (const String& other);
	bool operator != (const String& other);

	String& operator = (const String& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	String& operator+(const String& other);
	String& operator+(const char&);

	String& operator+=(const String& other);
	String& operator+=(const char&);

private:
	size_t m_length = 1;
	char* m_string = new char[m_length];
	 
};

