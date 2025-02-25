#include <algorithm>
#include <array>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>

const int BASE_SIZE = 20;
const int MIN_ACCOUNT_NUMBER = 1000000;
const int MAX_ACCOUNT_NUMBER = 9999999;

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> account_dist(MIN_ACCOUNT_NUMBER, MAX_ACCOUNT_NUMBER);
std::uniform_int_distribution<int> rand_num(0, BASE_SIZE-1);

struct BankAccount {
    int account_number; 
    std::string full_name; 
    std::string address;

    BankAccount() {
        account_number = MAX_ACCOUNT_NUMBER;
        full_name = "Вася Пупкин";
        address = "Россия, г. Одинцово, Пасхальная ул., д. 1 кв.48";
    }

    BankAccount(int number, const std::string& name, const std::string& addr) {
        account_number = number;
        full_name = name;
        address = addr;
    }

    bool operator<(const BankAccount& another) const {
        return this->account_number < another.account_number;
    }
};

std::array<std::string, 20> names = {
    "Алексей",
    "Федор",
    "Герман",
    "Максим",
    "Евгений",
    "Андрей",
    "Александр",
    "Дмитрий",
    "Майк",
    "Никита",
    "Денис",
    "Данила",
    "Мухаммед",
    "Даниил",
    "Артур",
    "Трэвис",
    "Матвей",
    "Василий",
    "Григорий",
    "Николай",
};

std::array<std::string, 20> surnames = {
    "Мишин",
    "Иванов",
    "Скотт",
    "Петрушкин",
    "Лепешков",
    "Ким",
    "Ибрагимов",
    "Герасимов",
    "Тищенко",
    "Линде",
    "Русаков",
    "Переверзев",
    "Ахмедов",
    "Федотов",
    "Семенов",
    "Слонов",
    "Молчанов",
    "Титов",
    "Азазинов",
    "Геркулесов",
};

std::array<std::string, 20> addresses = {
    "Россия, г. Кисловодск, Калинина ул., д. 1 кв.42",
    "Россия, г. Владивосток, Приозерная ул., д. 18 кв.17",
    "Россия, г. Рубцовск, Школьная ул., д. 15 кв.132",
    "Россия, г. Братск, Солнечный пер., д. 15 кв.196",
    "Россия, г. Великий Новгород, Мира ул., д. 22 кв.125",
    "Россия, г. Радужный, Иванова ул., д. 14 кв.88",
    "Россия, г. Пермь, Озерная ул., д. 34 кв.69",
    "Россия, г. Йошкар-Ола, Ленина ул., д. 9 кв.69",
    "Россия, г. Воронеж, Комсомольская ул., д. 13 кв.18",
    "Россия, г. Хасавюрт, Победы ул., д. 3 кв.34",
    "Россия, г. Хасавюрт, Победы ул., д. 3 кв.34",
    "Россия, г. Рязань, Озерная ул., д. 20 кв.40",
    "Россия, г. Кызыл, Майская ул., д. 9 кв.51",
    "Россия, г. Сургут, Первомайский пер., д. 6 кв.64",
    "Россия, г. Назрань, Зеленый пер., д. 22 кв.91",
    "Россия, г. Реутов, Лесная ул., д. 17 кв.207",
    "Россия, г. Самара, Пивной пер., д. 13 кв.37",
    "Россия, г. Тольятти, Кирова ул., д. 24 кв.10",
    "США, г. Хьюстон, Навигейшн бул., д. 16",
    "Россия, г. Нефтекамск, Хуторская ул., д. 23 кв.98",
};

std::vector<BankAccount> generate_random_accounts(const int amount) {
    std::vector<BankAccount> accounts(amount);
    for (int i{}; i < amount; i++) {
        int i1 = rand_num(rng), 
            i2 = rand_num(rng), 
            i3 = rand_num(rng),
            acc_num = account_dist(rng);

        BankAccount account(acc_num, names[i1] + ' ' + surnames[i2], addresses[i3]);

        accounts[i] = account;
    }

    return accounts;
}

void create_binary_file(const std::string& filename, int accs_amount) {
    auto accounts = generate_random_accounts(accs_amount);

    std::ofstream f("data/accounts_binary.txt");
    if (!f.is_open()) {
        std::cerr << "Ошибка при открытии текстового файла\n";
        return;
    }

    for (auto &acc: accounts) {
        f << std::to_string(acc.account_number) + ';' + acc.full_name + ';' + acc.address + '\n';
    }
    f.close();

    std::ifstream in("data/accounts_binary.txt");
    if (!in.is_open()) {
        std::cerr << "Ошибка при открытии текстового файла\n";
        return;
    }

    std::vector<char> file_content((std::istreambuf_iterator<char>(in)),
                                    std::istreambuf_iterator<char>());

    in.close();

    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        std::cerr << "Ошибка при открытии бинарного файла\n";
        return;
    }

    output.write(file_content.data(), file_content.size());

    output.close();

    std::cout << "Данные успешно записаны в бинарный файл " << filename << "\n";
}

BankAccount* linear_search(std::vector<BankAccount>& accounts, int account_number) {
    for (auto &acc : accounts) {
        if (account_number == acc.account_number) {
            return &acc;
        }
    }

    return nullptr;
}

BankAccount* binary_search(
    std::vector<BankAccount>& accounts, 
    int account_number
) {
    int left = 0, right = accounts.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (accounts[mid].account_number == account_number) {
            return &accounts[mid];
        }
        if (accounts[mid].account_number < account_number) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nullptr; 
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<BankAccount> read_binary_file(const std::string& filename) {
    std::vector<BankAccount> accounts;

    std::ifstream input(filename, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Ошибка при открытии бинарного файла\n";
        return std::vector<BankAccount>{};
    }

    std::vector<char> file_content((std::istreambuf_iterator<char>(input)),
                                   std::istreambuf_iterator<char>());
    input.close();

    std::string content(file_content.begin(), file_content.end());

    std::vector<std::string> lines = split(content, '\n');

    for (std::string& line : lines) {
        auto parts = split(line, ';');

        if (parts.size() == 3) {
            BankAccount acc{};

            acc.account_number = std::stoi(parts[0]);
            acc.full_name = parts[1];
            acc.address = parts[2];

            accounts.push_back(acc);
        } else {
            std::cout << "Ожидалось 3 значения, в строке " << parts.size() << '\n';
        }
    }

    std::cout << "Данные успешно считаны из бинарного файла " << filename << "\n";

    return accounts;
}

int main() {
    const std::string filename = "data/accounts_binary.bin";
    const int files_amount = 10000;

    create_binary_file(filename, files_amount);

    auto accounts = read_binary_file(filename);

    int target_number;
    while (true) {
        std::cout << "Введите искомый номер: ";
        std::cin >> target_number;

        if (target_number < MIN_ACCOUNT_NUMBER || target_number > MAX_ACCOUNT_NUMBER) {
            std::cout << "Введенное значение не входит в диапазон [" << MIN_ACCOUNT_NUMBER << ';' << MAX_ACCOUNT_NUMBER << "]\n";
        } else {
            break;
        }
    }

    // сортировка для бинарного поиска
    std::sort(accounts.begin(), accounts.end());

    auto start = std::chrono::high_resolution_clock::now();

    auto acc = binary_search(accounts, target_number);

    auto end = std::chrono::high_resolution_clock::now();

    if (acc == nullptr) {
        std::cout << "Аккаунта с номером " << target_number << " не найдено\n";
    } else {
        std::cout << "Аккаунт с номером " << target_number << " найден!\n";
        std::cout << "Имя владельца: " << acc->full_name
                  << "\nАдрес владельца: " << acc->address << '\n';
    }

    auto duration = std::chrono::duration(end - start);

    std::cout << "Время выполнения поиска на " << files_amount << " файлов: " << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << " нс\n";
}
