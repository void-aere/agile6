#include "checkingAccount.hpp"
#include <iostream>

checkingAccount::checkingAccount(string name, int accountNumber, double balance)
	: bankAccount(name, accountNumber, balance) {}
