#include "String.h"

String::String() {
	m_string[m_length - 1] = '\0';
}

String::String(const char* string) {
	m_length = strlen(string) + 1;

	delete[] m_string;
	m_string = new char[m_length];
	for (int i = 0; i < m_length; i++) {
		m_string[i] = string[i];
	}
	m_string[m_length - 1] = '\0';
}

String::String(const String& other) {
	delete[] m_string;
	m_length = other.Length() + 1;
	m_string = new char[m_length];
	for (int i = 0; i < m_length; i++) {
		m_string[i] = other[i];
	}
}


size_t String::Length() const {
	return strlen(m_string);
}

String::~String() {
	delete[] m_string;
}

char& String::CharacterAt(size_t index) {
	
	if (index < m_length || index < 0) { return m_string[index]; }
	else return m_string[m_length -1];
}

bool String::EqualTo(String str) {
	for (int i = 0; i < m_length; i++) {
		if (m_string[i] != str[i]) return false;
	}
	return true;
}

void String::Append(String str) {
	char* m_newString = new char[m_length + str.Length()];
	for (int i = 0; i < Length(); i++) {
		m_newString[i] = m_string[i];
	}
	for (int i = Length(); i < m_length + str.Length(); i++) {
		m_newString[i] = str[i];
	}
	m_newString[Length() + str.Length()] = '\0';
	delete[] m_string;
	m_length += str.Length();
	m_string = m_newString;
}

void String::Prepend(String str) {
	char* m_newString = new char[str.Length() + m_length];
	for (int i = 0; i < str.Length(); i++) {
		m_newString[i] = str[i];
	}
	for (int i = str.Length(); i < str.Length() + m_length; i++) {
		m_newString[i] = m_string[i];
	}
	delete[] m_string;
	m_length += str.Length();
	m_string = m_newString;
}

const char* String::CStr() {
	return m_string;
}

void String::ToUpper() {	
	for (int i = 0; i < m_length; i++) {
		if (97 <= m_string[i] && m_string[i] <= 122) m_string[i] -= 32;
	}
}

void String::ToLower() {
	for (int i = 0; i < m_length; i++) {
		if (97 <= m_string[i] && m_string[i] <= 122) m_string[i] -= 32;
	}
}

size_t String::Find(String findString) {
	if (findString.Length() > m_length) return -1;
	for (int i = 0; i < m_length; i++) {
		for (int j = 0; j <= findString.Length(); j++) {
			if (j == findString.Length()) return i;
			if (m_string[i] != m_string[j]) {
				break;
			}
		}
	}
	return -1;
}

size_t String::Find(int startIndex, String findString) {
	if (startIndex + findString.Length() > m_length) return -1;
	for (int i = startIndex; i < m_length; i++) {
		for (int j = 0; j <= findString.Length(); j++) {
			if (j == findString.Length()) return i;
			if (m_string[i] != m_string[j]) {
				break;
			}
		}
	}
	return -1;
}

void String::Replace(String findString, String replaceString) {

}

void String::ReadFromConsole() {
	std::cin >> m_string;
}

void String::WriteToConsole() {
	std::cout << *m_string << std::endl;
}

bool String::operator == (const String& other) {
	if (m_length != other.m_length) return false;
	for (int i = 0; i < m_length; i++) {
		if (m_string[i] != other[i]) return false;
	}
	return true;
}

bool String::operator != (const String& other) {
	if (m_length != other.m_length) return true;
	for (int i = 0; i < m_length; i++) {
		if (m_string[i] != other[i]) return true;
	}
	return false;
}


String& String::operator = (const String& other) {
	delete[] m_string;
	m_length = other.Length();
	m_string = new char[m_length];
	for (int i = 0; i < m_length; i++) {
		m_string[i] = other[i];
	}

	String newString = String(m_string);

	return newString;
}

char& String::operator[](size_t index) {
	if (index > m_length) return m_string[m_length -1];
	return m_string[index];
}

const char& String::operator[](size_t index) const {
	if (index > m_length) return '\0';
	return m_string[index];
}

String& String::operator+ (const String& other) {
	String newString(m_string);
	char* m_newString = new char[m_length + other.Length()];
	for (int i = 0; i < m_length; i++) {
		m_newString[i] = m_string[i];
	}
	for (int i = m_length; i < m_length + other.Length(); i++) {
		m_newString[i] = other[i];
	}
	delete[] m_string;
	m_length += other.Length();
	return newString;
}

String& String::operator+= (const String& other) {
	char* m_newString = new char[m_length + other.Length()];
	for (int i = 0; i < m_length; i++) {
		m_newString[i] = m_string[i];
	}
	for (int i = m_length; i < m_length + other.Length(); i++) {
		m_newString[i] = other[i];
	}
	
	String newString = String(m_newString);
	
	delete[] m_string;
	delete[] m_newString;


	return newString;
}