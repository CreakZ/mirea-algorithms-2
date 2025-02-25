#include <iostream>
#include <array>

using std::cout, std::cerr, std::cin, std::array;

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

    array<unsigned char, 8> nums{0,0,0,0,0,0,0,0};
    unsigned char mask = 1;
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

        nums[num / 8] |= (mask << (num % 8));
    }

    for (int i = 0; i < 64; i++) {
        if (nums[i / 8] & (mask << (i % 8))) {
            cout << i;
            if (i != 63) {
                cout << ' ';
            }
        }
    }

    cout << '\n';
}
