#include "highInterestChecking.hpp"
#include <iostream>
#include <iomanip>

const double highInterestChecking::INTEREST_RATE = 0.05;
const double highInterestChecking::MINIMUM_BALANCE = 5000.00;

highInterestChecking::highInterestChecking(string name, int accountNumber, double balance)
	: noChargeChecking(name, accountNumber, balance) {
	minimumBalance = MINIMUM_BALANCE;
	interestRate = INTEREST_RATE;
}

highInterestChecking::highInterestChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate)
	: noChargeChecking(name, accountNumber, balance, minimumBalance, interestRate) {}

double highInterestChecking::getInterestRate() {
	return interestRate;
}

void highInterestChecking::setInterestRate(double interestRate) {
	this->interestRate = interestRate;
}

void highInterestChecking::postInterest() {
	balance = 2 * balance * interestRate;
}

void highInterestChecking::createMonthlyStatement() {
	postInterest();
}

void highInterestChecking::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "High Interest Checking: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}
