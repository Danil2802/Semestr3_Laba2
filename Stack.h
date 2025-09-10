#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Stack {
private:
    std::string* data;
    int top;
    int capacity;

public:
    Stack(int initialCapacity = 10);
    ~Stack();

    void push(const std::string& value);
    void pop();
    string peek() const;
    void print() const;
    void saveToFile(const fs::path& filePath) const;
    void loadFromFile(const fs::path& filePath);
};

#endif
