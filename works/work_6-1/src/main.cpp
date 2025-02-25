#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <locale>

const int TABLE_SIZE = 7; // Начальный размер таблицы
const float LOAD_FACTOR = 0.75; // Коэффициент загрузки для рехеширования

// Структура товара
struct Product {
    int code;       // Шестиразрядное число (ключ)
    std::string name;
    double price;

    Product() : code(-1), name(""), price(0.0) {} 
    Product(int c, const std::string& n, double p) : code(c), name(n), price(p) {}
};

// Класс хеш-таблицы
class HashTable {
private:
    // Перечисление для модификатора setw (организация красивого вывода метода display())
    enum setw_sizes : int {
        index = 10,
        code  = 15,
        name  = 20,
        price = 15,
    };

    std::vector<Product> table;
    int current_size;

    // Хеш-функция (взятие модуля по размеру таблицы)
    int hash_function(int key) const {
        return key % table.size();
    }

    // Рехеширование (увеличение размера таблицы)
    void rehash() {
        std::vector<Product> oldTable = table;
        int new_size = table.size() * 2;
        table = std::vector<Product>(new_size, Product());

        for (const auto& item : oldTable) {
            if (item.code != -1) {
                int index = hash_function(item.code);
                while (table[index].code != -1) {
                    index = (index + 1) % table.size();
                }
                table[index] = item;
                current_size++;
            }
        }
    }

public:
    HashTable() : table(TABLE_SIZE, Product()), current_size(0) {}

    // Вставка элемента
    void insert(int code, const std::string& name, double price) {
        if (current_size >= table.size() * LOAD_FACTOR) { 
            // Реаллоцируем память для вдвое большей таблицы, если исходная заполнена не менее, чем на 75%
            rehash();
        }

        int index = hash_function(code); 
        int startIndex = index;          

        do {
            if (table[index].code == -1) {  //
                table[index].code = code;
                table[index].name = name;
                table[index].price = price;
                current_size++;
                std::cout << "Product inserted successfully.\n";
                return;
            } else if (table[index].code == code) {
                std::cout << "Product with code " << code << " already exists.\n";
                return;
            }

            // Линейное пробирование при коллизии
            index = (index + 1) % table.size();
        } while (index != startIndex);

        std::cout << "Table is full. Unable to insert new product.\n";
    }

    // Удаление элемента
    void remove(int code) {
        int idx = hash_function(code);
        int originalIdx = idx;
        int step = 0;

        while (table[idx].code != -1) {
            if (table[idx].code == code) {
                table[idx] = Product(); // Удаление элемента
                current_size--;
                std::cout << "Product with " << code << " deleted successfully.\n";
                return;
            }
            idx = (originalIdx + ++step) % table.size();
        }
        std::cout << "No product with " << code << " code found." << std::endl;
    }

    // Поиск элемента
    void search(int code) const {
        int idx = hash_function(code);
        int originalIdx = idx;
        int step = 0;

        while (table[idx].code != -1) {
            if (table[idx].code == code) {
                std::cout << "Product found: " << table[idx].name << ", price: " << table[idx].price << std::endl;
                return;
            }
            idx = (originalIdx + ++step) % table.size();
        }
        std::cout << "No product with " << code << " code found." << std::endl;
    }

    // Вывод таблицы
    void display() const {
        std::wcout.imbue(std::locale(""));

        std::cout << '\n' << std::setw(setw_sizes::index) << "Index" 
                          << std::setw(setw_sizes::code) << "Product code" 
                          << std::setw(setw_sizes::name) << "Product name" 
                          << std::setw(setw_sizes::price) << "Product price" 
                          << std::endl;

        for (int i = 0; i < table.size(); i++) {
            if (table[i].code != -1) {
                std::cout << std::setw(setw_sizes::index) << i 
                          << std::setw(setw_sizes::code) << table[i].code 
                          << std::setw(setw_sizes::name) << table[i].name 
                          << std::setw(setw_sizes::price) << table[i].price 
                          << std::endl;
            } else {
                std::cout << std::setw(setw_sizes::index) << i 
                          << std::setw(setw_sizes::code) << "<empty>" 
                          << std::setw(setw_sizes::name) << "<empty>" 
                          << std::setw(setw_sizes::price) << "<empty>" 
                          << std::endl;
            }
        }
    }
};

// Пользовательский интерфейс
void ui() {
    HashTable hashTable;

    // Добавление 5-7 записей
    hashTable.insert(123456, "IPhone 16", 799);
    hashTable.insert(654321, "MacBook Pro 2021", 133.99);
    hashTable.insert(112233, "JBL Tunes 100", 0.99);
    hashTable.insert(332211, "AOC 16T15", 109.99);
    hashTable.insert(445566, "Wooting 60HE+", 219.99);
    hashTable.insert(445567, "Something", 0.99);

    int choice;
    do {
        std::cout << "\n1. Add product\n2. Delete product\n3. Find product\n4. Display all products\n5. Quit\nYour choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int code;

                while (true) {
                    std::cout << "Enter product code (6 digits): ";
                    std::cin >> code;

                    if (code < 100000 || code > 999999) {
                        std::cout << "Code value must be in [100000;999999]\n";
                    } else {
                        break;
                    }
                }

                std::string name;
                while (true) {
                    std::cout << "Enter product name: ";
                    std::getline(std::cin >> std::ws, name);

                    if (name == "") {
                        std::cout << "Product name can't be empty\n";
                    } else {
                        break;
                    }
                }
                
                double price;
                while (true) {
                    std::cout << "Enter product price: ";
                    std::cin >> price;

                    if (price <= 0.0) {
                        std::cout << "Product price must be positive\n";
                    } else {
                        break;
                    }
                }

                hashTable.insert(code, name, price);
                break;
            }
            case 2: {
                int code;
                std::cout << "Enter product code to delete: ";
                std::cin >> code;
                hashTable.remove(code);
                break;
            }
            case 3: {
                int code;
                std::cout << "Enter product code to find: ";
                std::cin >> code;
                hashTable.search(code);
                break;
            }
            case 4: {
                hashTable.display();
                break;
            }
            case 5:
                std::cout << "Quitting...\n";
                break;
            default:
                std::cout << "Wrong choice. Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    ui();
    return 0;
}
