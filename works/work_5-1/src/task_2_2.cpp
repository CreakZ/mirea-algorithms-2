#include <iostream>

using std::cout, std::cerr, std::cin;

int main() {
    int n;
    while (true) {
        cout << "Введите количество чисел в массиве (от 1 до 64)\n";
        cin >> n;
        if (n < 1 || n > 64) {
            cerr << "Ошибка: число не принадлежит диапазону!\n";
        } else {
            break;
        }
    }

    unsigned long long bit_nums = 0, mask = 1;
    for (int i = 0; i < n; i++) {
        int num;
        while (true) {
            cout << "Введите " << i + 1 << " число (от 0 до 63)\n";
            cin >> num;
            if (num < 0 || num > 63) {
                cerr << "Ошибка: число не принадлежит диапазону!\n";
            } else {
                break;
            }
        }

        bit_nums |= (mask << num);
    }

    const int unsinged_ll_bitsize = sizeof(unsigned long long) * 8;
    for (int i = 0; i < unsinged_ll_bitsize; i++) {
        if (bit_nums & (mask << i)) {
            cout << i;
            if (i != unsinged_ll_bitsize - 1) {
                cout << ' ';
            }
        }
    }

    cout << '\n';
}
