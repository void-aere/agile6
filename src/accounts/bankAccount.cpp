#include <iostream>
#include <string>
#include <iomanip>
#include "bankAccount.hpp"
#include "helpers.hpp"

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
	double floatTemp;

	std::cout << "Account Name: ";
	name = inputString();

	std::cout << "Account Number: ";
	accountNumber = inputDouble();

	std::cout << "Account Balance: ";
	balance = inputDouble();

	std::cout << "Account has been created!\n";
}

void bankAccount::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl << endl;

	prompt = confirm("Would you like to edit Account Name? (Y/N): ");
	if (prompt)
	{
		std::cout << "Enter the new Account Name: ";
		name = inputString();
	}

	prompt = confirm("Would you like to edit Account Number? (Y/N): ");
	if (prompt)
	{
		std::cout << "Enter the new Account Number: ";
			accountNumber = inputDouble();
	}

	prompt = confirm("Would you like to edit Account Balance? (Y/N): ");
	if (prompt)
	{
		std::cout << "Enter the new Account Balance: ";
			accountNumber = inputDouble();
	}

	std::cout << "Here are the new account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl << endl;

	return;
}