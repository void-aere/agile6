#pragma once
#define highInterestSavings_hpp

#include "savingsAccount.hpp"

class highInterestSavings : public savingsAccount {
	public:
		highInterestSavings(string name, int accountNumber, double balance);
		highInterestSavings(string name, int accountNumber, double balance, double interestRate, double minBalance);
		double getMinimumBalance();
		bool verifyMinimumBalance(double amount);
		virtual void withdraw(double amount);
		virtual void print();
	
	protected:
		double minimumBalance;

	private:
		static const double MINIMUM_BALANCE; // = 2500.00
		static const double INTEREST_RATE; // = 0.05
};
