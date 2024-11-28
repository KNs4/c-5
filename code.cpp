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

    // Задание 1: Исключить дубликаты
    static void RemoveDuplicates(const string& inputFile, const string& outputFile) {
        ifstream input(inputFile, ios::binary);
        ofstream output(outputFile, ios::binary);
        vector<int> numbers;
        int num;
        while (input.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            if (find(numbers.begin(), numbers.end(), num) == numbers.end()) {
                numbers.push_back(num);
                output.write(reinterpret_cast<char*>(&num), sizeof(num));
            }
        }
        input.close();
        output.close();
    }

    // Задание 1: Исключить дубликаты в текстовом формате
    static void RemoveDuplicatesText(const string& inputFile, const string& outputFile) {
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
    }

    // Задание 4: Проверка наличия числа
    static bool ContainsNumber(const string& filename, int target) {
        ifstream file(filename);
        int num;
        while (file >> num) {
            if (num == target) return true;
        }
        return false;
    }

    // Задание 5: Сумма элементов, кратных числу
    static int SumMultiples(const string& filename, int k) {
        ifstream file(filename);
        int num, sum = 0;
        while (file >> num) {
            if (num % k == 0) sum += num;
        }
        return sum;
    }

    // Задание 6: Строки без цифр
    static void CopyLinesWithoutDigits(const string& inputFile, const string& outputFile) {
        ifstream input(inputFile);
        ofstream output(outputFile);
        string line;
        while (getline(input, line)) {
            if (none_of(line.begin(), line.end(), ::isdigit)) {
                output << line << endl;
            }
        }
        input.close();
        output.close();
    }
};

int main() {
    // Задание 1: Генерация и удаление дубликатов
    FileTasks::FillBinaryFile("binary1.dat", 10, 1, 100);
    FileTasks::RemoveDuplicates("binary1.dat", "unique_binary.dat");

    FileTasks::FillTextFileSingle("numbers.txt", 20, 1, 100);
    FileTasks::RemoveDuplicatesText("numbers.txt", "unique_text.txt");

    // Задание 4: Генерация и проверка числа
    FileTasks::FillTextFileSingle("numbers_check.txt", 20, 1, 100);
    cout << (FileTasks::ContainsNumber("numbers_check.txt", 50) ? "true" : "false") << endl;

    // Задание 5: Генерация и вычисление суммы
    FileTasks::FillTextFileMultiple("numbers_multi.txt", 5, 4, 1, 100);
    cout << FileTasks::SumMultiples("numbers_multi.txt", 5) << endl;

    // Задание 6: Генерация и копирование строк без цифр
    FileTasks::CopyLinesWithoutDigits("text.txt", "no_digits.txt");

    return 0;
}
