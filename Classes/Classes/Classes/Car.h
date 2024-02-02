#pragma once
#include <string>
using namespace std;
class Car
{
private:
	string m_company;
	string m_model;
	int m_year;
public:
	string GetCompany();
	void SetCompany(string a_company);
	string GetModel();
	void SetModel(string a_model);
	int GetYear();
	void SetYear(int a_year);
};

