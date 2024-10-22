#pragma once

#include <string>
#include "bankAccount.hpp"

class savingsAccount : public bankAccount {
	public:
		savingsAccount(std::string name, int accountNumber, double balance, double interestRate);
		savingsAccount(std::string name, int accountNumber, double balance);
        savingsAccount(const nlohmann::json &j);
        ~savingsAccount();
		double getInterestRate() const;
		void setInterestRate(double interestRate);
		void postInterest();
		virtual void createMonthlyStatement();
		virtual void print() const;

        virtual nlohmann::json toJson() const;

		virtual void createAccountMenu();
		virtual void viewAccount();
		virtual void editAccountMenu();
		virtual void oldEditAccountMenu();

		const short QUIT = 4;

	protected:
		double interestRate;
	
	private:
		static const double INTEREST_RATE; // = 0.03;
};
