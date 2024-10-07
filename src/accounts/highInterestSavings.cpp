#include "highInterestSavings.hpp"
#include "helpers.hpp"
#include <iostream>
#include <iomanip>

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

void highInterestSavings::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	// minimumBalance = inputDouble("Minimum Balance: ");

	std::cout << "Account has been created!\n";
}

void highInterestSavings::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;
	std::cout << "Minimum Balance: " << minimumBalance << endl;

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

	prompt = confirm("\nWould you like to edit Minimum Balance? (Y/N): ");
	if (prompt)
	{
			minimumBalance = inputDouble("Enter the new Minimum Balance: ");
	}

	std::cout << "\nHere are the new account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;
	std::cout << "Minimum Balance: " << minimumBalance << endl;

	return;
}