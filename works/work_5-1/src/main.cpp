#include <cstdlib>
#include <iostream>
#include <bitset>

const int BITSET_SIZE = 8;

using std::bitset, std::cout;

void task_1() {
    unsigned char x = 255, mask = 1;

    mask = ~(mask << 4);

    x = x & mask;

    cout << static_cast<int>(x) << '\n';
}

void example_code() {
    unsigned int x = 25;
    const int n = sizeof(int) * 8;
    unsigned mask = (1 << (n - 1));

    cout << "Начальный вид маски: " << bitset<n>(mask) << '\n';
    
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & mask) >> (n - i));
        mask = mask >> 1;
    }
    cout << '\n';
}

int main() {
    task_1();
}
