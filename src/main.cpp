// #include "helpers.hpp"
#include "mainmenu.hpp"
#include "context.hpp"
#include "dataHandler.hpp"
#include "exceptionHandler.hpp"
#include "accounts/bankAccount.hpp"


#include "helpers.hpp"
int main() {

    try {
        Context *context = new Context("env");
        if (!context->checkDataDir()) throw exceptionHandler("env");

        context->setBankHandler(new DataHandler<bankAccount>("env/bank"));
        context->setUserHandler(new DataHandler<UserAccount>("env/user"));

        context->bdb()->loadData();
        context->udb()->loadData();

        mainmenu::login(*context);
        mainmenu::start(*context);

        delete context;

        // login::start();
    } catch (exceptionHandler err) {
        err.what();
    }
}
