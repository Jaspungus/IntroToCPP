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
	const char& CharacterAt(size_t index) const;
	bool EqualTo(const String str);
	void Append(const String str);
	
	void Prepend(String str);
	const char* CStr() const;
	void ToLower();
	void ToUpper();
	size_t Find(const String findString);
	size_t Find(int startIndex, const String findString);
	void Replace(const String findString, const String replaceString);
	void ReadFromConsole();
	void WriteToConsole();

	
public:
	bool operator == (const String& other);
	bool operator != (const String& other);

	String& operator = (const String& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	const String operator+(const String& other) const;

	String& operator+=(const String& other);

private:
	size_t m_length = 1;
	char* m_string = new char[m_length];
	 
};

