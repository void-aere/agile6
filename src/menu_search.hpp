#pragma once

#include "dataHandler.hpp"

namespace menu_search {
	void start(DataHandler& db);                            // Search Options Menu
    void queryAndEditByName(DataHandler& db);               // Search by Name, Choice to Edit Matches
    void queryAndEditByAccountNumber(DataHandler& db);       // Search by Account #, Choice to Edit Matches
    const short QUIT = 3;
}