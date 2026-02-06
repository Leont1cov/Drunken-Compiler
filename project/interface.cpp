#include <iostream>

int main() {
    int hp = 100;           
    float bac = 0.5;         
    int money = 100;         
    int time = 22 * 60;      

    while (true) {
        int hours = time / 60;
        int minutes = time % 60;

        std::cout << "\n===== DRUNKEN COMPILER =====\n";
        std::cout << "Время: " << hours << ":";

        if (minutes < 10) std::cout << "0";
    
        std::cout << minutes << "\n";

        std::cout << "Здоровье: " << hp << "\n";
        std::cout << "Градус: " << bac << "\n";
        std::cout << "Деньги: " << money << "\n";

        // условия проигрыша и победы
        if (hp <= 0) {
            std::cout << "\nТы уничтожил печень. Конец игры.\n";
            break;
        }

        if (bac >= 4.0) {
            std::cout << "\nАлкогольная кома. Конец игры.\n";
            break;
        }

        if (bac <= 0.0) {
            std::cout << "\nСлишком трезвый. Депрессия.\n";
            break;
        }

        if (money <= 0) {
            std::cout << "\nДеньги закончились. Тебя выгнали.\n";
            break;
        }

        if (time >= 6 * 60) {
            std::cout << "\nТы дожил до утра! Победа!\n";
            break;
        }

        std::cout << "\nВыбери действие:\n";
        std::cout << "1 - Выпить\n";
        std::cout << "2 - Закусить\n";
        std::cout << "3 - Ничего не делать\n";
        std::cout << "0 - Выйти\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            bac += 0.3;
            money -= 10;
            time += 20;
            std::cout << "Ты выпил.\n";
        }
        else if (choice == 2) {
            hp += 10;
            if (hp > 100) hp = 100;

            money -= 5;
            time += 10;
            std::cout << "Ты поел.\n";
        }
        else if (choice == 3) {
            bac -= 0.1;
            time += 10;
            std::cout << "Ты просто сидишь.\n";
        }
        else if (choice == 0) {
            std::cout << "Игра завершена.\n";
            break;
        }
        else {
            std::cout << "Неверный ввод.\n";
        }
    }

    return 0;
}