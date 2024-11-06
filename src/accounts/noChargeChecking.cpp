#include "noChargeChecking.hpp"
#include "helpers.hpp"
#include <iomanip>
#include <iostream>

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double noChargeChecking::MINIMUM_BALANCE = 1000.00;
const double noChargeChecking::INTEREST_RATE = 0.02;

noChargeChecking::noChargeChecking(string name, int accountNumber, double balance)
	: noChargeChecking(name, accountNumber, balance, MINIMUM_BALANCE, INTEREST_RATE) { }

noChargeChecking::noChargeChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate)
	: checkingAccount(name, accountNumber, balance) {
	this->minimumBalance = minimumBalance;
	this->interestRate = interestRate;
}

noChargeChecking::noChargeChecking(const json &j) 
    : noChargeChecking(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("minimumBalance"), j.at("interestRate")) { }

noChargeChecking::~noChargeChecking() { }

double noChargeChecking::getMinimumBalance() const {
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

void noChargeChecking::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::setw(25) << std::left << "No Charge Checking:";
	std::cout << std::setw(20) << std::left << name;
	std::cout << " ACCT# ";
	std::cout << std::setw(10) << std::left << accountNumber;
	std::cout << " Balance: $";
	std::cout << std::setw(8) << std::left << balance << std::endl;
}

json noChargeChecking::toJson() const {
    return json{
        {"name", name},
        {"accountNumber", accountNumber},
        {"balance", balance},
        {"interestRate", interestRate},
        {"minimumBalance", minimumBalance},
        {"type", "noChargeChecking"}
    };
}

void noChargeChecking::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = bankAccount::generateAccountNumber(); // Generate random account number

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
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Minimum Balance: " << minimumBalance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;

	return;
}