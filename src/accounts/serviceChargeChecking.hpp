#pragma once

#include "checkingAccount.hpp"

class serviceChargeChecking: public checkingAccount {
	public:
		serviceChargeChecking(std::string name, int accountNumber, double balance);
		serviceChargeChecking(std::string name, int accountNumber, double balance, double serviceChargeAmount, double serviceChargeChecksExceeded);
		serviceChargeChecking(std::string name, int accountNumber, double balance, double serviceChargeAmount, double serviceChargeChecksExceeded, int checksWritten);
        serviceChargeChecking(const nlohmann::json &j);
        ~serviceChargeChecking();
		double getServiceChargeAmount() const;
		void setServiceChargeAmount(double amount);
		double getServiceChargeChecksExceeded() const;
		void setServiceChargeChecksExceeded(double amount);
		int getChecksWritten() const;
		void setChecksWritten(int num);
		void postServiceCharge();
		void writeCheck(double amount);
		void createMonthlyStatement();
		void print() const;

        nlohmann::json toJson() const;

		virtual void createAccountMenu();
		virtual void viewAccount();
		virtual void editAccountMenu();
		virtual void oldEditAccountMenu();

		const short QUIT = 4;

	protected:
		double serviceChargeAmount;
		double serviceChargeChecksExceeded;
		int checksWritten;

	private:
		static const double SERVICE_CHARGE_AMOUNT; // = 10.00
		static const int MAXIMUM_CHECK_QUANTITY; // = 5
		static const double SERVICE_CHARGE_CHECKS_EXCEEDED; // = 5
};
