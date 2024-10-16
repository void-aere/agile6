// #include "helpers.hpp"
#include "mainmenu.hpp"
#include "context.hpp"
#include "dataHandler.hpp"
#include "exceptionHandler.hpp"
#include "accounts/bankAccount.hpp"


#include "helpers.hpp"
int main(int argc, char *argv[]) {
    // Maybe compute a word's hash
    if (argc >= 2 && strcmp(argv[1], "hashword") == 0) {
        if (argc < 3) {
            std::cout << "what do you want me to hash?" << std::endl;
            return 1;
        }

        std::string pass = "";
        for (int i = 2; i < argc; ++i) pass += argv[i];
        std::cout << hashword(pass) << std::endl;
        return 0;
    }

    // for (int i = 0; i < argc; ++i) std::cout << argv[i] << std::endl;
    // waitForInput();

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
