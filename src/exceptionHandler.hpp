#pragma once

#include "dataHandler.hpp"
#include <iostream>

class exceptionHandler {
	private:
		std::string message;

	public:
		exceptionHandler();
		exceptionHandler(std::string);
		~exceptionHandler();

		void what();
};
