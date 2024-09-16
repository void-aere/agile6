#include <iostream>
#include <fstream>
#include "Account.h"
using namespace std;

void addAccount(fstream& db);
void listAllAccounts(fstream& db);
void updateUsername(fstream& db, char uName[]);
void updateFile(fstream& db, char uName[], char fName[]);
bool findAccount(fstream& db, char uName[]);

int main()
{
	fstream database;

	char currentUserName[64] = "chamedani0";
	char currentFileName[64] = "BankAccount1.txt";
	char currentFileName2[64] = "BankAccount2.txt";

	addAccount(database);

	addAccount(database);

	addAccount(database);

	listAllAccounts(database);

	//updateUsername(database, currentUserName);

	updateFile(database, currentUserName, currentFileName);

	listAllAccounts(database);

	addAccount(database);

	listAllAccounts(database);

	updateFile(database, currentUserName, currentFileName2);

	listAllAccounts(database);

	if (findAccount(database, currentUserName))
	{
		cout << "Account found!" << endl;
	}
}

void addAccount(fstream &db) 
{
	db.open("database.dat", ios::out | ios::binary | ios::app);

	Account newAccount;
	
	cout << "Please enter a username: ";
	cin.getline(newAccount.userName, 64);

	db.seekp(0L, ios::end);

	db.write(reinterpret_cast<char*>(&newAccount), sizeof(newAccount));

	cout << "Account has been created!\n";

	db.close();
}

void listAllAccounts(fstream& db)
{
	db.open("database.dat", ios::in | ios::binary);

	db.seekg(0L, ios::beg);

	Account showAccount;

	cout << "Here are all currently registered users:\n\n";

	while (db.read(reinterpret_cast<char*>(&showAccount), sizeof(showAccount)))
	{
		cout << "Account Name: " << showAccount.userName << endl
			 << "Current File: " << showAccount.fileName << endl << endl;
	}

	db.close();
}

void updateUsername(fstream& db, char uName[])
{
	db.open("database.dat", ios::in | ios::binary);

	char newName[64] = "";

	cout << "Please enter the new username: ";
	cin.getline(newName, 64);

	db.seekg(0L, ios::beg);

	Account showAccount;

	bool found = false;
	int seekNum = 0;

	while (!found && db.read(reinterpret_cast<char*>(&showAccount), sizeof(showAccount)))
	{
		if (strncmp(showAccount.userName, uName, sizeof(showAccount.userName)) == 0)
		{
			strncpy_s(showAccount.userName, newName, sizeof(showAccount.userName));
			found = true;
		}
		else
		{
			seekNum++;
		}
	}

	db.close();

	db.open("database.dat", ios::in | ios::out | ios::binary);

	db.seekp((seekNum * sizeof(showAccount)), ios::beg);

	db.write(reinterpret_cast<char*>(&showAccount), sizeof(showAccount));

	cout << "Username has been updated!\n";

	db.close();
}

void updateFile(fstream& db, char uName[], char fName[])
{
	db.open("database.dat", ios::in | ios::binary);

	db.seekg(0L, ios::beg);

	Account showAccount;
	bool found = false;
	int seekNum = 0;

	while (!found && db.read(reinterpret_cast<char*>(&showAccount), sizeof(showAccount)))
	{
		if (strncmp(showAccount.userName, uName, sizeof(showAccount.userName)) == 0)
		{
			found = true;
		}
		else
		{
			seekNum++;
		}
	}

	db.close();

	db.open("database.dat", ios::in | ios::out | ios::binary);

	db.seekp(seekNum * sizeof(showAccount), ios::beg);

	strncpy_s(showAccount.fileName, fName, sizeof(showAccount.fileName));

	db.write(reinterpret_cast<char*>(&showAccount), sizeof(showAccount));

	db.close();
}
	
bool findAccount(fstream& db, char uName[])
{
	db.open("database.dat", ios::in | ios::binary);

	db.seekg(0L, ios::beg);

	Account showAccount;

	bool found = false;

	while (!found && db.read(reinterpret_cast<char*>(&showAccount), sizeof(showAccount)))
	{
		if (strncmp(showAccount.userName, uName, sizeof(showAccount.userName)) == 0)
		{
			db.close();

			return true;
		}
	}

	db.close();

	return false;
}