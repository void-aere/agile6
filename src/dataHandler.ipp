#include "dataHandler.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

template <class DataType>
DataHandler<DataType>::DataHandler(const std::string &dataDir) {
    namespace fs = std::filesystem;

    this->dataDir = dataDir;

    // Initialize data directory if it doesn't exist
    fs::path path = dataDir;
    if (!fs::exists(path) || !fs::is_directory(path)) fs::create_directory(path);
}

template <class DataType>
DataHandler<DataType>::~DataHandler() {
    for (DataType* entry : entries) {
        delete entry;
    }
}

template <class DataType>
void DataHandler<DataType>::loadData() {
    namespace fs = std::filesystem;

    // TODO: only load files modified since last call

    // Scan dataDir
    // Load each file into JSON
        // parse into classes based on "type"
        // append to vector

    for (const auto & dirEntry : fs::directory_iterator(dataDir)) {
        if (dirEntry.path().extension() == ".json") {
            std::fstream file;
            file.open(dirEntry.path());
            nlohmann::json data = nlohmann::json::parse(file);
            file.close();

            DataType* newEntry = DataType::fromJson(data);
            // Assert that loading went correctly
            if (newEntry == nullptr) {
                continue;
            }

            size_t entryIndex = this->getIndexByID(newEntry->getID());

            // Is this account in the list?
                // If no, add it
                // If yes, update it using pointer magic

            if (entryIndex == (size_t)-1) {
                // Add account to vector
                entries.push_back(newEntry);

            } else {
                // Account already exists
                DataType* temp = entries[entryIndex];
                entries[entryIndex] = newEntry;
                delete temp;
            }
        }
    }
}

template <class DataType>
void DataHandler<DataType>::saveData() {
    for (DataType* entry : entries) {
        this->saveToJson(entry);
    }
}

template <class DataType>
void DataHandler<DataType>::saveToJson(const DataType* entry) {
    namespace fs = std::filesystem;
    
    fs::path path = dataDir + "/" + entry->getFilename();
    if (fs::exists(path)) fs::remove(path);

    std::ofstream file;
    file.open(path);
    file << entry->toJson().dump();
    file.close();
}

template <class DataType>
std::vector<DataType*>* DataHandler<DataType>::getEntries() {
    return &entries;
}

template <class DataType>
DataType* DataHandler<DataType>::getEntryByID(const int id) {
    for (DataType* entry : entries) {
        if (entry->getID() == id) return entry;
    }

    return nullptr;
}

template <class DataType>
std::vector<DataType*> DataHandler<DataType>::getAccountsByName(const std::string& name) {
    std::vector<DataType*> matchingAccounts;

    for (DataType* entry : entries) {
        if (entry->getName() == name) {  
            matchingAccounts.push_back(entry);
        }
    }

    return matchingAccounts;
}

template <class DataType>
size_t DataHandler<DataType>::getIndexByID(const int id) {
    for (size_t i = 0; i < entries.size(); i++) {
        if (entries[i]->getID() == id) return i;
    }

    return -1;
}

template <class DataType>
bool DataHandler<DataType>::assume(int id) {
    namespace fs = std::filesystem;

    fs::path path = _getLockPath(id);
    if (fs::exists(path)) return false;

    std::ofstream file(path);
    file.close();
    return true;
}

template <class DataType>
void DataHandler<DataType>::relinquish(int id) {
    namespace fs = std::filesystem;

    fs::path path = _getLockPath(id);
    if (fs::exists(path)) fs::remove(path);
}

template <class DataType>
std::string DataHandler<DataType>::_getLockPath(int id) {
    return (dataDir + "/" + std::to_string(id) + ".lock");
}
