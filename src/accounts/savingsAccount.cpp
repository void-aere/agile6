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

void savingsAccount::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	std::cout << "Account has been created!\n";
}

void savingsAccount::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;

	prompt = confirm("\nWould you like to edit Account Name? (Y/N): ");
	if (prompt)
	{
		name = inputString("Enter the new Account Name: ");
	}

	prompt = confirm("\nWould you like to edit Account Number? (Y/N): ");
	if (prompt)
	{
			accountNumber = inputDouble("Enter the new Account Number: ");
	}

	prompt = confirm("\nWould you like to edit Account Balance? (Y/N): ");
	if (prompt)
	{
			balance = inputDouble("Enter the new Account Balance: ");
	}

	prompt = confirm("\nWould you like to edit Interest Rate? (Y/N): ");
	if (prompt)
	{
			interestRate = inputDouble("Enter the new Interest Rate: ");
	}

	std::cout << "\nHere are the new account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;

	return;
}



