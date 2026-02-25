#include "ui.h"

#include <cstdlib>
#include <iostream>

void waitForEnter() {
    std::cout << "\nНажми Enter, чтобы продолжить...";
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void printHeader() {
    std::cout << "\n=============================================\n";
    std::cout << "            DRUNKEN COMPILER                 \n";
    std::cout << "=============================================\n";
}

void printSunrise() {
    std::cout << "\n          \\  |  /\n";
    std::cout << "        --  O  --\n";
    std::cout << "          /  |  \\\n";
    std::cout << "\nТы дожил до рассвета!\n";
}
