#pragma once
#define noChargeChecking_h

#include "checkingAccount.hpp"

class noChargeChecking : public checkingAccount {
	public:
		noChargeChecking(string name, int accountNumber, double balance);
		noChargeChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate);

		double getMinimumBalance();
		void setMinimumBalance(double minumumBalance);
		bool verifyMinimumBalance(double balance);
		void writeCheck(double amount);
		void withdraw(double amount);
		virtual void createMonthlyStatement();
		virtual void print();
		virtual void createAccountMenu();
		virtual void editAccountMenu();

	protected:
		double minimumBalance;
		double interestRate;

	private:
		static const double MINIMUM_BALANCE;
		static const double INTEREST_RATE;
};
