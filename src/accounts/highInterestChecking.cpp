#include "highInterestChecking.hpp"
#include "helpers.hpp"
#include <iostream>
#include <iomanip>

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double highInterestChecking::INTEREST_RATE = 0.05;
const double highInterestChecking::MINIMUM_BALANCE = 5000.00;

highInterestChecking::highInterestChecking(string name, int accountNumber, double balance)
	: highInterestChecking(name, accountNumber, balance, MINIMUM_BALANCE, INTEREST_RATE) { }

highInterestChecking::highInterestChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate)
	: noChargeChecking(name, accountNumber, balance, minimumBalance, interestRate) {}

highInterestChecking::highInterestChecking(const json &j)
    : highInterestChecking(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("minimumBalance"), j.at("interestRate")) { }

highInterestChecking::~highInterestChecking() { }

double highInterestChecking::getInterestRate() const {
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

void highInterestChecking::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::setw(25) << std::left << "High Interest Checking:";
	std::cout << std::setw(20) << std::left << name;
	std::cout << " ACCT# ";
	std::cout << std::setw(10) << std::left << accountNumber;
	std::cout << " Balance: $";
	std::cout << std::setw(8) << std::left << balance << std::endl;
}

json highInterestChecking::toJson() const {
    return json{
        {"name", name},
        {"accountNumber", accountNumber},
        {"balance", balance},
        {"interestRate", interestRate},
        {"minimumBalance", minimumBalance},
        {"type", "highInterestChecking"}
    }; 
}

void highInterestChecking::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = bankAccount::generateAccountNumber(); // Generate random account number

	balance = inputDouble("Account Balance: ");

	// if they are already declared in the constructor they aren't needed i guess???
	// minimumBalance = inputDouble("Minimum Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	std::cout << "Account has been created!\n";
}

void highInterestChecking::viewAccount() {
	std::cout << "Account Name: " << getName() << endl;
	std::cout << "Account Number: " << getID() << endl;
	std::cout << "Account Balance: " << getBalance() << endl;
	std::cout << "Minimum Balance: " << getMinimumBalance() << endl;
	std::cout << "Interest Rate: " << getInterestRate() << endl;
}

void highInterestChecking::editAccountMenu() {
	int option = 0;
	do {
		clearScreen();
		std::cout << "Here are the current account (highInterestChecking) details:\n";
		viewAccount();

		std::cout << "\nWhat would you like to do?\n"
			   	 << "[1] Deposit Money\n"
					 << "[2] Withdraw Money\n"
					 << "[3] Change Name\n"
					 << "[4] Change Minimum Balance\n"
					 << "[5] Change Interest Rate\n"
				    << "[6] Write Check\n"
					 << "[7] Create Monthly Statement\n"
					 << "[8] Exit\n\n";

		option = getMenuOptionAuto(8);
				
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
			std::cout << "Enter the new minimum balance for the account: ";
			tempAmount = inputDouble();
			setMinimumBalance(tempAmount);
		}
		else if (option == 5) {
			std::cout << "Enter the new interest rate for the account: ";
			tempAmount = inputDouble();
			setInterestRate(tempAmount);
		}
		else if (option == 6) {
			std::cout << "Enter the amount of the check being written: ";
			tempAmount = inputDouble();
			writeCheck(tempAmount);
		}
		else if (option == 7) {
			createMonthlyStatement();
		}

	} while (option != highInterestChecking::QUIT);
		
}


void highInterestChecking::oldEditAccountMenu() {
	bool prompt = false;
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
	viewAccount();

	return;
}
