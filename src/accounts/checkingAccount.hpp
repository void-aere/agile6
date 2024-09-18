#pragma once

#include <string>
#include "bankAccount.hpp"

class checkingAccount : public bankAccount {
	public:
		checkingAccount(std::string name, int accountNumber, double balance);
		virtual void writeCheck(double amount) = 0;
};