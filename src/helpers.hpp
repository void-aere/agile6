#pragma once

#include <string>
using std::string;

//UI tools / formatting / string tools
void clearScreen();
void waitForInput();
string printMoney(float val);
string chop(const string& str, int width);
string pad(int width); //literally just <width> spaces
string lowercase(const string& str); //return a lowercased version of str
int searchraw(const string& source, const string& query);

//Getting user input
string inputString();
int inputInt();
int inputInt(const string& prompt);
float inputFloat();
float inputFloat(const string& prompt);
double inputDouble();
double inputDouble();
int getMenuOption(int high); //gets a menu selection option between 1 and $high
int getMenuOptionAuto(int high); //works better but will return -1 on error
void ignoreLine(); // refined usage of cin.ignore()
bool confirm(const string& prompt); // Get user confirmation (y/n)

//Working with dates
string currentDate();
bool valiDate(const string& date); //validate a date (mm-dd-yyyy)