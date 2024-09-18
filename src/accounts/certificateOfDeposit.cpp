#include "certificateOfDeposit.hpp"
#include <iostream>
#include <iomanip>

const double certificateOfDeposit::INTEREST_RATE = 0.05;
const double certificateOfDeposit::MATURITY_MONTH = 6;

certificateOfDeposit::certificateOfDeposit(string name, int accountNumber, double balance)
	: bankAccount(name, accountNumber, balance) {
	interestRate = INTEREST_RATE;
	//maturityMonth = MATURITY_MONTH;
	maturityMonth = 0;
	currentMonth = 0;
}

certificateOfDeposit::certificateOfDeposit(string name, int accountNumber, double balance, double interestRate, int maturityMonth)
	: bankAccount(name, accountNumber, balance) {
	this->interestRate = interestRate;
	this->maturityMonth = maturityMonth;
	currentMonth = 0;
}

double certificateOfDeposit::getInterestRate() {
	return interestRate;
}

void certificateOfDeposit::setInterestRate(double interestRate) {
	this->interestRate = interestRate;
}

double certificateOfDeposit::getCurrentMonth() {
	return currentMonth;
}

void certificateOfDeposit::setCurrentMonth(int currentMonth) {
	this->currentMonth = currentMonth;
}

double certificateOfDeposit::getMaturityMonth() {
	return maturityMonth;
}

void certificateOfDeposit::setMaturityMonth(int maturityMonth) {
	this->maturityMonth = maturityMonth;
}

void certificateOfDeposit::postInterest() {
	balance = 2 * balance * interestRate;
}

void certificateOfDeposit::withdraw(double amount) {
	//no withdrawl until maturity
}

void certificateOfDeposit::withdraw() {
	if (currentMonth > maturityMonth) balance = 0;
	else std::cout << "CD has not matured. No withdrawl." << std::endl;
}

void certificateOfDeposit::createMonthlyStatement() {
	postInterest();
	currentMonth++;
}

void certificateOfDeposit::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "Certificate of Deposit: " << name << "\t ACCT# " << accountNumber << "\t Balance: $" << balance << std::endl;
}

void certificateOfDeposit::createAccountMenu() {
	double floatTemp;

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	interestRate = inputDouble("Interest Rate: ");

	maturityMonth = inputInt("Maturity Month: ");

	currentMonth = inputInt("Current Month:");

	std::cout << "Account has been created!\n";
}

void certificateOfDeposit::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;
	std::cout << "Maturity Month: " << maturityMonth << endl;
	std::cout << "Current Month: " << currentMonth << endl;


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
			accountNumber = inputDouble("Enter the new Account Balance: ");
	}

	prompt = confirm("\nWould you like to edit Interest Rate? (Y/N): ");
	if (prompt)
	{
			accountNumber = inputDouble("Enter the new Interest Rate: ");
	}

	prompt = confirm("\nWould you like to edit Maturity Month? (Y/N): ");
	if (prompt)
	{
			accountNumber = inputDouble("Enter the new Maturity Month: ");
	}

	prompt = confirm("\nWould you like to edit Current Month? (Y/N): ");
	if (prompt)
	{
			accountNumber = inputDouble("Enter the new Current Month: ");
	}

	std::cout << "\nHere are the new account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Interest Rate: " << interestRate << endl;
	std::cout << "Maturity Month: " << maturityMonth << endl;
	std::cout << "Current Month: " << currentMonth << endl;

	return;
}