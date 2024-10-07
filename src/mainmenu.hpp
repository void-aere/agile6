#pragma once

#include "dataHandler.hpp"

namespace mainmenu {
	void start(DataHandler& db);
	void print();
	const short QUIT = 5;
}