#include "interface.h"
#include <iostream>

void drawUI(const Player& p) {
    int hours = p.time / 60;
    int minutes = p.time % 60;

    std::cout << "\n===== DRUNKEN COMPILER =====\n";
    std::cout << "Время: " << hours << ":";
    if (minutes < 10) std::cout << "0";
    std::cout << minutes << "\n";

    std::cout << "Здоровье: " << p.hp << "\n";
    std::cout << "Градус: " << p.bac << "\n";
    std::cout << "Деньги: " << p.money << "\n";
}

int askAction() {
    std::cout << "\nВыбери действие:\n";
    std::cout << "1 - Выпить\n";
    std::cout << "2 - Закусить\n";
    std::cout << "3 - Ничего не делать\n";
    std::cout << "0 - Выйти\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;
    return choice;
}
