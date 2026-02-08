#include "game.h"
#include "interface.h"
#include <iostream>

void Game::run() {
    player = {100, 0.5f, 100, 22 * 60};

    bool running = true;

    while (running) {
        drawUI(player);

        if (checkEnding())
            break;

        int choice = askAction();
        processAction(choice);
    }
}

bool Game::checkEnding() {
    if (player.hp <= 0) {
        std::cout << "\nТы уничтожил печень. Конец игры.\n";
        return true;
    }

    if (player.bac >= 4.0f) {
        std::cout << "\nАлкогольная кома. Конец игры.\n";
        return true;
    }

    if (player.bac <= 0.0f) {
        std::cout << "\nСлишком трезвый. Депрессия.\n";
        return true;
    }

    if (player.money <= 0) {
        std::cout << "\nДеньги закончились. Тебя выгнали.\n";
        return true;
    }

    if (player.time >= 6 * 60) {
        std::cout << "\nТы дожил до утра! Победа!\n";
        return true;
    }

    return false;
}

void Game::processAction(int choice) {
    switch (choice) {
        case 1: // пить
            player.bac += 0.3f;
            player.money -= 10;
            player.time += 20;
            std::cout << "Ты выпил.\n";
            break;

        case 2: // есть
            player.hp += 10;
            if (player.hp > 100) player.hp = 100;
            player.money -= 5;
            player.time += 10;
            std::cout << "Ты поел.\n";
            break;

        case 3: // ждать
            player.bac -= 0.1f;
            player.time += 10;
            std::cout << "Ты просто сидишь.\n";
            break;

        case 0:
            std::cout << "Игра завершена.\n";
            exit(0);

        default:
            std::cout << "Неверный ввод.\n";
    }
}
