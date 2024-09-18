#pragma once

#include "client.hpp"
#include <string>
#include <vector>

class DataHandler {
    private:
        std::vector<Client> clientList;
        std::vector<std::string> employeeList;
        std::string dataDir;

    public:
        DataHandler(std::string dataDir);

        void loadData();

        std::vector<Client>& getClientList();
        void writeClient(Client& client);
};