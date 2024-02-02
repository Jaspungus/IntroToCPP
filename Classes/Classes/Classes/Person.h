#pragma once
#include <string>
using namespace std;

class Person
{
private:
	string m_name;
	int m_age;
	string m_country;

public:
	string GetName();
	void SetName(string a_name);

	int GetAge();
	void SetAge(int a_age);

	string GetCountry();
	void SetCountry(string a_country);

	Person();
	Person(string a_name, int a_age, string a_country);

};

