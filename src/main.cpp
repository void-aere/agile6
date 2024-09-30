// #include "helpers.hpp"
#include "mainmenu.hpp"
#include "dataHandler.hpp"

int main() {
    DataHandler *db = new DataHandler("env");
    db->loadData();

    mainmenu::start(*db);

    delete db;

    // login::start();
}