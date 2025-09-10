#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Set {
private:
    static const size_t MAX_SIZE = 100; 
    int elements[MAX_SIZE]; 
    size_t size = 0; 

public:
    void add(int element) {
        if (!contains(element)) {
            elements[size++] = element;
        }
    }
    bool contains(int element) const {
        for (size_t i = 0; i < size; ++i) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }
    size_t getSize() const {
        return size;
    }
};

int maxTruthfulTurtles(int N, const vector<pair<int, int>>& statements) {
    Set validPositions;

    for (const auto& st : statements) {
        int a = st.first;
        int b = st.second;
        
        if (a + b == N - 1) {
            
            validPositions.add(a);
        }
    }
    return validPositions.getSize();
}

bool isPositiveInteger(const string& s) {
    if (s.empty()) {
       return false;
    }
    for (char c : s) {
        if (!isdigit(c)) {
           return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 1) {
        cerr << "Usage: " << argv[0] << endl;
        return 1;
    }

    int N;
    string input;
    
    // Цикл ввода с проверкой
    while (true) {
        cout << "Укажите количество черепах: ";
        getline(cin, input);
        
        // Проверка, что ввод - положительное число
        if (!isPositiveInteger(input)) {
            cerr << "Ошибка: Введите одно положительное число." << endl;
            continue;
        }
        
        // Преобразование строки в число
        istringstream iss(input);
        if (!(iss >> N) || N == 0 || !iss.eof()) {
            cerr << "Ошибка: Некорректный ввод." << endl;
            continue;
        }
        
        break;
    }

    // Ввод данных о черепахах
    vector<pair<int, int>> statements(N);
    cout << "Введите пары чисел (a_i b_i) для каждой черепахи:" << endl;
    for (int i = 0; i < N; ++i) {
        while (true) {
            cout << "Черепаха " << (i+1) << ": ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            
            if (!(iss >> statements[i].first >> statements[i].second) || !iss.eof()) {
                cerr << "Ошибка: Введите два числа через пробел." << endl;
                continue;
            }
            string a_str = to_string(statements[i].first);
            string b_str = to_string(statements[i].second);
            if (!isPositiveInteger(a_str) || !isPositiveInteger(b_str)) {
                cerr << "Ошибка: Введите два числа через пробел." << endl;
                continue;
            }
            break;
        }
    }

    cout << "Результат: " << maxTruthfulTurtles(N, statements) << endl;

    return 0;
}
