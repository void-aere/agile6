#include "serviceChargeChecking.hpp"
#include "helpers.hpp"
#include <iomanip>
#include <iostream>
#include "logger.hpp"

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

serviceChargeChecking::~serviceChargeChecking() { }

double serviceChargeChecking::getServiceChargeAmount() const {
	return serviceChargeAmount;
}

void serviceChargeChecking::setServiceChargeAmount(double amount) {
	serviceChargeAmount = amount;
}

double serviceChargeChecking::getServiceChargeChecksExceeded() const {
	return serviceChargeChecksExceeded;
}

void serviceChargeChecking::setServiceChargeChecksExceeded(double amount) {
	serviceChargeChecksExceeded = amount;
}

int serviceChargeChecking::getChecksWritten() const {
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

void serviceChargeChecking::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::setw(25) << std::left << "Service Charge Checking:";
	std::cout << std::setw(20) << std::left << name;
	std::cout << " ACCT# ";
	std::cout << std::setw(10) << std::left << accountNumber;
	std::cout << " Balance: $";
	std::cout << std::setw(8) << std::left << balance << std::endl;
}

json serviceChargeChecking::toJson() const {
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

void serviceChargeChecking::createAccountMenu(Context& cx) {

	std::cout << "Please enter the details for the Service Charge Checking account you would like to create:\n";

	name = inputString("Account Name: ");

	accountNumber = bankAccount::generateAccountNumber(); // Generate random account number

	balance = inputDouble("Account Balance: ");

	// serviceChargeAccount = inputDouble("Service Charge Account: ");

	serviceChargeChecksExceeded = inputDouble("Service Charge Checks Exceeded: ");

	checksWritten = inputInt("Checks Written: ");

	std::cout << "\nAccount has been created!\n"
				 << "Press RETURN to continue";

	std::string logMessage = "Account (" + name + ") was created.";
	logAction(cx.user()->getName(), logMessage, 1);

	std::cin.ignore();
}

void serviceChargeChecking::viewAccount() {
	std::cout << "Account Name: " << getName() << endl;
	std::cout << "Account Number: " << getID() << endl;
	std::cout << "Account Balance: " << getBalance() << endl;
	std::cout << "Service Charge Amount: " << getServiceChargeAmount() << endl;
	std::cout << "Service Charge Checks Exceeded: " << getServiceChargeChecksExceeded() << endl;
	std::cout << "Checks Written: " << getChecksWritten() << endl;
}

void serviceChargeChecking::editAccountMenu(Context& cx) {
	int option = 0;
	
	std::string logMessage = "Began editing account (" + name + ")...";
	logAction(cx.user()->getName(), logMessage, 1);

	do {
		clearScreen();
		mainmenu::printHeader(cx);
		std::cout << "Here are the current account (serviceChargeChecking) details:\n";
		viewAccount();

		std::cout << "\nWhat would you like to do?\n"
			   	 << "[1] Deposit\n"
					 << "[2] Withdraw\n"
					 << "[3] Change Name\n"
					 << "[4] Change Charge Amount\n"
					 << "[5] Change Checks Exceeded Amount\n"
					 << "[6] Change Checks Written Amount\n"
				 	 << "[7] Write Check\n"
					 << "[8] Create Monthly Statement\n"
					 << "[9] Exit\n\n";

		option = getMenuOptionAuto(9);
				
		double tempAmount = 0.0;
		int tempInt = 0;

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
			std::cout << "Enter the new service charge amount for the account: ";
			tempAmount = inputDouble();
			setServiceChargeAmount(tempAmount);
		}
		else if (option == 5) {
			std::cout << "Enter the new service charge checks exceeded amount for the account: ";
			tempAmount = inputDouble();
			setServiceChargeChecksExceeded(tempAmount);
		}
		else if (option == 6) {
			std::cout << "Enter the new amount of checks written for the account: ";
			tempInt = inputInt();
			setChecksWritten(tempInt);
		}
		else if (option == 7) {
			std::cout << "Enter the amount of the check being written: ";
			tempAmount = inputDouble();
			writeCheck(tempAmount);
		}
		else if (option == 8) {
			createMonthlyStatement();
		}
		

	} while (option != serviceChargeChecking::QUIT);

	logMessage = "Finished editing account (" + name + ")!";
	logAction(cx.user()->getName(), logMessage, 1);
		
}

void serviceChargeChecking::oldEditAccountMenu() {
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
	//		accountNumber = inputDouble("Enter the new Account Number: ");
	// }

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
	viewAccount();

	return;
}
