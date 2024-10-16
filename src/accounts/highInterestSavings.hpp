#pragma once

#include "savingsAccount.hpp"

class highInterestSavings : public savingsAccount {
	public:
		highInterestSavings(std::string name, int accountNumber, double balance);
		highInterestSavings(std::string name, int accountNumber, double balance, double interestRate, double minBalance);
        highInterestSavings(const nlohmann::json &j);
        ~highInterestSavings();
		double getMinimumBalance() const;
		bool verifyMinimumBalance(double amount);
		void withdraw(double amount);
		void print() const;

        nlohmann::json toJson() const;
		void createAccountMenu();
		void editAccountMenu();
	
	protected:
		double minimumBalance;

	private:
		static const double MINIMUM_BALANCE; // = 2500.00
		static const double INTEREST_RATE; // = 0.05
};
