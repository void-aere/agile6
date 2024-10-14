#pragma once

#include "dataHandler.hpp"

namespace menu_search {
	void start(DataHandler<bankAccount>& db);                            // Search Options Menu
    void queryAndEditByName(DataHandler<bankAccount>& db);               // Search by Name, Choice to Edit Matches
    void queryAndEditByAccountNumber(DataHandler<bankAccount>& db);       // Search by Account #, Choice to Edit Matches
    const short QUIT = 3;
}