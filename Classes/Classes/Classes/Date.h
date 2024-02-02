#pragma once
class Date
{
private:
	int m_day;
	int m_month; 
	int m_year;

public:
	int GetDay();
	void SetDay(int a_day);

	int GetMonth();
	void SetMonth(int a_month);

	int GetYear();
	void SetYear(int a_year);

	bool Validate();
};

