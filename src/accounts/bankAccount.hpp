#pragma once

#include <string>
using std::string;

class bankAccount {
	public:
		bankAccount(string name, int accountNumber, double balance);
		int getAccountNumber();
		double getBalance();
		string getName();
		void setName(string name);
		virtual void withdraw(double amount);
		void deposit(double amount);
		virtual void createMonthlyStatement() = 0;
		virtual void print();

	protected:
		int accountNumber;
		string name;
		double balance;
};


