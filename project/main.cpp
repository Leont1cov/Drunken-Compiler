#include "events.h"
#include "game_state.h"
#include "ui.h"

#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    GameState s;

    if (hasSaveFile()) {
        std::cout << "Найдено сохранение.\n";
        std::cout << "1) Новая игра\n2) Продолжить сессию\n3) Выйти\n";
        int startChoice = 0;
        std::cin >> startChoice;

        if (startChoice == 2) {
            if (loadGame(s)) {
                std::cout << "Сессия загружена. Продолжаем с того же места.\n";
                waitForEnter();
            } else {
                std::cout << "Не удалось загрузить сохранение. Запускаем новую игру.\n";
                s = GameState{};
                waitForEnter();
            }
        } else if (startChoice == 3) {
            std::cout << "До встречи!\n";
            return 0;
        } else {
            s = GameState{};
            std::cout << "Запущена новая игра.\n";
            waitForEnter();
        }
    }

    while (true) {
        clearScreen();
        printHeader();

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "HP: " << s.hp << "  BAC: " << s.bac << "  $: " << s.money << "\n";

        std::cout << "Время: ";
        if (s.hour < 10) std::cout << '0';
        std::cout << s.hour << ':';
        if (s.minutes < 10) std::cout << '0';
        std::cout << s.minutes << "\n\n";

        std::cout << "1) Пиво (20$)\n2) Виски (40$)\n3) Закуски (25$)\n4) Подождать\n5) Выйти\n";

        int choice = 0;
        std::cin >> choice;
        if (choice == 5) {
            if (saveGame(s)) {
                std::cout << "Сессия сохранена. Можешь продолжить позже.\n";
            } else {
                std::cout << "Не удалось сохранить сессию перед выходом.\n";
            }
            break;
        }

        if (choice == 1 && s.money >= 20) {
            s.money -= 20;
            s.liters++;
            s.bac += (s.foodBuff > 0) ? 0.2f : 0.4f;
            s.minutes += 20;
            std::cout << "Ты выпил пиво. +BAC и -20$.\n";
        } else if (choice == 2 && s.money >= 40) {
            s.money -= 40;
            s.liters++;
            s.bac += (s.foodBuff > 0) ? 0.4f : 0.8f;
            s.minutes += 25;
            std::cout << "Ты выпил виски. Крепко! +BAC и -40$.\n";
        } else if (choice == 3 && s.money >= 25) {
            s.money -= 25;
            s.hp += 15;
            s.foodBuff = 1;
            s.minutes += 15;
            std::cout << "Ты взял закуски. Защита от алкоголя: 1 ход.\n";
            waitForEnter();
        } else if (choice == 4) {
            s.minutes += 15;
            s.bac -= 0.2f;
            std::cout << "Ты немного перевел дух. BAC снизился.\n";
        } else {
            std::cout << "Недостаточно денег или неверный выбор.\n";
            waitForEnter();
            continue;
        }

        if (s.foodBuff > 0) s.foodBuff--;

        while (s.minutes >= 60) {
            s.minutes -= 60;
            s.hour++;
        }
        if (s.hour >= 24) {
            s.hour = 0;
            s.afterMidnight = true;
        }

        randomEvent(s.hp, s.bac, s.money, s.fights, s.guru, s.sage, s.l1, s.l2, s.l3, s.designBoss, s.afterMidnight, s.hour);
        normalizeStats(s.hp, s.bac, s.money);

        if (!saveGame(s)) {
            std::cout << "⚠ Не удалось автосохранить сессию.\n";
        }

        if (s.hp <= 0) {
            std::cout << "\nИгра окончена: здоровье на нуле.\n";
            clearSaveFile();
            break;
        }
        if (s.bac >= 4.0f) {
            std::cout << "\nИгра окончена: перебор по BAC.\n";
            clearSaveFile();
            break;
        }
        if (s.bac <= 0.0f) {
            std::cout << "\nИгра окончена: слишком трезво.\n";
            clearSaveFile();
            break;
        }
        if (s.money <= 0) {
            std::cout << "\nИгра окончена: денег нет.\n";
            clearSaveFile();
            break;
        }

        if (s.afterMidnight && s.hour >= 6) {
            printSunrise();
            std::cout << "\n===== СТАТИСТИКА =====\n";
            std::cout << "Выпито: " << s.liters << "\n";
            std::cout << "Драк/схваток: " << s.fights << "\n";
            std::cout << "Денег: " << s.money << "\n";
            std::cout << "Финальный BAC: " << s.bac << "\n";
            std::cout << "Статус: " << (s.bac < 1.5f ? "Junior" : "Senior") << "\n";
            std::cout << "Гуру Кода: " << (s.guru ? "встречен" : "нет") << "\n";
            std::cout << "Духовный Мудрец: " << (s.sage ? "встречен" : "нет") << "\n";
            std::cout << "Босс Дизайнеров: " << (s.designBoss ? "встречен" : "нет") << "\n";
            std::cout << "Legacy I/II/III: " << (s.l1 ? "I " : "") << (s.l2 ? "II " : "") << (s.l3 ? "III" : "нет") << "\n";
            clearSaveFile();
            break;
        }

        waitForEnter();
    }

    std::cout << "\nHave a nice compile.\n";
    return 0;
}
