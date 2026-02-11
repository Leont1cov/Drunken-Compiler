#include <iostream>

struct Player {
    int hp;       // здоровье
    float bac;    // градус
    int money;    // деньги
    int turns;    // количество ходов
};

void drawUI(const Player& p) {
    std::cout << "\n===== DRUNKEN COMPILER =====\n";
    std::cout << "Ход: " << p.turns << "\n";
    std::cout << "Здоровье: " << p.hp << "\n";
    std::cout << "Градус: " << p.bac << "\n";
    std::cout << "Деньги: " << p.money << "\n";
}

int askAction() {
    std::cout << "\nВыбери действие:\n";
    std::cout << "1 - Выпить пиво (+BAC, -деньги)\n";
    std::cout << "2 - Закусить (+HP, -деньги)\n";
    std::cout << "3 - Ждать (снижение BAC)\n";
    std::cout << "0 - Выйти из игры\n";
    std::cout << "> ";
    
    int choice;
    std::cin >> choice;
    return choice;
}

bool checkEnding(const Player& p) {
    if (p.hp <= 0) {
        std::cout << "\n💀 Ты уничтожил печень. Конец игры.\n";
        return true;
    }
    if (p.bac >= 4.0f) {
        std::cout << "\n💀 Алкогольная кома. Конец игры.\n";
        return true;
    }
    if (p.bac <= 0.0f) {
        std::cout << "\n💀 Слишком трезвый. Депрессия.\n";
        return true;
    }
    if (p.money <= 0) {
        std::cout << "\n💀 Деньги закончились. Тебя выгнали.\n";
        return true;
    }
    if (p.turns >= 20) { // победа после 20 ходов
        std::cout << "\n🌅 Ты дожил до утра! Победа!\n";
        return true;
    }
    return false;
}

void processAction(int choice, Player& p) {
    switch (choice) {
        case 1: // пить
            p.bac += 0.3f;
            p.money -= 10;
            p.turns += 1;
            std::cout << "Ты выпил пиво.\n";
            break;
        case 2: // закусить
            p.hp += 10;
            if (p.hp > 100) p.hp = 100;
            p.money -= 5;
            p.turns += 1;
            std::cout << "Ты поел закуску.\n";
            break;
        case 3: // ждать
            p.bac -= 0.2f;
            if (p.bac < 0) p.bac = 0;
            p.turns += 1;
            std::cout << "Ты просто сидишь и отдыхаешь.\n";
            break;
        case 0:
            std::cout << "Игра завершена.\n";
            exit(0);
        default:
            std::cout << "Неверный ввод.\n";
            break;
    }
}

int main() {
    Player player = {100, 0.5f, 100, 0}; // стартовые значения

    while (true) {
        drawUI(player);

        if (checkEnding(player))
            break;

        int choice = askAction();
        processAction(choice, player);
    }

    return 0;
}