#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

template <class DataType>
class DataHandler {
    private:
        std::vector<DataType *> entries;
        std::string dataDir;

    public:
        DataHandler(const std::string &dataDir);
        ~DataHandler();

        // Loading and Saving
        void loadData();
        void saveData();
        void saveToJson(const DataType* entry);
        
        // Accessing Members
        std::vector<DataType*>* getEntries();
        DataType* getEntryByID(const int id);
        std::vector<DataType*> getAccountsByName(const std::string& name);
        size_t getIndexByID(const int id);

        // Adding new users
        bool addEntry(const DataType& entry);
        
        // Deadlock
        bool assume(int id);
        void relinquish(int id);
        std::string _getLockPath(int id);
};

#include <dataHandler.ipp>