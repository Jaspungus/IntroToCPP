#include "String.h"

//As it turns out, C-String functions are fine, so that means 814 less loops!
//Heeheehoo hahaho C-String functions make it so neat.

String::String() {
	m_string[0] = '\0';
}

// Working
//Creates a String based on a char array
String::String(const size_t a_size) {
	m_length = a_size + 1;
	m_string = new char[m_length];
	m_string[m_length] = '\0';
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

	//It copies each string to a temporary one.
	strcat_s(m_newString, newLength, m_string);
	strcat_s(m_newString, newLength, str.CStr());
	
	//Copies the temporary one back onto the original and deletes the temporary.
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

	//It copies each string to a temporary one.
	strcat_s(m_newString, newLength, str.CStr());
	strcat_s(m_newString, newLength, m_string);

	//Copies the temporary one back onto the original and deletes the temporary.
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

//Working
//I made this to do the Replace Function and then realised I didn't need it.
//It's still neat though.
String& String::ConcatAt(String str, size_t index) {
	m_length += str.Length();
	char* m_newString = new char[m_length];
	m_newString[0] = '\0';

	//Up until then new string, write the old string.
	for (size_t i = 0; i <= index; i++) {
		if (i == index) {
			m_newString[i] = '\0';
			break;
		}
		
		m_newString[i] = m_string[i];
	}

	//Add the new string.
	strcat_s(m_newString, m_length, str.CStr());

	//Finish adding the old string.
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


//Working
//Fetches the substring between start(inclusive) and end (exclusive).
String String::Substring(size_t start, size_t end) {
	
	if (start - end == 0) return String("\0");

	char* m_newString = new char[end - start + 1];
	m_newString[0] = '\0';

	for (size_t i = start; i < end; i++) {
		m_newString[i - start] = m_string[i];
	}
	m_newString[end - start] = '\0';
	
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
	return Find(0, findString);
}
//Finds the string, if it is not found, return -1. If found, return the index of the string.
//This one starts at a givent index and only checks after that point.
size_t String::Find(const int startIndex, String findString) {
	//If the given string exceeds the size of the original, or the index is out of bounds. Return -1.
	//The loop starts at startIndex. Otherwise it is identical.
	if (startIndex + findString.Length() > m_length || startIndex < 0) return -1;
	for (int i = startIndex; i < m_length; i++) {
		for (int j = 0; j <= findString.Length(); j++) {
			if (i + j >= findString.Length()) return -1;
			if (j == findString.Length()) return i;
			if (findString.ToLower()[j] != ToLower()[j + i]) {
				break;
			}
		}
	}
	return -1;
}

//Working
//This replaces all instances of findString with replaceString
//and dynamically scales the string etc.
String& String::Replace(String findString, String replaceString) {

	int replaceIndex = 0;

	//These two loops are near identical to the find function
	//I could probably be smart and use Find here, but that would require some
	//redesigning that I don't feel like doing.
	
	while(true) 
	{ 
		replaceIndex = Find(replaceIndex, findString); 
		if (replaceIndex == -1) break;
		//Increase m_length(null terminator inclusive) by the find and replace strings
		//excluding their terminators.
		m_length = m_length - findString.Length() + replaceString.Length();
		//Clear m_newString;
		char* m_newString = new char[m_length];
		m_newString[0] = '\0';
		String newStringInstance(m_newString);

		//This prevents it from appending nothing to the front of the string.
		//Otherwise it adds the string up to the replacement point onto an empty char[]
		if (replaceIndex > 0) newStringInstance.Append(Substring(0, replaceIndex));

		//Then it appends the replacement string in question.
		newStringInstance.Append(replaceString);

		//And then finishes by adding the string after the area to be replaced.
		//It will only do so if there is room left of the original string to insert on the end.
		if (replaceIndex + findString.Length() < m_length - 1) {
			newStringInstance.Append(Substring(replaceIndex + findString.Length(), m_length - 1));
		}

		//It then clears m_string and reinitialises it and copies over the temporary value.
		//The temporary value is then deleted and the original is returned, having had
		//The target string replaced.
		delete[] m_string;
		m_string = new char[m_length];
		m_string[m_length - 1] = '\0'; //Accidentally was setting this outside the array and it broke nasty.
		strcpy_s(m_string, strlen(newStringInstance.CStr()) + 1, newStringInstance.CStr());
		delete[] m_newString;

		//This makes sure that it skips over the newly inserted chars
		//Otherwise it could end up looping infinitely if the inserted string
		//contained the string to be replaced.
		replaceIndex += replaceString.Length();
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
	//Get line returns the entire line, including spaces.
	std::cin.getline(m_newString, MAXSTRINGLENGTH);
	

	//Clears m_string and copies the temporary value.
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