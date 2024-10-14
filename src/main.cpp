// #include "helpers.hpp"
#include "mainmenu.hpp"
#include "dataHandler.hpp"
#include "exceptionHandler.hpp"
#include "accounts/bankAccount.hpp"

int main() {

    try {
        DataHandler<bankAccount> *db = new DataHandler<bankAccount>("env");   

        if (!db->checkForDB()) throw exceptionHandler("env");

        db->loadData();

        mainmenu::start(*db);

        delete db;

        // login::start();
    } catch (exceptionHandler err) {
        err.what();
    }
}
