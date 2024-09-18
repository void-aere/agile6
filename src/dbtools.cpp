#include "dbtools.hpp"

#include <iostream>
#include <fstream>
#include <string.h>
#include "account.hpp"
using namespace std;

// int main()
// {
// 	// Universal fstream variable that will be defined
// 	// when first opening menu
// 	fstream database;

// 	// test data
// 	char currentUserName[64] = "chamedani0";
// 	char currentFileName[64] = "BankAccount1.txt";
// 	char currentFileName2[64] = "BankAccount2.txt";

// 	// for adding account just pass in the fstream variable
// 	addAccount(database);

// 	addAccount(database);

// 	addAccount(database);

// 	// for listing accounts just pass in fstream
// 	listAllAccounts(database);

// 	// commented out during testing but pass in fstream as
// 	// well as the current user name logged in so the
// 	// computer knows which username to update
// 	// 
// 	// this is an extra function that is really only needed
// 	// if we want to allow users to chnage their name on the
// 	// database, not a priority
// 	//updateUsername(database, currentUserName);

// 	// this will be used to update the current user, pass in
// 	// fstream, the current user's name, as well as the file
// 	// they are trying to access/if they are leaving
// 	//
// 	// this function will be called whenever a user attempts to
// 	// access the data of a bank account so when other database
// 	// users try to edit any account we can run fileInUse and
// 	// find that file name in the database to tell the user
// 	// if the file is in use
// 	//
// 	// when using updateFile to "leave" an account just pass
// 	// in a literal of "Not in a file." or whatever, it shouldn't
// 	// matter
// 	updateFile(database, currentUserName, currentFileName);

// 	listAllAccounts(database);

// 	addAccount(database);

// 	listAllAccounts(database);

// 	updateFile(database, currentUserName, currentFileName2);

// 	listAllAccounts(database);

// 	// use findAccount and fileInUse to return boolean variables
// 	// that can be used to either direct user to the edit menu
// 	// for an account or just shoot them back to the main menu
// 	if (findAccount(database, currentUserName))
// 	{
// 		cout << "Account found!" << endl;
// 	}

// 	if (fileInUse(database, currentFileName2))
// 	{
// 		cout << "BACK TO MENU..." << endl;
// 	}
// }

// creates an account with the entered username and stores it on the
// database, could create a check to see if said account is already
// on the database but maybe in the next build
void addAccount(fstream& db, char uName[])
{
	db.open("database.dat", ios::out | ios::binary | ios::app);

	Account newAccount;

	strncpy(newAccount.userName, uName, 64);

	db.seekp(0L, ios::end);

	db.write(reinterpret_cast<char*>(&newAccount), sizeof(newAccount));

	db.close();
}

// simply lists all accounts, if you want to clear database just
// delete "database.dat" from file directory
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

// updates the current user's name, complicated though as we also need to
// update the user's name in the main-menu, maybe don't add this in yet
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
			strncpy(showAccount.userName, newName, sizeof(showAccount.userName));
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

// updateFile will be called whenever ANY ACCOUNT IS BEING ACCESSED
// OR EXITED; when accessing an account pass in the file name, and
// when leaving the account pass in some random literal like "Not in a file."
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

	strncpy(showAccount.fileName, fName, sizeof(showAccount.fileName));

	db.write(reinterpret_cast<char*>(&showAccount), sizeof(showAccount));

	db.close();
}

// check used at login to see whether they are a new or returning user
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

// checked used BEFORE EVERY SINGLE TIME AN ACCOUNT IS ACCESSED to ensure nobody else
// is editing
bool fileInUse(fstream& db, char fName[])
{
	db.open("database.dat", ios::in | ios::binary);

	db.seekg(0L, ios::beg);

	Account showAccount;

	bool found = false;

	while (!found && db.read(reinterpret_cast<char*>(&showAccount), sizeof(showAccount)))
	{
		if (strncmp(showAccount.fileName, fName, sizeof(showAccount.userName)) == 0)
		{
			db.close();

			cout << "The file you are trying to access, \"" << showAccount.fileName
				<< "\" is currently being edited by " << showAccount.userName
				<< " and cannot be accessed right now.\n";

			return true;
		}
	}

	db.close();

	return false;
}

// OUTPUT

//Please enter a username : chamedani0
//Account has been created!
//Please enter a username : dsf
//Account has been created!
//Please enter a username : erwefgasd
//Account has been created!
//Here are all currently registered users :
//
//Account Name : chamedani0
//Current File : Not in a file.
//
//Account Name : dsf
//Current File : Not in a file.
//
//Account Name : erwefgasd
//Current File : Not in a file.
//
//Here are all currently registered users :
//
//Account Name : chamedani0
//Current File : BankAccount1.txt
//
//Account Name : dsf
//Current File : Not in a file.
//
//Account Name : erwefgasd
//Current File : Not in a file.
//
//Please enter a username : jdksfl
//Account has been created!
//Here are all currently registered users :
//
//Account Name : chamedani0
//Current File : BankAccount1.txt
//
//Account Name : dsf
//Current File : Not in a file.
//
//Account Name : erwefgasd
//Current File : Not in a file.
//
//Account Name : jdksfl
//Current File : Not in a file.
//
//Here are all currently registered users :
//
//Account Name : chamedani0
//Current File : BankAccount2.txt
//
//Account Name : dsf
//Current File : Not in a file.
//
//Account Name : erwefgasd
//Current File : Not in a file.
//
//Account Name : jdksfl
//Current File : Not in a file.
//
//Account found!
//The file you are trying to access, "BankAccount2.txt" is currently being edited by chamedani0 and cannot be accessed right now.
//BACK TO MENU...

