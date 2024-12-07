#include "certificateOfDeposit.hpp"
#include "helpers.hpp"
#include "logger.hpp"
#include <iostream>
#include <iomanip>

using std::string, std::cout, std::endl;
using json = nlohmann::json;

const double certificateOfDeposit::INTEREST_RATE = 0.05;
const double certificateOfDeposit::MATURITY_MONTH = 6;


// First constructor (for creating a new Certificate of Deposit)
certificateOfDeposit::certificateOfDeposit(string name, int accountNumber, double balance)
	: certificateOfDeposit(name, accountNumber, balance, INTEREST_RATE, MATURITY_MONTH, 0) {
}

// Second constructor (for creating a new Certificate of Deposit with interest rate and maturity month)
certificateOfDeposit::certificateOfDeposit(string name, int accountNumber, double balance, double interestRate, int maturityMonth)
	: certificateOfDeposit(name, accountNumber, balance, interestRate, maturityMonth, 0) {
}

// Third constructor (for creating a new Certificate of Deposit with all parameters)
certificateOfDeposit::certificateOfDeposit(std::string name, int accountNumber, double balance, double interestRate, int maturityMonth, int currentMonth) 
    : bankAccount(name, accountNumber, balance) {
        this->interestRate = interestRate;
        this->maturityMonth = maturityMonth;
        this->currentMonth = currentMonth;
}

// Load from JSON constructor
certificateOfDeposit::certificateOfDeposit(const json &j) 
    : certificateOfDeposit(j.at("name"), j.at("accountNumber"), j.at("balance"), j.at("interestRate"), j.at("maturityMonth"), j.at("currentMonth")) {
}


certificateOfDeposit::~certificateOfDeposit() { }

double certificateOfDeposit::getInterestRate() const {
	return interestRate;
}

void certificateOfDeposit::setInterestRate(double interestRate) {
	this->interestRate = interestRate;
}

double certificateOfDeposit::getCurrentMonth() const {
	return currentMonth;
}

void certificateOfDeposit::setCurrentMonth(int currentMonth) {
	this->currentMonth = currentMonth;
}

double certificateOfDeposit::getMaturityMonth() const {
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

void certificateOfDeposit::print() const {
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::setw(25) << std::left << "Certificate of Deposit:";
	std::cout << std::setw(20) << std::left << name;
	std::cout << " ACCT# ";
	std::cout << std::setw(10) << std::left << accountNumber;
	std::cout << " Balance: $";
	std::cout << std::setw(8) << std::left << balance << std::endl;
}

json certificateOfDeposit::toJson() const {
    return json{
        {"name", name},
        {"accountNumber", accountNumber},
        {"balance", balance},
        {"interestRate", interestRate},
        {"maturityMonth", maturityMonth},
        {"currentMonth", currentMonth},
        {"type", "certificateOfDeposit"}
    };
}

void certificateOfDeposit::createAccountMenu(Context &cx) {

	std::cout << "Please enter the details for the Certificate of Deposit account you would like to create:\n";


	name = inputString("Account Name: ");

	balance = inputDouble("Account Balance: ");

	accountNumber = bankAccount::generateAccountNumber(); // Generate random account number

	// interestRate = inputDouble("Interest Rate: ");

	maturityMonth = inputInt("Maturity Month: ");

	currentMonth = inputInt("Current Month: ");

	std::cout << "\nAccount has been created!\n"
				 << "Press RETURN to continue";

	std::string logMessage = "Account (" + name + ") was created.";
	logAction(cx.user()->getName(), logMessage, 1);

	std::cin.ignore();

}

void certificateOfDeposit::viewAccount() {
	std::cout << "Account Name: " << getName() << endl;
	std::cout << "Account Number: " << getID() << endl;
	std::cout << "Account Balance: " << getBalance() << endl;
	std::cout << "Interest Rate: " << getInterestRate() << endl;
	std::cout << "Maturity Month: " << getMaturityMonth() << endl;
	std::cout << "Current Month: " << getCurrentMonth() << endl;
}

void certificateOfDeposit::editAccountMenu(Context& cx) {
	int option = 0;

	std::string logMessage = "Began editing account (" + name + ")...";
	logAction(cx.user()->getName(), logMessage, 1);

	do {
		clearScreen();
		mainmenu::printHeader(cx);
		std::cout << "Here are the current account (certificateOfDeposit) details:\n";
		viewAccount();
	
		std::cout << "\nWhat would you like to do?\n"
					 << "[1] Deposit\n"
					 << "[2] Withdraw\n"
					 << "[3] Change Name\n"
					 << "[4] Change Interest Rate\n"
					 << "[5] Change Maturity Month\n"
					 << "[6] Create Monthly Statement\n"
					 << "[7] Exit\n\n";
			
		option = getMenuOptionAuto(7);
		
		double  tempAmount = 0.0;
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
			std::cout << "Enter the new interest rate for the account: ";
			tempAmount = inputDouble();
			setInterestRate(tempAmount);
		}
		else if (option == 5) {
			std::cout << "Enter the new maturity month for the account: ";
			tempInt = inputInt();
			setMaturityMonth(tempInt);
		}
		else if (option == 6) {
			createMonthlyStatement();
		}

	} while (option != certificateOfDeposit::QUIT);

	logMessage = "Finished editing account (" + name + ")!";
	logAction(cx.user()->getName(), logMessage, 1);
}


void certificateOfDeposit::oldEditAccountMenu() {
	bool prompt = false;
	std::cout << "Here are the current account details:\n";
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
	viewAccount();

	return;
}
