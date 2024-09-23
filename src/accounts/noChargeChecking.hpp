#pragma once

#include "checkingAccount.hpp"

class noChargeChecking : public checkingAccount {
	public:
		noChargeChecking(string name, int accountNumber, double balance);
		noChargeChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate);
        noChargeChecking(const nlohmann::json &j);
		double getMinimumBalance() const;
		void setMinimumBalance(double minumumBalance);
		bool verifyMinimumBalance(double balance);
		void writeCheck(double amount);
		void withdraw(double amount);
		virtual void createMonthlyStatement();
		virtual void print() const;

        virtual nlohmann::json toJson() const;
		virtual void createAccountMenu();
		virtual void editAccountMenu();

	protected:
		double minimumBalance;
		double interestRate;

	private:
		static const double MINIMUM_BALANCE;
		static const double INTEREST_RATE;
};
