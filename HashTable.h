#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class HashNode {
public:
    string key;
    string value;
    HashNode* next;
    HashNode(const string& key, const string& value) : key(key), value(value), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;
    int capacity;
    int hash(const std::string& key) const;
    int size = 0; 
    const double LOAD_FACTOR = 2;

public:
    HashTable(int initialCapacity = 10);
    ~HashTable();

    void insert(const std::string& key, const string& value);
    string get(const std::string& key) const;
    void remove(const std::string& key);
    void print(const fs::path& filePath) const;
    void saveToFile(const fs::path& filePath) const;
    void loadFromFile(const fs::path& filePath);
    int count() const;
    void rehash();
    size_t hasher(const string& key, size_t mod, int mult) const;
};

#endif
