#include "savingsAccount.hpp"
#include "helpers.hpp"
#include <iostream>
#include <iomanip>

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double savingsAccount::INTEREST_RATE = 0.03;

savingsAccount::savingsAccount(string name, int accountNumber, double balance)
	: savingsAccount(name, accountNumber, balance, INTEREST_RATE) { }

savingsAccount::savingsAccount(string name, int accountNumber, double balance, double interestRate)
	: bankAccount(name, accountNumber, balance) {
	this->interestRate = interestRate;
}

savingsAccount::savingsAccount(const json &j) 
    : savingsAccount(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("interestRate")) { }

savingsAccount::~savingsAccount() { }

double savingsAccount::getInterestRate() const {
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

void savingsAccount::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::setw(25) << std::left << "Savings account: ";
	std::cout << std::setw(20) << std::left << name;
	std::cout << " ACCT# ";
	std::cout << std::setw(10) << std::left << accountNumber;
	std::cout << " Balance: $";
	std::cout << std::setw(8) << std::left << balance << std::endl;
}

json savingsAccount::toJson() const {
    return json{
        {"name", name},
        {"accountNumber", accountNumber},
        {"balance", balance},
        {"interestRate", interestRate},
        {"type", "savingsAccount"}
    };
}

void savingsAccount::createAccountMenu() {

	std::cout << "Please enter the details for the Savings account you would like to create:\n";

	name = inputString("Account Name: ");

	accountNumber = bankAccount::generateAccountNumber(); // Generate random account number

	balance = inputDouble("Account Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	std::cout << "\nAccount has been created!\n"
				 << "Press RETURN to continue";
	std::cin.ignore();
}

void savingsAccount::viewAccount() {
	std::cout << "Account Name: " << getName() << endl;
	std::cout << "Account Number: " << getID() << endl;
	std::cout << "Account Balance: " << getBalance() << endl;
	std::cout << "Interest Rate: " << getInterestRate() << endl;

}

void savingsAccount::editAccountMenu() {
	int option = 0;
	do {
		clearScreen();
		std::cout << "Here are the current account (savingsAccount) details:\n";
		viewAccount();

		std::cout << "\nWhat would you like to do?\n"
			   	 << "[1] Deposit Money\n"
					 << "[2] Withdraw Money\n"
					 << "[3] Change Name\n"
					 << "[4] Change Interest Rate\n"
					 << "[5] Create Monthly Statement\n"
					 << "[6] Exit\n\n";

		option = getMenuOptionAuto(6);
				
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
		else if (option == 4) {
			std::cout << "Enter the new interest rate for the account: ";
			tempAmount = inputDouble();
			setInterestRate(tempAmount);
		}
		else if (option == 5) {
			createMonthlyStatement();
		}
		

	} while (option != savingsAccount::QUIT);
		
}


void savingsAccount::oldEditAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	viewAccount();

	prompt = confirm("\nWould you like to edit Account Name? (Y/N): ");
	if (prompt)
	{
		name = inputString("Enter the new Account Name: ");
	}

	// prompt = confirm("\nWould you like to edit Account Number? (Y/N): ");
	// if (prompt)
	// {
			// accountNumber = inputDouble("Enter the new Account Number: ");
	// }

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
	viewAccount();

	return;
}



