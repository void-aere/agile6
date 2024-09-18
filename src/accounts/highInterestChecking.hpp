#pragma once
#define highInterestChecking_hpp

#include "noChargeChecking.hpp"

class highInterestChecking : public noChargeChecking {
	public:
		highInterestChecking(string name, int accountNumber, double balance);
		highInterestChecking(string name, int accountNumber, double balance, double minimumBalance, double interestRate);
		double getInterestRate();
		void setInterestRate(double interestRate);
		void postInterest();
		void createMonthlyStatement();
		virtual void print();
		virtual void createAccountMenu();
		virtual void editAccountMenu();

	private:
		static const double INTEREST_RATE;
		static const double MINIMUM_BALANCE;
};
