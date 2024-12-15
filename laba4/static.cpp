#include <iostream> 

#include "lib1.cpp"
#include "lib2.cpp"

int main() {
    int a, b;
    int choice;

    std::cout << "Введите диапазон (a b): ";
    std::cin >> a >> b;

    std::cout << "Выберите алгоритм (1 - наивный, 2 - решето Эратосфена): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Количество простых чисел: " << PrimeCountNaive(a, b) << std::endl;
    } else if (choice == 2) {
        std::cout << "Количество простых чисел: " << PrimeCountSieve(a, b) << std::endl;
    }

    return 0;
}