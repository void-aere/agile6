#include "checkingAccount.hpp"
#include <iostream>

using std::string;

checkingAccount::checkingAccount(string name, int accountNumber, double balance)
	: bankAccount(name, accountNumber, balance) {}
