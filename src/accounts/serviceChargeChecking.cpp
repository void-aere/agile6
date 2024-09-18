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
