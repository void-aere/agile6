#include "certificateOfDeposit.hpp"
#include "helpers.hpp"
#include <iostream>
#include <iomanip>

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double certificateOfDeposit::INTEREST_RATE = 0.05;
const double certificateOfDeposit::MATURITY_MONTH = 6;

certificateOfDeposit::certificateOfDeposit(string name, int accountNumber, double balance)
	: certificateOfDeposit(name, accountNumber, balance, INTEREST_RATE, MATURITY_MONTH, 0) {
}

certificateOfDeposit::certificateOfDeposit(string name, int accountNumber, double balance, double interestRate, int maturityMonth)
	: certificateOfDeposit(name, accountNumber, balance, interestRate, maturityMonth, 0) {
}

certificateOfDeposit::certificateOfDeposit(std::string name, int accountNumber, double balance, double interestRate, int maturityMonth, int currentMonth) 
    : bankAccount(name, accountNumber, balance) {
        this->interestRate = interestRate;
        this->maturityMonth = maturityMonth;
        this->currentMonth = currentMonth;
}

certificateOfDeposit::certificateOfDeposit(const json &j) 
    : certificateOfDeposit(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("interestRate"), j.at("maturityMonth"), j.at("currentMonth")) {
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

json certificateOfDeposit::toJson() {
    return json{{"name", name}, {"accountNumber", accountNumber}, {"balance", balance}, {"interestRate", interestRate}, {"maturityMonth", maturityMonth}, {"currentMonth", currentMonth}};
}

void certificateOfDeposit::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	// interestRate = inputDouble("Interest Rate: ");

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
			balance = inputDouble("Enter the new Account Balance: ");
	}

	prompt = confirm("\nWould you like to edit Interest Rate? (Y/N): ");
	if (prompt)
	{
			interestRate = inputDouble("Enter the new Interest Rate: ");
	}

	prompt = confirm("\nWould you like to edit Maturity Month? (Y/N): ");
	if (prompt)
	{
			maturityMonth = inputInt("Enter the new Maturity Month: ");
	}

	prompt = confirm("\nWould you like to edit Current Month? (Y/N): ");
	if (prompt)
	{
			currentMonth = inputInt("Enter the new Current Month: ");
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