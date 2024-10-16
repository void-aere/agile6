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
        size_t getIndexByID(const int id);
        
        // Deadlock
        bool assume(int id);
        void relinquish(int id);
        std::string _getLockPath(int id);
};

#include <dataHandler.ipp>