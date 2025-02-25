#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct LZ78Token {
    int index;  
    char nextSymbol;
};

// Функция для сжатия строки с помощью LZ78
vector<LZ78Token> compressLZ78(const string& input) {
    unordered_map<string, int> dictionary; // Словарь для подстрок
    vector<LZ78Token> tokens;              // Результирующие токены
    string current;                        // Текущая подстрока
    int dictIndex = 1;                     // Индексы в словаре начинаются с 1

    for (char c : input) {
        current += c;
        if (dictionary.find(current) == dictionary.end()) {
            // Если подстрока отсутствует в словаре, добавляем её
            string prefix = current.substr(0, current.size() - 1); // Префикс подстроки
            int prefixIndex = (prefix.empty()) ? 0 : dictionary[prefix];
            tokens.push_back({prefixIndex, c});
            dictionary[current] = dictIndex++;
            current.clear(); // Сбрасываем текущую подстроку
        }
    }

    // Если осталась незакодированная подстрока
    if (!current.empty()) {
        string prefix = current.substr(0, current.size() - 1);
        int prefixIndex = (prefix.empty()) ? 0 : dictionary[prefix];
        tokens.push_back({prefixIndex, current.back()});
    }

    return tokens;
}

string decompressLZ78(const vector<LZ78Token>& tokens) {
    vector<string> dictionary; // Словарь для декодирования
    string output;

    for (const auto& token : tokens) {
        string entry;
        if (token.index == 0) {
            // Если индекс 0, добавляем только символ
            entry = string(1, token.nextSymbol);
        } else {
            // Ищем подстроку в словаре по индексу и добавляем символ
            entry = dictionary[token.index - 1] + token.nextSymbol;
        }
        output += entry;            // Добавляем в результат
        dictionary.push_back(entry); // Добавляем в словарь
    }

    return output;
}

int main() {
    string input = "sionsinossionsinos";

    vector<LZ78Token> compressed = compressLZ78(input);
    cout << "Сжатая строка (токены):" << endl;
    for (const auto& token : compressed) {
        cout << "(" << token.index << ", " << token.nextSymbol << ")" << endl;
    }

    string decompressed = decompressLZ78(compressed);
    cout << "\nДекодированная строка:" << endl;
    cout << decompressed << endl;

    // Проверка
    if (input == decompressed) {
        cout << "\nАлгоритм успешно восстановил исходную строку!" << endl;
    } else {
        cout << "\nОшибка: декодированная строка не совпадает с исходной." << endl;
    }

    return 0;
}
