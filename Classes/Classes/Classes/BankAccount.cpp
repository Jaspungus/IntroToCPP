#include "BankAccount.h"

void BankAccount::Deposit(float a_deposit) {
	balance += a_deposit;
	cout << "New Balance: " << balance << endl;
}

void BankAccount::Withdraw(float a_withdrawal) {
	balance -= a_withdrawal;
	cout << "New Balance: " << balance << endl;
}