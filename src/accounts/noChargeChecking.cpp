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

void noChargeChecking::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	// minimumBalance = inputDouble("Minimum Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	std::cout << "Account has been created!\n";
}

void noChargeChecking::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Minimum Balance: " << minimumBalance << endl;
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

	prompt = confirm("\nWould you like to edit Minimum Balance? (Y/N): ");
	if (prompt)
	{
			minimumBalance = inputDouble("Enter the new Minimum Balance: ");
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
	std::cout << "Minimum Balance: " << minimumBalance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;

	return;
}