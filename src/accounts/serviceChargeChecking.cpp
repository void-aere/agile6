#include "serviceChargeChecking.hpp"
#include <iomanip>
#include <iostream>

const double serviceChargeChecking::SERVICE_CHARGE_ACCOUNT = 10.00;
const int serviceChargeChecking::MAXIMUM_CHECK_QUANTITY = 5;
const double serviceChargeChecking::SERVICE_CHARGE_CHECKS_EXCEEDED = 5;

serviceChargeChecking::serviceChargeChecking(string name, int accountNumber, double balance)
	: checkingAccount(name, accountNumber, balance) {
	serviceChargeAccount = SERVICE_CHARGE_ACCOUNT;
	serviceChargeChecksExceeded = 0;
	checksWritten = 0;
}

serviceChargeChecking::serviceChargeChecking(string name, int accountNumber, double balance, double serviceChargeAccount, double serviceChargeChecksExceeded)
	: checkingAccount(name, accountNumber, balance) {
	serviceChargeAccount = serviceChargeAccount;
	this->serviceChargeChecksExceeded = serviceChargeChecksExceeded;
	this->checksWritten = 0;
}

double serviceChargeChecking::getServiceChargeAccount() {
	return serviceChargeAccount;
}

void serviceChargeChecking::setServiceChargeAccount(double amount) {
	serviceChargeAccount = amount;
}

double serviceChargeChecking::getServiceChargeChecksExceeded() {
	return serviceChargeChecksExceeded;
}

void serviceChargeChecking::setServiceChargeChecksExceeded(double amount) {
	serviceChargeChecksExceeded = amount;
}

int serviceChargeChecking::getChecksWritten() {
	return checksWritten;
}

void serviceChargeChecking::setChecksWritten(int num) {
	checksWritten = num;
}

void serviceChargeChecking::postServiceCharge() {
	balance -= serviceChargeAccount;
}

void serviceChargeChecking::writeCheck(double amount) {
	if (checksWritten >=  MAXIMUM_CHECK_QUANTITY)
		balance -= serviceChargeChecksExceeded;

	balance -= amount;
	checksWritten++;
}

void serviceChargeChecking::createMonthlyStatement() {
	postServiceCharge();
}

void serviceChargeChecking::print() {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "Service CHarge Checking: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}

void serviceChargeChecking::createAccountMenu() {

	name = inputString("Account Name: ");

	accountNumber = inputDouble("Account Number: ");

	balance = inputDouble("Account Balance: ");

	// serviceChargeAccount = inputDouble("Service Charge Account: ");

	serviceChargeChecksExceeded = inputDouble("Service Charge Checks Exceeded: ");

	checksWritten = inputInt("Checks Written: ");

	std::cout << "Account has been created!\n";
}

void serviceChargeChecking::editAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Service Charge Account: " << serviceChargeAccount << endl;
	std::cout << "Service Charge Checks Exceeded: " << serviceChargeChecksExceeded << endl;
	std::cout << "Checks Written: " << checksWritten << endl;
	
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

	prompt = confirm("\nWould you like to edit Service Charge Account? (Y/N): ");
	if (prompt)
	{
			serviceChargeAccount = inputDouble("Enter the new Service Charge Account: ");
	}

	prompt = confirm("\nWould you like to edit Service Charge Checks Exceeded? (Y/N): ");
	if (prompt)
	{
			serviceChargeChecksExceeded = inputDouble("Enter the new Service Charge Checks Exceeded: ");
	}

		prompt = confirm("\nWould you like to edit Checks Written? (Y/N): ");
	if (prompt)
	{
			checksWritten = inputInt("Enter the new Checks Written: ");
	}

	std::cout << "\nHere are the new account details:\n";
	std::cout << "Account Name: " << name << endl;
	std::cout << "Account Number: " << accountNumber << endl;
	std::cout << "Account Balance: " << balance << endl;
	std::cout << "Service Charge Account: " << serviceChargeAccount << endl;
	std::cout << "Service Charge Checks Exceeded: " << serviceChargeChecksExceeded << endl;
	std::cout << "Checks Written: " << checksWritten << endl;

	return;
}