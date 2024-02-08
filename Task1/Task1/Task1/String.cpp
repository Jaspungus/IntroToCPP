#include "String.h"

//As it turns out, C-String functions are fine, so that means 814 less loops!
//Heeheehoo hahaho C-String functions make it so neat.

String::String() {
	m_string[0] = '\0';
}

//Working
String::String(const char* string) {
	m_length = strlen(string) + 1;

	delete[] m_string;
	m_string = new char[m_length];
	strcpy_s(m_string, m_length, string);
}

//Working
String::String(const String& other) {
	delete[] m_string;
	m_length = other.Length() + 1;
	m_string = new char[m_length];
	strcpy_s(m_string, m_length, other.CStr());


	//for (int i = 0; i < m_length; i++) {
	//	m_string[i] = other[i];
	//}
}

//Working
size_t String::Length() const {
	return strlen(m_string);
}

String::~String() {
	delete[] m_string;
}

//Working
char& String::CharacterAt(size_t index) {
	if (index > m_length || index < 0) return m_string[m_length -1];
	return m_string[index];
}

//Working
const char& String::CharacterAt(size_t index) const {
	if (index > m_length || index < 0) return '\0';
	return m_string[index];
}


bool String::EqualTo(String str) {
	return (strcmp(m_string, str.CStr()) == 0);
}

//Working
void String::Append(const String str) {
	size_t newLength = m_length + str.Length();
	char* m_newString = new char[newLength];
	m_newString[0] = '\0';

	strcat_s(m_newString, newLength, m_string);
	strcat_s(m_newString, newLength, str.CStr());
	
	delete[] m_string;
	m_length = newLength;
	m_string = new char[m_length];
	strcpy_s(m_string, m_length, m_newString);

	delete[] m_newString;
}

//Working
void String::Prepend(String str) {

	size_t newLength = m_length + str.Length();
	char* m_newString = new char[newLength];
	m_newString[0] = '\0';

	strcat_s(m_newString, newLength, str.CStr());
	strcat_s(m_newString, newLength, m_string);

	delete[] m_string;
	m_length = newLength;
	m_string = new char[m_length];
	strcpy_s(m_string, m_length, m_newString);

	delete[] m_newString;
}
//Working
const char* String::CStr() const {
	return m_string;
}


//Working
void String::ToUpper() {	
	for (int i = 0; i < m_length; i++) {
		if (97 <= m_string[i] && m_string[i] <= 122) m_string[i] -= 32;
	}
}

//Working
void String::ToLower() {
	for (int i = 0; i < m_length; i++) {
		if (65 <= m_string[i] && m_string[i] <= 90) m_string[i] += 32;
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

//Working
void String::ReadFromConsole() {
	//536870911/3 was the largest char array size I could find.
	//It could be more precise. But I didn't want to. All I know is that anything much larger
	//Exceeds 2GB allocated memory.
	//Instead its a lame 100 max.
	const size_t MAXSTRINGLENGTH = 100;
	char m_newString[MAXSTRINGLENGTH];
	m_newString[0] = '\0';
	std::cin.getline(m_newString, MAXSTRINGLENGTH);
	
	delete[] m_string;

	m_length = strlen(m_newString) + 1;
	m_string = new char[m_length];

	strcpy_s(m_string, m_length, m_newString);
}

//Working
void String::WriteToConsole() {
	std::cout << m_string << std::endl;
}

//Working
bool String::operator == (const String& other) {
	
	return EqualTo(other);
}

//Working
bool String::operator != (const String& other) {
	return !EqualTo(other);
}

//Working
String& String::operator = (const String& other) {
	delete[] m_string;
	m_length = other.Length() + 1;
	m_string = new char[m_length];

	strcpy_s(m_string, m_length, other.CStr());

	String newString = String(m_string);

	return newString;
}

//Working??
char& String::operator[](size_t index) {
	if (index > m_length) return m_string[m_length -1];
	return m_string[index];
}

//Working??
const char& String::operator[](size_t index) const {

	if (index > m_length || index < 0) return '\0';
	return m_string[index];
}

//Working
const String String::operator+ (const String& other) const {
		
	String newString(m_string);
	newString.Append(other);

	return newString;
}

//Working
String& String::operator+= (const String& other) {
	Append(other);

	return *this;
}