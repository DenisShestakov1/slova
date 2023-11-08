#include <iostream>
#include <map>
#include <fstream>
#include <string>

std::map<std::string, std::string> loadDictionaryFromFile() {
    std::map<std::string, std::string> dictionary;
    std::ifstream file("slovar.txt");

    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            std::string translation;
            file >> translation;
            dictionary[word] = translation;
        }
        file.close();
    }

    return dictionary;
}

void saveWordToFile(const std::string& word, const std::string& translation) {
    std::ofstream file("slovar.txt", std::ios::app);
    if (file.is_open()) {
        file << word << " " << translation << "\n";
        file.close();
    }
}

int main() {
    setlocale(0, "rus");

    std::map<std::string, std::string> dictionary = loadDictionaryFromFile();

    while (true) {
        std::cout << "Выберите действие:\n";
        std::cout << "1. Ввести английское слово и получить перевод на русский.\n";
        std::cout << "2. Ввести русское слово и получить перевод на английский.\n";
        std::cout << "3. Добавить новое слово в словарь.\n";
        std::cout << "0. Выход.\n";
        std::cout << "Ваш выбор: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            std::string englishWord;
            std::cout << "Введите английское слово: ";
            std::cin >> englishWord;

            auto it = dictionary.find(englishWord);
            if (it != dictionary.end()) {
                std::cout << "Перевод на русский: " << it->second << std::endl;
            }
            else {
                std::cout << "Слово не найдено в словаре." << std::endl;
            }
        }
        else if (choice == 2) {
            std::string russianWord;
            std::cout << "Введите русское слово: ";
            std::cin >> russianWord;

            for (const auto& entry : dictionary) {
                if (entry.second == russianWord) {
                    std::cout << "Перевод на английский: " << entry.first << std::endl;
                    break;
                }
            }
            std::cout << "Слово не найдено в словаре." << std::endl;
        }
        else if (choice == 3) {
            std::string englishWord, russianWord;
            std::cout << "Введите английское слово: ";
            std::cin >> englishWord;
            std::cout << "Введите перевод на русском: ";
            std::cin >> russianWord;

            dictionary[englishWord] = russianWord;
            saveWordToFile(englishWord, russianWord);

            std::cout << "Слово успешно добавлено в словарь." << std::endl;
        }
        else {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}
