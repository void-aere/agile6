#include "passwordInput.hpp"

#include <stdio.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

using std::cout, std::endl;

void getPassword(char* password) {

	// Struct for terminal settings
	struct termios oldt, newt;

	//Get current terminal settings and save them to oldt
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	//Diasble echo in terminal (clear ECHO tag)
	newt.c_lflag &= ~ECHO;

	//Set the new terminal settings 
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	cout << "Enter password: ";

	//Read the user password
	int index = 0;
	char ch;
	while (index < MAX_PASSWORD_LENGTH - 1) {
		ch = getchar(); //read single character

		//Break  when enter is pressed
		if (ch == '\n' || ch == '\r') {
			break;
		}

		//Handle backspace
		if (ch == '\b' && index > 0) {
			cout << "\b \b"; //moves cursor and erases character
			index--;
		} else {
			password[index++] = ch;
			cout << '*'; //Print an asterisk in place of each character
		}
	}

	password[index] = '\0'; //null-terminate the password

	//Restore the original terminal settings to show password
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	cout << endl; //Move to the next line after password input
}
