#include "HashTable.h"
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Bloom {
private:
    static const size_t BIT_ARRAY_SIZE = 100;
    bitset<BIT_ARRAY_SIZE> bitArray;
    HashTable hashtable;
    static const int HASH1_MULT = 31;
    static const int HASH2_MULT = 37;
    static const int HASH3_MULT = 41;
    static const int HASH4_MULT = 43;

    // Хэш-функции с модульным делением
    size_t hash1(const string& item) const {
        return hashtable.hasher(item, BIT_ARRAY_SIZE, HASH1_MULT);
    }

    size_t hash2(const string& item) const {
        string reversed = reverseString(item);
        return hashtable.hasher(reversed + "salt", BIT_ARRAY_SIZE, HASH2_MULT);
    }

    size_t hash3(const string& item) const {
        return hashtable.hasher(item + item, BIT_ARRAY_SIZE, HASH3_MULT);
    }

    size_t hash4(const string& item) const {
    string reversed = reverseString(item);
    return hashtable.hasher(item + "salt" + reversed, BIT_ARRAY_SIZE, HASH4_MULT);
    }

    static string reverseString(const string& str) {
        string reversed;
        for (int i = str.length() - 1; i >= 0; i--) {
            reversed += str[i];
        }
        return reversed;
    }

    void addToBitArray(const string& item) {
        size_t idx1 = hash1(item);
        size_t idx2 = hash2(item);
        size_t idx3 = hash3(item);
        size_t idx4 = hash4(item);
        
        bitArray.set(idx1);
        bitArray.set(idx2);
        bitArray.set(idx3);
        bitArray.set(idx4);
    }

public:
    Bloom() : hashtable() {}

    void add(const string& value) {
        addToBitArray(value);
    }

    void del() {
        bitArray.reset();
    }

    bool test(const string& value) const {
        size_t idx1 = hash1(value);
        size_t idx2 = hash2(value);
        size_t idx3 = hash3(value);
        size_t idx4 = hash4(value);
        
        return bitArray.test(idx1) && 
               bitArray.test(idx2) && 
               bitArray.test(idx3) && 
               bitArray.test(idx4);
    }

    void print(const fs::path& filePath) const {
        cout << filePath.filename().string() << ":\n" << bitArray.to_string() << endl;
    }

    void saveToFile(const fs::path& filePath) const {
        ofstream file(filePath);
        file << bitArray.to_string() << "\n";
        file.close();
    }

    void loadFromFile(const fs::path& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error: Cannot open file " << filePath << endl;
            return;
        }
        
        string bitString;
        getline(file, bitString);
        
        // Очищаем строку от лишних символов
        string cleanString;
        for (char c : bitString) {
            if (c == '0' || c == '1') {
               cleanString += c;
            }
        }
        bitString = cleanString;

        if (bitString.length() != BIT_ARRAY_SIZE) {
           cerr << "Error: Invalid bitset length in file" << endl;
           bitArray.reset();
           return;
        }

        if (!bitString.empty()) {
            try {
                bitArray = bitset<BIT_ARRAY_SIZE>(bitString);
            } catch (const exception& e) {
                cerr << "Error loading bitset: " << e.what() << endl;
                bitArray.reset(); // Сбрасываем если есть проблемы
            }
        } else {
            bitArray.reset(); // Если файл пустой, сбрасываем
        }
        
        file.close();
    }
};

void BloomCommand(const string& filePath, const string& queryString) {
    Bloom arr;
    
    // Сначала загружаем файл
    arr.loadFromFile(filePath);
    
    istringstream iss(queryString);
    vector<string> tokens;
    string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() < 2) {
        cerr << "Error: Invalid command format\n";
        return;
    }

    string command = tokens[0];

    if (command == "BLOOM_ADD") {
        if (tokens.size() != 3) {
            cerr << "Error: Invalid command format\n";
            return;
        }
        string value = tokens[2];
        arr.add(value);
    }
    else if (command == "BLOOM_DEL") {
        if (tokens.size() != 2) {
            cerr << "Error: Invalid command format\n";
            return;
        }
        arr.del();
    }   
    else if (command == "PRINT") {
        if (tokens.size() != 2) {
            cerr << "Error: Invalid command format\n";
            return;
        }
        arr.print(filePath);
    }
    else if (command == "BLOOM_TEST") {
        if (tokens.size() != 3) {
            cerr << "Error: Invalid command format\n";
            return;
        }
        string value = tokens[2]; 
        cout << (arr.test(value) ? "Вероятно да" : "Точно нет") << endl;
    }
    else {
        cout << "Invalid command!\n";
        return;
    }
    arr.saveToFile(filePath);
}

int main(int argc, char* argv[]) {
    // Проверка формата команды
    if (argc != 5 || string(argv[1]) != "--file" || string(argv[3]) != "--query") {
        cerr << "Usage: " << argv[0] << " --file <data_directory> --query '<command> <filename>'" << endl;
        return 1;
    }

    // Получаем директорию с данными
    fs::path dataDir(argv[2]);
    
    // Проверяем существование директории
    if (!fs::exists(dataDir) || !fs::is_directory(dataDir)) {
        cerr << "Error: Directory not found" << endl;
        return 1;
    }

    // Разбираем query часть
    string query(argv[4]);
    istringstream queryStream(query);
    string command, filename;
    
    if (!(queryStream >> command >> filename)) {
        cerr << "Error: Invalid query format" << endl;
        return 1;
    }

    // Формируем полный путь к файлу
    fs::path filePath = dataDir / filename;
    
    // Проверяем существование файла
    if (!fs::exists(filePath)) {
        cerr << "Error: Structure file not found" << endl;
        return 1;
    }

    BloomCommand(filePath.string(), query);

    return 0;
}
