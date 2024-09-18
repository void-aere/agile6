#pragma once

#include "bankAccount.hpp"

class certificateOfDeposit : public bankAccount {
	public:
		certificateOfDeposit(std::string name, int accountNumber, double balance);
		certificateOfDeposit(std::string name, int accountNumber, double balance, double interestRate, int maturityMonth);
        certificateOfDeposit(std::string name, int accountNumber, double balance, double interestRate, int maturityMonth, int currentMonth);
        certificateOfDeposit(const nlohmann::json &j);
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

        nlohmann::json toJson();
		void createAccountMenu();
		void editAccountMenu();


	private:
		static const double INTEREST_RATE; // = 0.05
		static const double MATURITY_MONTH; // = 6

		double interestRate;
		int maturityMonth;
		int currentMonth;
};
