#include <iostream>
#include <cstdlib>
#include <ctime>

struct Player {
    int hp;
    float bac;
    int money;
    int time;      // минуты с начала дня
    int drinks;    // сколько выпито
};

void drawUI(const Player& p) {
    int hours = (p.time / 60) % 24;
    int minutes = p.time % 60;

    std::cout << "\n===== DRUNKEN COMPILER =====\n";
    std::cout << "Время: " << hours << ":";
    if (minutes < 10) std::cout << "0";
    std::cout << minutes << "\n";

    std::cout << "HP: " << p.hp << "\n";
    std::cout << "BAC: " << p.bac << "\n";
    std::cout << "Money: " << p.money << "\n";
}

bool checkEnding(const Player& p) {
    if (p.hp <= 0) {
        std::cout << "\n💀 Печень отказала.\n";
        return true;
    }
    if (p.bac >= 4.0f) {
        std::cout << "\n💀 Алкогольная кома.\n";
        return true;
    }
    if (p.bac <= 0.0f) {
        std::cout << "\n💀 Слишком трезвый. Депрессия.\n";
        return true;
    }
    if (p.money <= 0) {
        std::cout << "\n💀 Деньги закончились.\n";
        return true;
    }

    // 06:00 следующего дня
    if (p.time >= 24 * 60 + 6 * 60) {
        std::cout << "\n🌅 Ты дожил до 06:00!\n";
        std::cout << "Выпито напитков: " << p.drinks << "\n";
        std::cout << "Денег осталось: " << p.money << "\n";
        return true;
    }

    return false;
}

int main() {
    std::srand(std::time(0));

    Player player = {100, 0.5f, 100, 22 * 60, 0};

    while (true) {

        drawUI(player);

        if (checkEnding(player))
            break;

        std::cout << "\n1 - Выпить пиво\n";
        std::cout << "2 - Закусить\n";
        std::cout << "3 - Ждать\n";
        std::cout << "0 - Выйти\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            int minutes = 15 + std::rand() % 16; // 15–30 минут
            player.time += minutes;
            player.bac += 0.3f;
            player.money -= 10;
            player.drinks++;
            std::cout << "Ты выпил. Прошло " << minutes << " минут.\n";
        }
        else if (choice == 2) {
            player.hp += 10;
            if (player.hp > 100) player.hp = 100;
            player.money -= 5;
            player.time += 10;
            std::cout << "Ты поел.\n";
        }
        else if (choice == 3) {
            player.bac -= 0.2f;
            if (player.bac < 0) player.bac = 0;
            player.time += 10;
            std::cout << "Ты просто сидишь.\n";
        }
        else if (choice == 0) {
            break;
        }
        else {
            std::cout << "Неверный ввод.\n";
        }
    }

    return 0;
}