#include "HashTable.h"
#include <iostream>
#include <string>
#include <vector>


void set(const std::string& filePath, const std::string& queryString) {
    HashTable hashTable;
    hashTable.loadFromFile(filePath);

    // Разбиваем queryString на команду и аргументы
    std::istringstream iss(queryString);
    std::vector<std::string> tokens;
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        std::cerr << "Error: Empty command\n";
        return;
    }

    std::string command = tokens[0];

    if (command == "SETADD") {
        if (tokens.size() != 3) {
            std::cerr << "Error: Invalid command format\n";
            return;
        }
        std::string key = tokens[2];
            hashTable.insert(key, "true");
    }
    else if (command == "SETDEL") {
        if (tokens.size() != 3) {
            std::cerr << "Error: Invalid command format\n";
            return;
        }
        std::string key = tokens[2];
            hashTable.remove(key);
    }
    else if (command == "SET_AT") {
        if (tokens.size() != 3) {
            std::cerr << "Error: Invalid command format\n";
            return;
        }
        std::string key = tokens[2];
        if (hashTable.get(key)=="true") {
                cout << "Element " << key << " is in the set." << endl;
        }
        else {
                cout << "Element " << key << " is not in the set." << endl;
        }
    }
    else {
        cout << "Invalid command!\n";
        return;
    }
    hashTable.saveToFile(filePath);
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

    // Открываем файл и читаем тип структуры
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Failed to open file '" << filePath << "'" << endl;
        return 1;
    }
    string structureType;
    
    if (!(file >> structureType)) {
        cerr << "Error: Cannot determine structure type" << endl;
        return 1;
    } 

    else if (structureType == "HashTable") {
        set(filePath.string(), argv[4]);
    }
    else {
        cerr << "Error: Unknown data structure type in file\n";
        return 1;
    }

    return 0;
}
