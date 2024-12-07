#pragma once

#include "noChargeChecking.hpp"
#include "mainmenu.hpp"

class highInterestChecking : public noChargeChecking {
	public:
		highInterestChecking(std::string name, int accountNumber, double balance);
		highInterestChecking(std::string name, int accountNumber, double balance, double minimumBalance, double interestRate);
        highInterestChecking(const nlohmann::json &j);
        ~highInterestChecking();
		double getInterestRate() const;
		void setInterestRate(double interestRate);
		void postInterest();
		void createMonthlyStatement();
		virtual void print() const;

        nlohmann::json toJson() const;

		virtual void createAccountMenu(Context& cx);
		virtual void viewAccount();
		virtual void editAccountMenu(Context& cx);
		virtual void oldEditAccountMenu();
		
		const short QUIT = 8;

	private:
		static const double INTEREST_RATE;
		static const double MINIMUM_BALANCE;
};
