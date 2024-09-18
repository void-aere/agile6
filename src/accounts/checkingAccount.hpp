#pragma once
#define checkingAccount_hpp

#include <string>
#include "bankAccount.hpp"

class checkingAccount : public bankAccount {
	public:
		checkingAccount(string name, int accountNumber, double balance);
		virtual void writeCheck(double amount) = 0;
};
