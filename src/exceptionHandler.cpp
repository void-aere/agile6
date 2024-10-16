#include "exceptionHandler.hpp"

using std::string;

exceptionHandler::exceptionHandler()
{
	message = string("The program has run into a problem. Please quit the program and try again.");
}

exceptionHandler::exceptionHandler(string file)
{
	message = string("The file \"") + file + "\" is not located in the program's directory.\n" 
		  "Please verify the program is up to date and try again.\n\n";
}

exceptionHandler::~exceptionHandler()
{

}

void exceptionHandler::what()
{
	std::cout << message;
	std::cin.ignore();
}
