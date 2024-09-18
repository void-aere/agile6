#pragma once

#include "noChargeChecking.hpp"

class highInterestChecking : public noChargeChecking {
	public:
		highInterestChecking(std::string name, int accountNumber, double balance);
		highInterestChecking(std::string name, int accountNumber, double balance, double minimumBalance, double interestRate);
        highInterestChecking(const nlohmann::json &j);
		double getInterestRate();
		void setInterestRate(double interestRate);
		void postInterest();
		void createMonthlyStatement();
		virtual void print();

        nlohmann::json toJson();
		virtual void createAccountMenu();
		virtual void editAccountMenu();

	private:
		static const double INTEREST_RATE;
		static const double MINIMUM_BALANCE;
};