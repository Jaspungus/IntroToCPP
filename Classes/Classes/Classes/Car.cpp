#include "Car.h"

string Car::GetCompany() {
	return m_company;
}

void Car::SetCompany(string a_company) {
	m_company = a_company;
}

string Car::GetModel() {
	return m_model;
}
void Car::SetModel(string a_model) {
	m_model = a_model;
}

int Car::GetYear() {
	return m_year;
}

void Car::SetYear(int a_year) {
	m_year = a_year;
}