#include <iostream>
#include <string>
#include <iomanip>
#include "bankAccount.hpp"
#include "helpers.hpp"

#include "certificateOfDeposit.hpp"
#include "highInterestChecking.hpp"
#include "highInterestSavings.hpp"
#include "noChargeChecking.hpp"
#include "savingsAccount.hpp"
#include "serviceChargeChecking.hpp"

using std::string, std::cout, std::endl;

bankAccount::bankAccount(string name, int accountNumber, double balance) {
	this->name = name;
	this->accountNumber = accountNumber;
	this->balance = balance;
}

bankAccount::~bankAccount() { }

int bankAccount::getAccountNumber() const {
	return accountNumber;
}

int bankAccount::getID() const { return getAccountNumber(); }

double bankAccount::getBalance() const {
	return balance;
}

string bankAccount::getName() const {
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

void bankAccount::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);

	//std::cout << std::setw(30) << name << "  ";	
	//std::cout << std::setw(30) << accountNumber;
	//std::cout << std::setw(40) << " balance : $" << balance << std::endl;

	std::cout << name << " " << accountNumber << " balance : $" << balance << std::endl;
}

bankAccount* bankAccount::fromJson(const nlohmann::json& data) {
    // Skip this object if it doesn't have the "type" tag
    if (!data.contains("type")) return nullptr;
    std::string type = data.at("type");

    bankAccount* newAccount = nullptr;

    // Unfortunately I can't think of a more abstract polymorphic way to instantiate bank accounts
    // If you've got any ideas feel free to play around with them
    if      (type == "certificateOfDeposit")  newAccount = new certificateOfDeposit(data);
    else if (type == "highInterestChecking")  newAccount = new highInterestChecking(data);
    else if (type == "highInterestSavings")   newAccount = new highInterestSavings(data);
    else if (type == "noChargeChecking")      newAccount = new noChargeChecking(data);
    else if (type == "savingsAccount")        newAccount = new savingsAccount(data);
    else if (type == "serviceChargeChecking") newAccount = new serviceChargeChecking(data);

    return newAccount; 
}

string bankAccount::getFilename() const {
    return std::to_string(this->accountNumber) + ".json";
}

void bankAccount::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	std::cout << "Account has been created!\n";
}

void bankAccount::viewAccount() {
	std::cout << "Account Name: " << getName() << endl;
	std::cout << "Account Number: " << getID() << endl;
	std::cout << "Account Balance: " << getBalance() << endl;
}

void bankAccount::editAccountMenu() {
	int option = 0;
	do {
		clearScreen();
		std::cout << "Here are the current account (bankAccount) details:\n";
		viewAccount();

		std::cout << "What would you like to do?\n"
			   	 << "[1] Deposit Money\n"
					 << "[2] Withdraw Money\n"
					 << "[3] Change Name\n"
					 << "[4] Exit\n";

		option = getMenuOptionAuto(4);
				
		double tempAmount = 0.0;

		if (option == 1) {
			std::cout << "Enter the amount you would like to deposit: ";
			tempAmount = inputDouble();
			deposit(tempAmount);
		}
		else if (option == 2) {
			std::cout << "Enter the amount you would like to withdraw: ";
			tempAmount = inputDouble();
			withdraw(tempAmount);
		}
		else if (option == 3) {
			std::cout << "Enter the new name of the account: ";
			string newName = inputString();
			setName(newName);
		}

	} while (option != bankAccount::QUIT);
		
}

void bankAccount::oldEditAccountMenu() {
	bool prompt = false;
	
	std::cout << "Here are the current account details:\n";
	viewAccount();
	
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
	viewAccount();

	return;
}
