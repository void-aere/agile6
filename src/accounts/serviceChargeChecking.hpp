#pragma once
#define serviceChargeChecking_hpp

#include "checkingAccount.hpp"

class serviceChargeChecking: public checkingAccount {
	public:
		serviceChargeChecking(string name, int accountNumber, double balance);
		serviceChargeChecking(string name, int accountNumber, double balance, double serviceChargeAmount, double serviceChargeChecksExceeded);
		double getServiceChargeAccount();
		void setServiceChargeAccount(double amount);
		double getServiceChargeChecksExceeded();
		void setServiceChargeChecksExceeded(double amount);
		int getChecksWritten();
		void setChecksWritten(int num);
		void postServiceCharge();
		void writeCheck(double amount);
		virtual void createMonthlyStatement();
		virtual void print();

	protected:
		double serviceChargeAccount;
		double serviceChargeChecksExceeded;
		int checksWritten;

	private:
		static const double SERVICE_CHARGE_ACCOUNT; // = 10.00
		static const int MAXIMUM_CHECK_QUANTITY; // = 5
		static const double SERVICE_CHARGE_CHECKS_EXCEEDED; // = 5
};
