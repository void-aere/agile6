#pragma once

#include <string>
#include "bankAccount.hpp"

class savingsAccount : public bankAccount {
	public:
		savingsAccount(std::string name, int accountNumber, double balance, double interestRate);
		savingsAccount(std::string name, int accountNumber, double balance);
        savingsAccount(const nlohmann::json &j);
		double getInterestRate();
		void setInterestRate(double interestRate);
		void postInterest();
		virtual void createMonthlyStatement();
		virtual void print();

        virtual nlohmann::json toJson();
		virtual void createAccountMenu();
		virtual void editAccountMenu();

	protected:
		double interestRate;
	
	private:
		static const double INTEREST_RATE; // = 0.03;
};