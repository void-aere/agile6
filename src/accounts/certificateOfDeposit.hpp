#pragma once
#define certificateOfDeposit_hpp

#include "bankAccount.hpp"

class certificateOfDeposit : public bankAccount {
	public:
		certificateOfDeposit(string name, int accountNumber, double balance);
		certificateOfDeposit(string name, int accountNumber, double balance, double interestRate, int maturityMonth);
		double getInterestRate();
		void setInterestRate(double interestRate);
		double getCurrentMonth();
		void setCurrentMonth(int currentMonth);
		double getMaturityMonth();
		void setMaturityMonth(int maturityMonth);
		void postInterest();
		void withdraw(double amount);
		void withdraw();
		void createMonthlyStatement();
		
		void print();

	private:
		static const double INTEREST_RATE; // = 0.05
		static const double MATURITY_MONTH; // = 6

		double interestRate;
		int maturityMonth;
		int currentMonth;
};
