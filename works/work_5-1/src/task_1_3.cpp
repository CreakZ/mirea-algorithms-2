#include <bitset>
#include <iostream>

using std::cout, std::bitset;

int main() {
    const int n = sizeof(int) * 8;

    unsigned int x = 55;
    
    unsigned mask = (1 << (n - 1));

    cout << "Начальный вид маски: " << bitset<n>(mask) << '\n';
    cout << "Вид x: " << bitset<n>(x) << '\n';
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) {
    cout << ((x & mask) >> (n - i));
    mask = mask >> 1;
    }
    cout << '\n';
}
