#include "noChargeChecking.hpp"
#include <iomanip>
#include <iostream>

const double noChargeChecking::MINIMUM_BALANCE = 1000.00;
const double noChargeChecking::INTEREST_RATE = 0.02;

noChargeChecking::noChargeChecking(string name, int accountNumber, double balance)
	: checkingAccount(name, accountNumber, balance) {
	minimumBalance = MINIMUM_BALANCE;
	interestRate = INTEREST_RATE;
}

noChargeChecking::noChargeChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate)
	: checkingAccount(name, accountNumber, balance) {
	this->minimumBalance = minimumBalance;
	this->interestRate = interestRate;
}

double noChargeChecking::getMinimumBalance() {
	return minimumBalance;
}

void noChargeChecking::setMinimumBalance(double minimumBalance) {
	this->minimumBalance = minimumBalance;
}

bool noChargeChecking::verifyMinimumBalance(double balance) {
	return (balance >= minimumBalance);
}

void noChargeChecking::writeCheck(double amount) {
	withdraw(amount);
}

void noChargeChecking::withdraw(double amount) {
	if (verifyMinimumBalance(balance - amount)) balance -= amount;
}

void noChargeChecking::createMonthlyStatement() {}

void noChargeChecking::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "No Charge Checking: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}
