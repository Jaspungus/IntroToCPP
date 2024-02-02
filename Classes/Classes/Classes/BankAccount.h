#pragma once
#include <string>
#include <iostream>
using namespace std;


class BankAccount
{
private:
	string m_accNum;
	float balance;

public:
	void Deposit(float a_deposit);
	void Withdraw(float a_withdrawal);
};

