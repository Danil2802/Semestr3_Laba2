#include "HashTable.h"

using namespace std;

HashTable::HashTable(int initialCapacity) {
    capacity = initialCapacity;
    table = new HashNode * [capacity]();
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        HashNode* entry = table[i];
        while (entry) {
            HashNode* prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = nullptr;
    }
    delete[] table;
}

int HashTable::hash(const std::string& key) const {
    int hash = 0;
    for (unsigned char ch : key) {
        hash = hash * 31 + ch;
    }
    return abs(hash % capacity);
}

void HashTable::insert(const std::string& key, const std::string& value) {
    if (size >= capacity * LOAD_FACTOR) { 
        rehash();
    }
    int index = hash(key);
    HashNode* prev = nullptr;
    HashNode* entry = table[index];
    while (entry && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }
    if (!entry) {
        entry = new HashNode(key, value);
        if (prev) {
            prev->next = entry;
        }
        else {
            table[index] = entry;
        }
        size++;
    }
    else {
        entry->value = value;
    }
}

void HashTable::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;
    HashNode** newTable = new HashNode*[capacity]();

    for (int i = 0; i < oldCapacity; i++) {
        HashNode* entry = table[i];
        while (entry) {
            HashNode* next = entry->next;
            int newIndex = hash(entry->key);
            entry->next = newTable[newIndex];
            newTable[newIndex] = entry;
            entry = next;
        }
    }

    delete[] table;
    table = newTable;
}

string HashTable::get(const std::string& key) const {
   int index = hash(key);
   HashNode* entry = table[index];
   while (entry) {
   if (entry->key == key) {
   return entry->value;
   }
   entry = entry->next;
   }
   return "";
}

void HashTable::remove(const std::string& key) {
    int index = hash(key);
    HashNode* prev = nullptr;
    HashNode* entry = table[index];
    while (entry && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }
    if (!entry) {
        cout << "Not found!\n";
        return;
    }
    if (prev) {
        prev->next = entry->next;
    }
    else {
        table[index] = entry->next;
    }
    delete entry;
    size--;
}

void HashTable::print(const fs::path& filePath) const {
    cout << filePath.filename().string() << ":\n";
    for (int i = 0; i < capacity; i++) {
        HashNode* entry = table[i];
        while (entry) {
            cout << "Key: " << entry->key << ", Value: " << entry->value << "\n";
            entry = entry->next;
        }
    }
}

void HashTable::saveToFile(const fs::path& filePath) const {
    ofstream file(filePath);
    file << "HashTable\n";
    for (int i = 0; i < capacity; i++) {
        HashNode* entry = table[i];
        while (entry) {
            file << entry->key << "," << entry->value << "\n";
            entry = entry->next;
        }
    }
    file.close();
}

void HashTable::loadFromFile(const fs::path& filePath) {
    ifstream file(filePath);
    string header;
    file >> header;
    string line;
    while (file >> line) {
        stringstream ss(line);
        string key, value;
        getline(ss, key, ',');
        getline(ss, value, ',');
        insert(key, value);
    }
    file.close();
}

int HashTable::count() const {
    return size; 
}

size_t HashTable::hasher(const std::string& key, size_t mod, int mult) const {
    size_t hash = 0;
    for (unsigned char ch : key) {
        hash = hash * mult + ch;
    }
    return hash % mod;
}
