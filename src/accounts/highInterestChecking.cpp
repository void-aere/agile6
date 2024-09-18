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

double highInterestChecking::getInterestRate() {
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

void highInterestChecking::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "High Interest Checking: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}

json highInterestChecking::toJson() {
    return json{{"name", name}, {"accountNumber", accountNumber}, {"balance", balance}, {"interestRate", interestRate}, {"minimumBalance", minimumBalance}}; 
}

void highInterestChecking::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	// if they are already declared in the constructor they aren't needed i guess???
	// minimumBalance = inputDouble("Minimum Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

	std::cout << "Account has been created!\n";
}

void highInterestChecking::editAccountMenu() {
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