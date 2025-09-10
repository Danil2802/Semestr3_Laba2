#include "Stack.h"

using namespace std;

Stack::Stack(int initialCapacity) {
    capacity = initialCapacity;
    data = new string[capacity];
    top = -1;
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(const string& value) {
    if (top == capacity - 1) {
        capacity *= 2;
        string* newData = new string[capacity];
        for (int i = 0; i <= top; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[++top] = value;
}

void Stack::pop() {
    if (top == -1) {
        cout << "Stack is empty!\n";
        return;
    }
   data[top].~string();
   top--;
}

string Stack::peek() const {
    if (top == -1) {
        return "";
    }
    return data[top];
}

void Stack::print() const {
    for (int i = 0; i <= top; i++) {
        cout << data[i] << " ";
    }
    cout << "\n";
}

void Stack::saveToFile(const fs::path& filePath) const {
    ofstream file(filePath);
    file << "Stack\n";
    for (int i = 0; i <= top; i++) {
        file << data[i] << "\n";
    }
    file.close();
}

void Stack::loadFromFile(const fs::path& filePath) {
    ifstream file(filePath);
    string header;
    file >> header;
    string value;
    while (file >> value) {
        push(value);
    }
    file.close();
}
