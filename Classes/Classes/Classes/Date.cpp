#include "Date.h"

int Date::GetDay()
{
    return m_day;
}

void Date::SetDay(int a_day) {
    m_day = a_day;
}

int Date::GetYear()
{
    return m_year;
}

void Date::SetMonth(int a_month) {
    m_month = a_month;
}

int Date::GetYear()
{
    return m_year;
}

void Date::SetYear(int a_year) {
    m_year = a_year;
}


bool Date::Validate() {
    
    if (m_day > 31) {
        return false;
    }

    if (m_month == 2) {
        if (m_year % 4 == 0 && m_day > 29) {
            return false;
        }
        else if (m_day > 28) {
            return false;
        }
    }

    if ((m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11) && m_day > 30) 
    {
        return false;
    }

    return true;
}
