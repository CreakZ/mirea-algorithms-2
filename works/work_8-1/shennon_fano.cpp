#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

// Структура для узла дерева Шеннона-Фано
struct Node {
    wchar_t symbol;
    int freq;
    Node* left, * right;

    Node(wchar_t s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

// Сравнение узлов по частоте (для сортировки)
bool compare(Node* a, Node* b) {
    return a->freq > b->freq;
}

// Функция для построения кодов Шеннона-Фано
void buildCodes(Node* root, const wstring& str, map<wchar_t, wstring>& codes) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->symbol] = str;
    }

    buildCodes(root->left, str + L"0", codes);
    buildCodes(root->right, str + L"1", codes);
}

// Функция для раскодирования
wstring decode(const wstring& encoded, const map<wchar_t, wstring>& codes) {
    wstring decoded;
    int index = 0;
    while (index < encoded.length()) {
        bool found = false;
        for (const auto& pair : codes) {
            if (encoded.substr(index, pair.second.length()) == pair.second) {
                decoded += pair.first;
                index += pair.second.length();
                found = true;
                break;
            }
        }
        if (!found) {
            throw runtime_error("Невозможно декодировать строку");
        }
    }
    return decoded;
}

int main() {
    locale::global(locale("ru_RU.UTF-8"));
    wcout.imbue(locale());

    wstring text = L"Дрынцы-брынцыбубен-цы, Раз-звонились удальцы, Диги-диги-диги-дон, Выхо-ди-скорее-вон!";

    map<wchar_t, int> freq;
    for (auto& ch : text) {
        freq[ch]++;
    }

    vector<Node*> nodes;
    for (auto& pair : freq) {
        nodes.push_back(new Node(pair.first, pair.second));
    }

    sort(nodes.begin(), nodes.end(), compare);

    while (nodes.size() > 1) {
        Node* left = nodes.back(); nodes.pop_back();
        Node* right = nodes.back(); nodes.pop_back();
        Node* parent = new Node(L'\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        nodes.push_back(parent);
        sort(nodes.begin(), nodes.end(), compare);
    }

    Node* root = nodes[0];

    map<wchar_t, wstring> codes;
    buildCodes(root, L"", codes);

    wstring encoded = L"";
    for (auto ch : text) {
        encoded += codes[ch];
    }

    wcout << L"Коды символов:\n";
    for (auto& pair : codes) {
        wcout << pair.first << L": " << pair.second << endl;
    }

    int text_size = text.size() * 8;
    int encoded_size = encoded.size();
    double ratio = (double)text_size / (double)encoded_size;

    wcout << L"\nЗакодированная строка:\n" << encoded << endl;

    wcout << L"\nДлина исходного текста: " << text_size << '\n';
    wcout << L"Длина полученного кода: " << encoded_size << '\n';
    wcout << L"Коэффицинет сжатия: " << ratio << '\n';

    try {
        wstring decoded = decode(encoded, codes);
        wcout << L"\nРаскодированная строка:\n" << decoded << endl;
    } catch (const runtime_error& e) {
        wcerr << e.what() << endl;
    }

    return 0;
}
