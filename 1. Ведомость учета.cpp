#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Payment {
    std::string recipient;
    int sum;
    std::string date;
};

std::vector<Payment> readPayments(const std::string& filename) {
    std::vector<Payment> payments;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return payments;
    }

    while (true) {
        std::string name, surname;
        file >> name;
        if (file.eof()) break;

        file >> surname;
        if (file.fail()) {
            std::cerr << "Ошибка чтения фамилии." << std::endl;
            break;
        }

        int sum;
        std::string date;
        file >> sum >> date;
        if (file.fail()) {
            std::cerr << "Ошибка чтения суммы или даты." << std::endl;
            break;
        }

        payments.push_back({ name + " " + surname, sum, date });

        // Игнорируем остаток строки (до 1000 символов)
        file.ignore(1000, '\n');
    }

    file.close();
    return payments;
}

void printPayments(const std::vector<Payment>& payments) {
    for (const auto& p : payments) {
        std::cout << p.recipient << " " << p.sum << " " << p.date << std::endl;
    }
}

void addPayment(const std::string& filename) {
    bool needsNewline = false;
    std::ifstream inFile(filename, std::ios::ate);
    if (inFile.is_open() && inFile.tellg() > 0) {
        inFile.seekg(-1, std::ios::end);
        char lastChar;
        inFile.get(lastChar);
        needsNewline = (lastChar != '\n');
        inFile.close();
    }
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    std::string name, surname, date;
    int sum;

    std::cout << "Введите имя получателя: ";
    std::cin >> name;
    std::cout << "Введите фамилию получателя: ";
    std::cin >> surname;

    std::cout << "Введите сумму выплаты: ";
    while (!(std::cin >> sum)) {
        std::cin.clear();
        // Очищаем буфер ввода (до 1000 символов)
        std::cin.ignore(1000, '\n');
        std::cout << "Неверный ввод суммы. Попробуйте снова: ";
    }

    std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
    std::cin >> date;

    file << name << " " << surname << " " << sum << " " << date << std::endl;
    file.close();
}

int main() {
    system("chcp 1251"); // Установить кодировку
    std::string filename = "C:\\Users\\user\\Documents\\Программы\\cpp\\21.5\\1. Ведомость учета\\payments.txt";
    std::string command;

    std::cout << "Введите команду (list или add): ";
    std::cin >> command;

    if (command == "list") {
        std::vector<Payment> payments = readPayments(filename);
        printPayments(payments);
    }
    else if (command == "add") {
        addPayment(filename);
    }
    else {
        std::cerr << "Неверная команда." << std::endl;
    }
}