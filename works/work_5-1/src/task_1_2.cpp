#include <iostream>

int main() {
    unsigned char x = 0;   // 11111111
    unsigned char mask = 1;// 00000000

    mask = mask << 6;      // 01000000
    x = x | mask;          // 01000000 -> 64

    std::cout << static_cast<int>(x) << '\n';
}