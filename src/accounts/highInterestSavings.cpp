#include "highInterestSavings.hpp"
#include <iostream>
#include <iomanip>

const double highInterestSavings::MINIMUM_BALANCE = 2500.00;
const double highInterestSavings::INTEREST_RATE = 0.05;

highInterestSavings::highInterestSavings(string name, int accountNumber, double balance)
	: savingsAccount(name, accountNumber, balance) {
	minimumBalance = MINIMUM_BALANCE;
	interestRate = INTEREST_RATE;
}

highInterestSavings::highInterestSavings(string name, int accountNumber, double balance, double interestRate, double minimumBalance)
	: savingsAccount(name, accountNumber, balance, interestRate) {
	this->minimumBalance = minimumBalance;
}
	
double highInterestSavings::getMinimumBalance() {
	return minimumBalance;
}

bool highInterestSavings::verifyMinimumBalance(double amount) {
	return (balance - amount >= minimumBalance);
}

void highInterestSavings::withdraw(double amount) {
	if (verifyMinimumBalance(amount)) balance -= amount;
}

void highInterestSavings::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "High Interest Savings: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}
