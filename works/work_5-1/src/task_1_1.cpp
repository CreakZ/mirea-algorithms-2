#include <iostream>

int main() {
    unsigned char x = 255;  // 11111111
    unsigned char mask = 1; // 00000000

    mask = ~(mask << 4);
    x = x & mask;

    std::cout << static_cast<int>(x) << '\n';
}
