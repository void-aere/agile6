#include <iostream>
#include <string>
#include <iomanip>
#include "bankAccount.hpp"
#include "helpers.hpp"

using std::cout, std::endl;

bankAccount::bankAccount(string name, int accountNumber, double balance) {
	this->name = name;
	this->accountNumber = accountNumber;
	this->balance = balance;
}

int bankAccount::getAccountNumber() {
	return accountNumber;
}

double bankAccount::getBalance() {
	return balance;
}

string bankAccount::getName() {
	return name;
}

void bankAccount::setName(string name) {
	this->name = name;
}

void bankAccount::withdraw(double amount) {
	balance -= amount;
}

void bankAccount::deposit(double amount) {
	balance += amount;
}

void bankAccount::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << name << " " << accountNumber << " balance : $" << balance << std::endl;
}

void bankAccount::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	std::cout << "Account has been created!\n";
}

void bankAccount::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;

	prompt = confirm("\nWould you like to edit Account Name? (Y/N): ");
	if (prompt) {
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

	std::cout << "\nHere are the new account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl << endl;

	return;
}