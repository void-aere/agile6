#pragma once

#include "dataHandler.hpp"
#include <iostream>
using std::string;

class exceptionHandler {
	private:
		string message;

	public:
		exceptionHandler();
		exceptionHandler(string);
		~exceptionHandler();

		void what();
};
