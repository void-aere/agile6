#pragma once
#define savingsAccount_hpp

#include <string>
#include "bankAccount.hpp"

class savingsAccount : public bankAccount {
	public:
		savingsAccount(string name, int accountNumber, double balance);
		savingsAccount(string name, int accountNumber, double balance, double interestRate);
		double getInterestRate();
		void setInterestRate(double interestRate);
		void postInterest();
		virtual void createMonthlyStatement();
		virtual void print();

	protected:
		double interestRate;
	
	private:
		static const double INTEREST_RATE; // = 0.03;
};
