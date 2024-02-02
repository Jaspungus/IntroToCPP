#include "Person.h"

string Person::GetName() {
	return m_name;
}

void Person::SetName(string a_name) {
	m_name = a_name;
}

int Person::GetAge() {
	return m_age;
}

void Person::SetAge(int a_age) {
	m_age = a_age;
}


string Person::GetCountry() {
	return m_country;
}

void Person::SetCountry(string a_country) {
	m_country = a_country;
}

Person::Person() {
	m_name = "";
	m_age = 0;
	m_country = "";
}

Person::Person(string a_name, int a_age, string a_country){
	m_name = a_name;
	m_age = a_age;
	m_country = a_country;
}