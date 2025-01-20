#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cctype>

using namespace std;

class FileTasks {
public:
    // Генерация бинарного файла
    static void FillBinaryFile(const string& binaryFile, int count, int minValue, int maxValue) {
        ofstream binary(binaryFile, ios::binary);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(minValue, maxValue);

        for (int i = 0; i < count; ++i) {
            int value = dist(gen);
            binary.write(reinterpret_cast<char*>(&value), sizeof(value));
        }
        binary.close();
    }

    // Генерация текстового файла с числами по одному в строке
    static void FillTextFileSingle(const string& textFile, int count, int minValue, int maxValue) {
        ofstream text(textFile);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(minValue, maxValue);

        for (int i = 0; i < count; ++i) {
            text << dist(gen) << "\n";
        }
        text.close();
    }

    // Генерация текстового файла с числами по несколько в строке
    static void FillTextFileMultiple(const string& textFile, int rows, int columns, int minValue, int maxValue) {
        ofstream text(textFile);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(minValue, maxValue);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                text << dist(gen) << (j == columns - 1 ? "\n" : " ");
            }
        }
        text.close();
    }

    // Чтение содержимого текстового файла
    static void ReadTextFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << endl;
    }

    // Задание 1: Исключить дубликаты
    static void RemoveDuplicates(const string& inputFile, const string& outputFile) {
        cout << "Начальный текстовый файл: " << endl;
        ReadTextFile(inputFile);

        ifstream input(inputFile);
        ofstream output(outputFile);
        vector<int> numbers;
        int num;
        while (input >> num) {
            if (find(numbers.begin(), numbers.end(), num) == numbers.end()) {
                numbers.push_back(num);
                output << num << "\n";
            }
        }
        input.close();
        output.close();

        cout << "Конечный текстовый файл после удаления дубликатов: " << endl;
        ReadTextFile(outputFile);
    }

    // Задание 4: Проверка наличия числа
    static void ContainsNumber(const string& filename) {
        // Сначала выводим содержимое файла
        cout << "Начальный текстовый файл: " << endl;
        ReadTextFile(filename);

        // Ввод числа, которое хотим найти
        cout << "Введите число, которое хотите найти в файле: ";
        int target;
        cin >> target; // Ввод числа с клавиатуры

        ifstream file(filename);
        int num;
        bool found = false;
        while (file >> num) {
            if (num == target) {
                found = true;
                break;
            }
        }
        file.close();

        cout << "Результат поиска числа " << target << ": " << (found ? "найдено" : "не найдено") << endl;
    }

    // Задание 5: Сумма элементов, кратных числу
    static void SumMultiples(const string& filename) {
        cout << "Введите число, на которое должны быть кратны элементы: ";
        int k;
        cin >> k; // Ввод числа с клавиатуры

        cout << "Начальный текстовый файл: " << endl;
        ReadTextFile(filename);

        ifstream file(filename);
        int num, sum = 0;
        while (file >> num) {
            if (num % k == 0) sum += num;
        }
        file.close();

        cout << "Сумма чисел, кратных " << k << " в файле '" << filename << "' = " << sum << endl;
    }

    // Задание 6: Строки без цифр
    static void CopyLinesWithoutDigits(const string& inputFile, const string& outputFile) {
        cout << "Начальный текстовый файл: " << endl;
        ifstream input(inputFile);
        string line;
        while (getline(input, line)) {
            cout << line << endl;
        }
        input.close();

        ifstream inputAgain(inputFile);
        ofstream output(outputFile);
        int linesCount = 0;

        while (getline(inputAgain, line)) {
            if (none_of(line.begin(), line.end(), ::isdigit)) {
                output << line << endl;
                linesCount++;
            }
        }
        inputAgain.close();
        output.close();

        cout << "Конечный текстовый файл после копирования строк без цифр: " << endl;
        ReadTextFile(outputFile);

        cout << "Количество строк без цифр: " << linesCount << endl;
    }
};

int main() {
    // Задание 1: Генерация и удаление дубликатов
    FileTasks::FillTextFileSingle("numbers.txt", 20, 1, 100);
    FileTasks::RemoveDuplicates("numbers.txt", "unique_text.txt");

    // Задание 4: Генерация и проверка числа
    FileTasks::FillTextFileSingle("numbers_check.txt", 20, 1, 100);
    FileTasks::ContainsNumber("numbers_check.txt");

    // Задание 5: Генерация и вычисление суммы
    FileTasks::FillTextFileMultiple("numbers_multi.txt", 5, 4, 1, 100);
    FileTasks::SumMultiples("numbers_multi.txt");

    // Задание 6: Генерация и копирование строк без цифр
    FileTasks::CopyLinesWithoutDigits("text.txt", "no_digits.txt");

    return 0;
}
