#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

// Кортеж: (offset, length, next_symbol)
typedef tuple<int, int, char> LZ77_Token;

const int WINDOW_SIZE = 10;
const int LOOKAHEAD_SIZE = 5;

// LZ77 сжатие
vector<LZ77_Token> compressLZ77(const string& input) {
    vector<LZ77_Token> tokens;
    int pos = 0;

    while (pos < input.size()) {
        int best_offset = 0, best_length = 0;
        char next_symbol = input[pos];

        int search_start = max(0, pos - WINDOW_SIZE);

        for (int i = search_start; i < pos; ++i) {
            int length = 0;
            while (length < LOOKAHEAD_SIZE && i + length < pos && pos + length < input.size() && input[i + length] == input[pos + length]) {
                ++length;
            }

            if (length > best_length) {
                best_length = length;
                best_offset = pos - i;
                next_symbol = (pos + length < input.size()) ? input[pos + length] : '\0';
            }
        }

        tokens.emplace_back(best_offset, best_length, next_symbol);

        pos += best_length + 1;
    }

    return tokens;
}

// Декодирование LZ77 токенов
string decompressLZ77(const vector<LZ77_Token>& tokens) {
    string output;

    for (const auto& [offset, length, next_symbol] : tokens) {
        int start = output.size() - offset;
        for (int i = 0; i < length; ++i) {
            output += output[start + i];
        }
        if (next_symbol != '\0') {
            output += next_symbol;
        }
    }

    return output;
}

int main() {
    string input = "1110100110111001101";

    vector<LZ77_Token> compressed = compressLZ77(input);
    cout << "Сжатая строка (токены):" << endl;
    for (const auto& [offset, length, next_symbol] : compressed) {
        cout << "(" << offset << ", " << length << ", " << next_symbol << ")" << endl;
    }

    string decompressed = decompressLZ77(compressed);
    cout << "\nДекодированная строка:" << endl;
    cout << decompressed << endl;

    if (input == decompressed) {
        cout << "\nАлгоритм успешно восстановил исходную строку!" << endl;
    } else {
        cout << "\nОшибка: декодированная строка не совпадает с исходной." << endl;
    }

    return 0;
}
