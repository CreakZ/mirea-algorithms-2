#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using std::cout, std::cerr, std::ifstream, std::ofstream;

const int RANGE_START = 1000000;
const int RANGE_END   = 9999999;
const int RANGE_SIZE  = RANGE_END - RANGE_START + 1;
const int ULL_SIZE    = 64;

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    ifstream input("../src/input.txt");
    if (!input.is_open()) {
        cerr << "Ошибка при открытии файла\n";
        return 1;
    }

    int ull_num = RANGE_SIZE / ULL_SIZE;
    std::vector<unsigned long long> bits(ull_num, 0);

    int number;
    unsigned long long mask = 1;
    while (input >> number) {
        int index = number - RANGE_START;
        bits[index / ULL_SIZE] |= (mask << (index % ULL_SIZE));
    }
    input.close();

    ofstream output("output.txt");
    if (!output.is_open()) {
        cerr << "Ошибка при открытии файла\n";
        return 1;
    }

    for (int i = 0; i < RANGE_SIZE; i++) {
        if (bits[i / ULL_SIZE] & (mask << (i % ULL_SIZE))) {
            output << i + RANGE_START << '\n';
        }
    }
    output.close();

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> exec_time = end_time - start_time;
    cout << "Время выполнения: " << exec_time.count()
    << " секунд\n";
    size_t memory = sizeof(unsigned long long) * bits.size();
    cout << "Использовано памяти: " << memory << " байт\n";
}
