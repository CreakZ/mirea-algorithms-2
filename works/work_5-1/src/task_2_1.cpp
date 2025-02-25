#include <iostream>

using std::cout, std::cerr, std::cin;

int main() {
    int n;
    while (true) {
        cout << "Введите количество чисел в массиве (от 1 до 8)\n";
        cin >> n;
        if (n < 1 || n > 8) {
            cerr << "Ошибка: число не принадлежит диапазону!\n";
        } else {
            break;
        }
    }

    unsigned char bit_nums = 0, mask = 1;
    for (int i = 0; i < n; i++) {
        int num;
        while (true) {
            cout << "Введите " << i + 1 << " число (от 0 до 7)\n";
            cin >> num;
            if (num < 0 || num > 7) {
                cerr << "Ошибка: число не принадлежит диапазону!\n";
            } else {
                break;
            }
        }

        bit_nums |= (mask << num);
    }

    const int unsinged_char_bitsize = sizeof(unsigned char) * 8;
    for (int i = 0; i < unsinged_char_bitsize; i++) {
        if (bit_nums & (mask << i)) {
            cout << i;
            if (i != unsinged_char_bitsize - 1) {
                cout << ' ';
            }
        }
    }

    cout << '\n';
}
