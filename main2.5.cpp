#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include "BinarySearchTree.h"

using namespace std;

// Функция для быстрой сортировки (QuickSort)
void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    // Выбираем опорный элемент (середина массива)
    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;
    
    while (i <= j) {
        // Ищем элемент больше опорного слева
        while (arr[i] < pivot) i++;
        
        // Ищем элемент меньше опорного справа
        while (arr[j] > pivot) j--;
        
        // Меняем элементы местами
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    // Рекурсивно сортируем левую и правую части
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

void quickSort(vector<int>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
}

bool isValidInput(const string& input) {
    istringstream iss(input);
    string token;
    
    while (iss >> token) {
        // Проверка 1: токен не должен быть пустым
        if (token.empty()) {
            return false;
        }
        
        // Проверка 2: каждый символ должен быть цифрой
        for (char c : token) {
            if (!isdigit(c)) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Проверяем количество аргументов
    if (argc < 2) {
        cerr << "Ошибка: Необходимо передать числа в качестве аргументов" << endl;
        cerr << "Использование: " << argv[0] << " число1 число2 ... 0" << endl;
        return 1;
    }
    
    // Объединяем все аргументы в одну строку
    string input;
    for (int i = 1; i < argc; i++) {
        if (i > 1) input += " ";
        input += argv[i];
    }
    
    if (!isValidInput(input)) {
        cerr << "Ошибка: Ввод содержит недопустимые символы" << endl;
        cerr << "Разрешены только цифры и пробелы" << endl;
        return 1;
    }
    
    // Проверяем, что последний символ - 0
    string lastArg = argv[argc - 1];
    if (lastArg != "0") {
        cerr << "Ошибка: Последний аргумент должен быть 0" << endl;
        return 1;
    }
    
    BinarySearchTree tree;
    istringstream iss(input);
    int value;
    
    // Считываем числа до 0
    while (iss >> value) {
        if (value == 0) {
            break;
        }
        tree.insert(value);
    }
    
    // Получаем развилки
    vector<int> branches = tree.findBranches();

    quickSort(branches);
    
    // Выводим результат
    for (int branch : branches) {
        cout << branch << " ";
    }
    cout << endl;
    
    return 0;
}
