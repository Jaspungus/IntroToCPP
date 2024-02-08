#include "String.h"

//As it turns out, C-String functions are fine, so that means 814 less loops!
//Heeheehoo hahaho C-String functions make it so neat.

String::String() {
	m_string[0] = '\0';
}

//Working
//Creates a String based on a char array
String::String(const char* string) {
	m_length = strlen(string) + 1;
	m_string = new char[m_length];
	strcpy_s(m_string, m_length, string);
}

//Working
//Creates a String by copying another String
String::String(const String& other) {
	m_length = other.Length() + 1;
	m_string = new char[m_length];
	strcpy_s(m_string, m_length, other.CStr());
}

String::~String() {
	delete[] m_string;
}

//Working
//Returns the length of the string. Exluding null space and anything afterwards.
size_t String::Length() const {
	return strlen(m_string);
}


//Working
//Returns the character at a given index. Returns a null space if index is out of range.
char& String::CharacterAt(size_t index) {
	if (index > m_length || index < 0) return m_string[m_length -1];
	return m_string[index];
}

//Working
//Returns the character at a given index. Returns a null space if index is out of range.
const char& String::CharacterAt(size_t index) const {
	if (index > m_length || index < 0) return '\0';
	return m_string[index];
}

//Working
//Compares two strings.
bool String::EqualTo(String str) {
	return (strcmp(m_string, str.CStr()) == 0);
}


//Working
//Appends another string to the end of the orginal.
String& String::Append(const String str) {
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

	return *this;
}

//Working
//Prepends another string to the beginning of the original.
String& String::Prepend(String str) {

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
	return *this;
}
//Working
//Returns the char array in String
const char* String::CStr() const {
	return m_string;
}

String& String::ConcatAt(String str, size_t index) {
	m_length += str.Length();
	char* m_newString = new char[m_length];
	m_newString[0] = '\0';

	for (size_t i = 0; i <= index; i++) {
		if (i == index) {
			m_newString[i] = '\0';;
			break;
		}
		
		m_newString[i] = m_string[i];
	}

	for (size_t i = 0; i <= index + str.Length(); i++) {
		if (i == index + str.Length()) {
			m_newString[i + index] = '\0';
			break;
		}

		m_newString[i + index] = str[i];
	}

	for (size_t i = 0; i <= m_length; i++) {
		if (i == m_length) {
			m_newString[i + index + str.Length()] = '\0';
			break;
		}
		
		m_newString[i + index + str.Length()] = m_string[i + index];
	}

	delete[] m_string;

	m_string = new char[m_length];
	strcpy_s(m_string, m_length, m_newString);

	delete[] m_newString;

	return *this;
}

//This is the festering corpse of my backwards solution to replace.
//I was going to delete the found string and stitch the sides together with DeleteRange
//And then insert the new string with ConcatAt.
//This is insane so I asked Josh and he pointed out a substring would work and be
//not completely absurd.
/*
String& String::DeleteRange(size_t start, size_t end) {

	if (start < 0 || start > Length() || end < 0 || end > Length()) return *this;
	m_length = m_length - (end - start);
	char* m_newString = new char[m_length];

	for (size_t i = 0; i < start; i++) {
		m_newString[i] = m_string[i];
	}

	for (size_t i = end; i < m_length; i++) {
		m_newString[i - end] = m_string[i];
	}

	delete[] m_string;

	m_string = new char[m_length];
	strcpy_s(m_string, m_length, m_newString);

	delete[] m_newString;

	return *this;
}*/

String String::Substring(size_t start, size_t end) {
	
	char* m_newString = new char[end - start + 1];

	for (int i = start; i < end; i++) {
		m_newString[i - start] = m_string[i];
	}
	
	return String(m_newString);
}


//Working
//Converts each lowercase letter to uppercase by adding 32 (The gap between the two ASCII sets)
//Horrible deceptive document made it look like it returned a seperate string
//It likely returns itself. Nasty wretched header template. Very upset.
String String::ToLower() {
	String newString = String(*this);
	for (int i = 0; i < newString.Length() + 1; i++) {
		if (65 <= newString[i] && newString[i] <= 90) newString[i] += 32;
	}

	return newString;
}

//Working
//Converts each uppercase letter to lowercase by subtracting 32 (The gap between the two ASCII sets)
String String::ToUpper() {
	String newString(m_string);
	for (int i = 0; i < newString.Length() + 1; i++) {
		if (97 <= newString[i] && newString[i] <= 122) newString[i] -= 32;
	}
	return newString;
}

//Finds the string, if it is not found, return -1. If found, return the index of the string.
size_t String::Find(String findString) {
	//If the given string exceeds the size of the original. Return -1.
	if (findString.Length() > Length()) return -1;
	//Loop through each character in the original.
	for (int i = 0; i < m_length; i++) {
		//For each character in the original, loop through again to search for a match.
		for (int j = 0; j <= findString.Length(); j++) {
			//If it reaches the end of the given string, return the index.
			if (j == findString.Length()) return i;
			//If the two strings no longer match, exit the inner loop.
			if (findString[j] != m_string[j + i]) {
				break;
			}
		}
	}
	return -1;
}
//Finds the string, if it is not found, return -1. If found, return the index of the string.
//This one starts at a givent index and only checks after that point.
size_t String::Find(const int startIndex, String findString) {
	//If the given string exceeds the size of the original, or the index is out of bounds. Return -1.
	//The loop starts at startIndex. Otherwise it is identical.
	if (startIndex + findString.Length() > m_length || startIndex < 0) return -1;
	for (int i = startIndex; i < m_length; i++) {
		for (int j = 0; j <= findString.Length(); j++) {
			if (j == findString.Length()) return i;
			if (findString[j] != m_string[j + i]) {
				break;
			}
		}
	}
	return -1;
}

String& String::Replace(String findString, String replaceString) {
	char* m_newString = new char[m_length];
	String newStringInstance(m_newString);
	int replaceIndex = -1;

	for (int i = 0; i < m_length; i++) {
		for (int j = 0; j <= findString.Length(); j++) {
			if (j == findString.Length()) replaceIndex = i;
			if (findString[j] != m_string[j + i]) {
				break;
			}
		}

		if (replaceIndex != -1) {
			delete[] m_newString;

			m_length += replaceString.Length();
			m_newString = new char[m_length];
			newStringInstance.Append(Substring(0, i)).Append(replaceString).Append(Substring(i + replaceString.Length(), m_length + replaceString.Length()));
				
			//	Substring(0, i) + replaceString + Substring(i + replaceString.Length(), m_length + replaceString.Length());
			i = -1;
		}
	}



	return *this;
}

//Working
//Takes an imput of max 100 chars. Sets the string to that. 
String& String::ReadFromConsole() {
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
	return *this;
}

//Working
//Discovered that despite the documents deviousness, Julian did make me realise that
//returning the String address of the string calling the function lets the results
//Interact with operators which is good.
//Anyway this just prints it to console.
String& String::WriteToConsole() {
	std::cout << m_string << std::endl;
	return *this;
}

//Working
//Uses EqualTo to compare if the value given is equal to the value stored.
bool String::operator == (const String& other) {
	
	return EqualTo(other);
}

//Working
//Uses EqualTo to compare if the value given is not equal to the value stored.
bool String::operator != (const String& other) {
	return !EqualTo(other);
}

//All of these just use strcmp to determine whether the first string is
//Greater than, less than, greater than or equal to, less than or equal to
//The second string given.
//It also works with char* due to implicit conversion.
bool String::operator > (const String& other) {
	return (strcmp(m_string, other.CStr()) == 1);
}

bool String::operator < (const String& other) {
	return (strcmp(m_string, other.CStr()) == -1);
}

bool String::operator >= (const String& other) {
	return (strcmp(m_string, other.CStr()) >= 0);
}

bool String::operator <= (const String& other) {
	return (strcmp(m_string, other.CStr()) <= 0);
}

//Working
//Sets the current value to the given value.
String& String::operator = (const String& other) {
	delete[] m_string;
	m_length = other.Length() + 1;
	m_string = new char[m_length];

	strcpy_s(m_string, m_length, other.CStr());
	
	return *this;
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
//Returns the result of appending the 2nd string to the 1st string.
const String String::operator + (const String& other) const {
		
	String newString(m_string);
	newString.Append(other);

	return newString;
}

//Working
//Appends the RHS to the LHS
String& String::operator += (const String& other) {
	Append(other);

	return *this;
}