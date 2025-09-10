#include "Stack.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

bool dfs(unordered_map<char, vector<char>>& graph, unordered_map<char, char>& visited, char currentTask, Stack& stack) {
    if(visited[currentTask] == 'G') { // Серый узел (цикл обнаружен)
        return false;
    }
    if(visited[currentTask] == 'B') { // Чёрный узел (уже обработан)
        return true;
    }
    
    visited[currentTask] = 'G'; // Отмечаем серым цветом (посещение начато)
    
    for(char nextTask : graph[currentTask]) {
        if(!dfs(graph, visited, nextTask, stack)) {
            return false; // Цикл найден
        }
    }
    
    visited[currentTask] = 'B'; // Завершаем посещение вершины, ставим чёрным цветом
    stack.push(string(1, currentTask)); // Преобразуем символ в строку и добавляем в стек
    return true;
}

// Основная функция проверки последовательности задач
bool canFinishTasks(vector<char>& tasks, vector<pair<char, char>> dependencies, Stack& stack) {
    // Граф зависимостей
    unordered_map<char, vector<char>> graph;
    for(pair<char, char> dep : dependencies) {
        graph[dep.first].push_back(dep.second); // Задача A зависит от задачи B
    }
    
    // Структура отслеживания состояний вершин (W=белый, G=серый, B=чёрный)
    unordered_map<char, char> visited;
    for(char task : tasks) {
        visited[task] = 'W'; // Изначально все белые (не посещены)
    }
    
    // Проходим по всем задачам
    for(char task : tasks) {
        if(visited[task] == 'W' && !dfs(graph, visited, task, stack)) {
            return false; // Найден цикл, невозможно завершение всех задач
        }
    }

    return true;
}

bool isAlnumOrSpace(char c) {
    return isalnum(c) || c == ' ';
}

bool contains(const vector<char>& vec, char value) {
    for (char item : vec) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void removeSpaces(string& str) {
    string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    str = result;
}

int main(int argc, char* argv[]) {
    // Проверка количества аргументов
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " [tasks] [dependencies]" << endl;
        return 1;
    }

    string tasksStr = argv[1];
    string depsStr = argv[2];

    // Проверка задач
    if(tasksStr.empty()) {
        cerr << "Ошибка: Нет задач для выполнения (список задач пуст)" << endl;
        return 1;
    }

    // Проверка символов
    for(char c : tasksStr) if(!isAlnumOrSpace(c)) {
        cerr << "Ошибка: Некорректные символы в задачах (разрешены только английские буквы и цифры)" << endl;
        return 1;
    }
    for(char c : depsStr) if(!isAlnumOrSpace(c)) {
        cerr << "Ошибка: Некорректные символы в задачах (разрешены только английские буквы и цифры)" << endl;
        return 1;
    }

    // Обработка зависимостей
    removeSpaces(depsStr);
    if(depsStr.length() % 2 != 0) {
        cerr << "Ошибка: Неверный формат зависимостей (количество символов должно быть чётным)" << endl;
        return 1;
    }

    Stack stack;

    // Первая команда — список задач (строку превращаем в вектор символов)
    vector<char> tasks(tasksStr.begin(), tasksStr.end());

    // Вторая команда — зависимости (парсим пары символов)
    vector<pair<char, char>> dependencies;
    istringstream dependencyStream(argv[2]); // Читаем вторую строку как поток
    char firstChar, secondChar;
    while(dependencyStream >> firstChar >> secondChar) {
        dependencies.emplace_back(firstChar, secondChar);
    }

    for(const pair<char, char>& dep : dependencies) {
    bool child_exists = contains(tasks, dep.second);
    
    if (!child_exists) {
        bool parent_exists = contains(tasks, dep.first);
        
        if (parent_exists) {
            cerr << "Ошибка: Дочерняя задача '" << dep.second 
                 << "' отсутствует, но требуется для родительской задачи '" 
                 << dep.first << "'" << endl;
            return 0;
        }
        continue;
    }
}

    // Проверка выполнимости задач
    if(canFinishTasks(tasks, dependencies, stack)) {
        cout << "Возможно" << endl;
        cout << "Порядок выполнения задач: ";
        stack.print();
    } else {
        cout << "Невозможно, есть цикл или некорректные зависимости" << endl;
    }

    return 0;
}
