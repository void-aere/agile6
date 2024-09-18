#include "savingsAccount.hpp"
#include <iostream>
#include <iomanip>

const double savingsAccount::INTEREST_RATE = 0.03;

savingsAccount::savingsAccount(string name, int accountNumber, double balance)
	: bankAccount(name, accountNumber, balance) {
	interestRate = INTEREST_RATE;
}

savingsAccount::savingsAccount(string name, int accountNumber, double balance, double interestRate)
	: bankAccount(name, accountNumber, balance) {
	this->interestRate = interestRate;
}

double savingsAccount::getInterestRate() {
	return interestRate;
}

void savingsAccount::setInterestRate(double interestRate) {
	this->interestRate = interestRate;
}

void savingsAccount::postInterest() {
	balance = 2 * balance * interestRate;
}

void savingsAccount::createMonthlyStatement() {
	postInterest();
}

void savingsAccount::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "Savings account: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}

