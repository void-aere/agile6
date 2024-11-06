#pragma once

#include "checkingAccount.hpp"
#include "mainmenu.hpp"

class noChargeChecking : public checkingAccount {
	public:
		noChargeChecking(std::string name, int accountNumber, double balance);
		noChargeChecking(std::string name, int accountNumber, double balance, double minimumBalance, double interestRate);
        noChargeChecking(const nlohmann::json &j);
        ~noChargeChecking();
		double getMinimumBalance() const;
		void setMinimumBalance(double minumumBalance);
		bool verifyMinimumBalance(double balance);
		void writeCheck(double amount);
		void withdraw(double amount);
		virtual void createMonthlyStatement();
		virtual void print() const;

        virtual nlohmann::json toJson() const;

		virtual void createAccountMenu();
		virtual void viewAccount();
		virtual void editAccountMenu(Context& cx);
		virtual void oldEditAccountMenu();

		const short QUIT = 7;

	protected:
		double minimumBalance;
		double interestRate;

	private:
		static const double MINIMUM_BALANCE;
		static const double INTEREST_RATE;
};
