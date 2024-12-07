#include "highInterestSavings.hpp"
#include "helpers.hpp"
#include <iostream>
#include <iomanip>
#include "logger.hpp"

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double highInterestSavings::MINIMUM_BALANCE = 2500.00;
const double highInterestSavings::INTEREST_RATE = 0.05;

highInterestSavings::highInterestSavings(string name, int accountNumber, double balance)
	: highInterestSavings(name, accountNumber, balance, INTEREST_RATE, MINIMUM_BALANCE) { }

highInterestSavings::highInterestSavings(string name, int accountNumber, double balance, double interestRate, double minimumBalance)
	: savingsAccount(name, accountNumber, balance, interestRate) {
	this->minimumBalance = minimumBalance;
}

highInterestSavings::highInterestSavings(const json &j)
    : highInterestSavings(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("interestRate"), j.at("minimumBalance")) { }

highInterestSavings::~highInterestSavings() { }
	
double highInterestSavings::getMinimumBalance() const {
	return minimumBalance;
}

bool highInterestSavings::verifyMinimumBalance(double amount) {
	return (balance - amount >= minimumBalance);
}

void highInterestSavings::withdraw(double amount) {
	if (verifyMinimumBalance(amount)) balance -= amount;
}

void highInterestSavings::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::setw(25) << std::left << "High Interest Savings:";
	std::cout << std::setw(20) << std::left << name;
	std::cout << " ACCT# ";
	std::cout << std::setw(10) << std::left << accountNumber;
	std::cout << " Balance: $";
	std::cout << std::setw(8) << std::left << balance << std::endl;
}

json highInterestSavings::toJson() const {
    return json{
        {"name", name},
        {"accountNumber", accountNumber},
        {"balance", balance},
        {"interestRate", interestRate},
        {"minimumBalance", minimumBalance},
        {"type", "highInterestSavings"}
    };
}

void highInterestSavings::createAccountMenu(Context& cx) {

	std::cout << "Please enter the details for the High Interest Savings account you would like to create:\n";


	name = inputString("Account Name: ");

	accountNumber = bankAccount::generateAccountNumber(); // Generate random account number

	balance = inputDouble("Account Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	// minimumBalance = inputDouble("Minimum Balance: ");

	std::cout << "\nAccount has been created!\n"
				 << "Press RETURN to continue";

	std::string logMessage = "Account (" + name + ") was created.";
	logAction(cx.user()->getName(), logMessage, 1);

	std::cin.ignore();
}

void highInterestSavings::viewAccount() {
	std::cout << "Account Name: " << getName() << endl;
	std::cout << "Account Number: " << getID() << endl;
	std::cout << "Account Balance: " << getBalance() << endl;
	std::cout << "Interest Rate: " << getInterestRate() << endl;
	std::cout << "Minimum Balance: " << getMinimumBalance() << endl;
}

void highInterestSavings::editAccountMenu(Context& cx) {
	int option = 0;
	
	std::string logMessage = "Began editing account (" + name + ")...";
	logAction(cx.user()->getName(), logMessage, 1);

	do {
		clearScreen();
		mainmenu::printHeader(cx);
		std::cout << "Here are the current account (highInterestSavings) details:\n";
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
			string newName = inputString();
			setInterestRate(tempAmount);
		}
		else if (option == 5) {
			createMonthlyStatement();
		}

	} while (option != highInterestSavings::QUIT);

	
	logMessage = "Finished editing account (" + name + ")!";
	logAction(cx.user()->getName(), logMessage, 1);
		
}


void highInterestSavings::oldEditAccountMenu() {
	bool prompt = false;
	viewAccount();

	prompt = confirm("\nWould you like to edit Account Name? (Y/N): ");
	if (prompt)
	{
		name = inputString("Enter the new Account Name: ");
	}

	//prompt = confirm("\nWould you like to edit Account Number? (Y/N): ");
	//if (prompt)
	//{
	//		accountNumber = inputDouble("Enter the new Account Number: ");
	//}

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

	prompt = confirm("\nWould you like to edit Minimum Balance? (Y/N): ");
	if (prompt)
	{
			minimumBalance = inputDouble("Enter the new Minimum Balance: ");
	}

	std::cout << "\nHere are the new account details:\n";
	viewAccount();

	return;
}
