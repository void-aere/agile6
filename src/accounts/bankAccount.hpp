#pragma once

#include <string>
#include <nlohmann/json.hpp>

class bankAccount {
	public:
		bankAccount(std::string name, int accountNumber, double balance);
		int getAccountNumber();
		double getBalance();
		std::string getName();
		void setName(std::string name);
		virtual void withdraw(double amount);
		void deposit(double amount);
		virtual void createMonthlyStatement() = 0;
		virtual void print();

        virtual nlohmann::json toJson();
		virtual void createAccountMenu();
		virtual void editAccountMenu();

	protected:
		int accountNumber;
		std::string name;
		double balance;
};


