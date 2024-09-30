#pragma once

#include "bankAccount.hpp"

class certificateOfDeposit : public bankAccount {
	public:
		certificateOfDeposit(std::string name, int accountNumber, double balance);
		certificateOfDeposit(std::string name, int accountNumber, double balance, double interestRate, int maturityMonth);
        certificateOfDeposit(std::string name, int accountNumber, double balance, double interestRate, int maturityMonth, int currentMonth);
        certificateOfDeposit(const nlohmann::json &j);
        ~certificateOfDeposit();
		double getInterestRate() const;
		void setInterestRate(double interestRate);
		double getCurrentMonth() const;
		void setCurrentMonth(int currentMonth);
		double getMaturityMonth() const;
		void setMaturityMonth(int maturityMonth);
		void postInterest();
		void withdraw(double amount);
		void withdraw();
		void createMonthlyStatement();
		void print() const;

        nlohmann::json toJson() const;
		void createAccountMenu();
		void editAccountMenu();


	private:
		static const double INTEREST_RATE; // = 0.05
		static const double MATURITY_MONTH; // = 6

		double interestRate;
		int maturityMonth;
		int currentMonth;
};
