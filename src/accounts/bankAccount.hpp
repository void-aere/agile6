#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "context.hpp"

class Context;

class bankAccount {
	public:
		bankAccount(std::string name, int accountNumber, double balance);
        virtual ~bankAccount();
		int getAccountNumber() const;
        int getID() const;
		double getBalance() const;
		std::string getName() const;
		void setName(std::string name);
		virtual void withdraw(double amount);
		void deposit(double amount);
		virtual void createMonthlyStatement() = 0;
		virtual void print() const;
		int generateAccountNumber();

        virtual nlohmann::json toJson() const = 0;
        static bankAccount* fromJson(const nlohmann::json& data);
        std::string getFilename() const;

		virtual void createAccountMenu(Context& cx);
		virtual void viewAccount();
		virtual void editAccountMenu(Context& cx);
		virtual void oldEditAccountMenu();

		const short QUIT = 4;

	protected:
		int accountNumber;
		std::string name;
		double balance;

};


