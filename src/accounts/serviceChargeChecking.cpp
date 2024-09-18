#include "serviceChargeChecking.hpp"
#include "helpers.hpp"
#include <iomanip>
#include <iostream>

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double serviceChargeChecking::SERVICE_CHARGE_AMOUNT = 10.00;
const int serviceChargeChecking::MAXIMUM_CHECK_QUANTITY = 5;
const double serviceChargeChecking::SERVICE_CHARGE_CHECKS_EXCEEDED = 5;

serviceChargeChecking::serviceChargeChecking(string name, int accountNumber, double balance)
	: serviceChargeChecking(name, accountNumber, balance, SERVICE_CHARGE_AMOUNT, 0, 0) { }

serviceChargeChecking::serviceChargeChecking(string name, int accountNumber, double balance, double serviceChargeAccount, double serviceChargeChecksExceeded)
	: serviceChargeChecking(name, accountNumber, balance, serviceChargeAccount, serviceChargeChecksExceeded, 0) { }

serviceChargeChecking::serviceChargeChecking(std::string name, int accountNumber, double balance, double serviceChargeAmount, double serviceChargeChecksExceeded, int checksWritten)
    : checkingAccount(name, accountNumber, balance) {
    this->serviceChargeAmount = serviceChargeAmount;
    this->serviceChargeChecksExceeded = serviceChargeChecksExceeded;
    this->checksWritten = checksWritten;
}

serviceChargeChecking::serviceChargeChecking(const json &j)
    : serviceChargeChecking(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("serviceChargeAmount"), j.at("serviceChargeChecksExceeded"), j.at("checksWritten")) { }

double serviceChargeChecking::getServiceChargeAmount() {
	return serviceChargeAmount;
}

void serviceChargeChecking::setServiceChargeAmount(double amount) {
	serviceChargeAmount = amount;
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
	balance -= serviceChargeAmount;
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
	std::cout << "Service Charge Checking: " << name << "\t ACCT# " << accountNumber << "\tBalance: $" << balance << std::endl;
}

json serviceChargeChecking::toJson() {
    return json{
        {"name", name},
        {"accountNumber", accountNumber},
        {"balance", balance},
        {"serviceChargeAmount", serviceChargeAmount},
        {"serviceChargeChecksExceeded", serviceChargeChecksExceeded},
        {"checksWritten", checksWritten},
        {"type", "serviceChargeChecking"}
    };
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
	std::cout << "Service Charge Amount: " << serviceChargeAmount << endl;
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

	prompt = confirm("\nWould you like to edit Service Charge Amount? (Y/N): ");
	if (prompt)
	{
			serviceChargeAmount = inputDouble("Enter the new Service Charge Amount: ");
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
	std::cout << "Service Charge Amount: " << serviceChargeAmount << endl;
	std::cout << "Service Charge Checks Exceeded: " << serviceChargeChecksExceeded << endl;
	std::cout << "Checks Written: " << checksWritten << endl;

	return;
}