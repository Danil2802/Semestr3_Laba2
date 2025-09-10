#include "Array.h"
#include <iostream>
#include <string>

using namespace std;

//QuickSort для строки
void quickSort(string& str, int left, int right) {
    if (left >= right) return;

    char pivot = str[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (str[i] < pivot) i++;
        while (str[j] > pivot) j--;
        if (i <= j) {
            swap(str[i], str[j]);
            i++;
            j--;
        }
    }

    quickSort(str, left, j);
    quickSort(str, i, right);
}

void buildHistogram(const string& text) {
    // Создаем массив для хранения пар (символ, количество)
    Array charCounts; // Достаточно для всех ASCII символов
    
    // Подсчитываем частоту символов (игнорируем пробелы и переводы строк)
    int counts[256] = {0};
    for (char c : text) {
        if (c != ' ' && c != '\n') {
            counts[static_cast<unsigned char>(c)]++;
        }
    }
    
    int maxCount = 0;
    string chars;

    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) {
           chars += static_cast<char>(i);
           if (counts[i] > maxCount) {
              maxCount = counts[i];
           }  
        }
    }
    
    // Сортируем символы по их кодам с помощью QuickSort
    quickSort(chars, 0, chars.size() - 1);
    
    // Строим гистограмму
    for (int level = maxCount; level > 0; level--) {
        string row;
        for (char c : chars) {
            if (counts[static_cast<unsigned char>(c)] >= level) {
                row += "#";
            } else {
                row += " ";
            }
        }
        charCounts.addToEnd(row);
    }
    
    // Добавляем строку с символами
    charCounts.addToEnd(chars);
    string get;
    for (int i = 0; i < charCounts.length(); i++) {
        get = charCounts.get(i);
        cout << get << "\n";  
    }
}

bool containsRussianLetters(const string& text) {
    for (unsigned char c : text) {
        if ((c >= 0xC0 && c <= 0xFF) || (c >= 0xD0 && c <= 0xD1)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 1) {
        cerr << "Usage: " << argv[0] << endl;
        return 1;
    }

    string input;
    bool validInput = false;

    while (!validInput) {
        cout << "Введите текст для гистограммы (только английские символы): ";
        getline(cin, input);

        if (containsRussianLetters(input)) {
            cout << "Ошибка: обнаружены русские символы. ";
            cout << "Пожалуйста, используйте только английские символы.\n";
        } else if (input.empty()) {
            cout << "Ошибка: пустой ввод. Пожалуйста, введите текст.\n";
        } else {
            validInput = true;
        }
    }

    buildHistogram(input);
    
    return 0;
}
