#include "Array.h"

Array::Array(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    data = new string[capacity];
}

Array::~Array() {
    delete[] data;
}

void Array::add(int index, const string& value) {
    if (index < 0 || index > size) {
        cout << "Invalid index.\n";
        return;
    }
    if (size == capacity) {
        capacity *= 2;
        string* newData = new string[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void Array::addToEnd(const string& value) {
    add(size, value);
}

string Array::get(int index) const {
    if (index < 0 || index >= size) {
        return "";
    }
    return data[index];
}

void Array::remove(int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid index.\n";
        return;
    }
    for (int i = index; i < size; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void Array::set(int index, const string& value) {
    if (index < 0 || index >= size) {
        cout << "Invalid index!\n";
        return;
    }
    data[index] = value;
}

int Array::length() const {
    return size;
}

void Array::print(const fs::path& filePath) const {
    cout << filePath.filename().string() << ": ";
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << "\n";
}

void Array::saveToFile(const fs::path& filePath) const {
    ofstream file(filePath);
    file << "Array\n";
    for (int i = 0; i < size; i++) {
        file << data[i] << "\n";
    }
    file.close();
}

void Array::loadFromFile(const fs::path& filePath) {
    ifstream file(filePath);
    string header;
    file >> header;
    string value;
    while (file >> value) {
        addToEnd(value);
    }
    file.close();
} 
