#include <iostream>
#include <cstdlib>
#include <ctime>

void printBar() {
    std::cout << "\n====================================\n";
    std::cout << "        (╯°□°）╯︵ ┻━┻\n";
    std::cout << "          DRUNKEN COMPILER\n";
    std::cout << "====================================\n";
}

void printSunrise() {
    std::cout << "\n\n";
    std::cout << "        \\  |  /\n";
    std::cout << "      --  ☀  --\n";
    std::cout << "        /  |  \\\n";
    std::cout << "\nТы дожил до рассвета!\n";
}

void randomEvent(int& hp, float& bac, int& money, int& fights) {

    int chance = std::rand() % 100;

    if (chance < 40) {

        int level = std::rand() % 3; // 0 - junior, 1 - middle, 2 - senior

        std::cout << "\n";

        if (level == 0)
            std::cout << "🟢 Junior-программист подходит к тебе.\n";
        else if (level == 1)
            std::cout << "🟡 Middle-программист оценивающе смотрит.\n";
        else
            std::cout << "🔴 Senior-программист медленно поворачивается...\n";

        int question = std::rand() % 3;
        int damage = 5;

        if (level == 1) damage = 10;
        if (level == 2) damage = 20;

        int answer;
        int correctAnswer = 0;

        // ================= JUNIOR =================
        if (level == 0) {

            if (question == 0) {
                std::cout << "Что такое переменная?\n";
                std::cout << "1) Контейнер для данных\n2) Цикл\n3) Ошибка\n";
                correctAnswer = 1;
            }
            else if (question == 1) {
                std::cout << "Что выведет: 5 + 5 ?\n";
                std::cout << "1) 55\n2) 10\n3) 5\n";
                correctAnswer = 2;
            }
            else {
                std::cout << "Что такое console.log?\n";
                std::cout << "1) Вывод в консоль\n2) Ошибка\n3) Тип данных\n";
                correctAnswer = 1;
            }
        }

        // ================= MIDDLE =================
        else if (level == 1) {

            if (question == 0) {
                std::cout << "Что делает оператор new в C++?\n";
                std::cout << "1) Удаляет память\n2) Выделяет память в куче\n3) Создает цикл\n";
                correctAnswer = 2;
            }
            else if (question == 1) {
                std::cout << "Разница между == и === в JS?\n";
                std::cout << "1) Нет разницы\n2) === проверяет тип\n3) === быстрее\n";
                correctAnswer = 2;
            }
            else {
                std::cout << "Что такое указатель?\n";
                std::cout << "1) Адрес переменной\n2) Цикл\n3) Функция\n";
                correctAnswer = 1;
            }
        }

        // ================= SENIOR =================
        else {

            if (question == 0) {
                std::cout << "Что такое RAII в C++?\n";
                std::cout << "1) Управление ресурсами через объект\n2) Тип цикла\n3) Шаблон функции\n";
                correctAnswer = 1;
            }
            else if (question == 1) {
                std::cout << "Что выведет typeof null в JS?\n";
                std::cout << "1) null\n2) object\n3) undefined\n";
                correctAnswer = 2;
            }
            else {
                std::cout << "Что делает virtual в C++?\n";
                std::cout << "1) Запрещает наследование\n2) Включает полиморфизм\n3) Удаляет функцию\n";
                correctAnswer = 2;
            }
        }

        std::cin >> answer;

        if (answer == correctAnswer) {
            int reward = 5 + std::rand() % 11; // 5-15$
            money += reward;
            std::cout << "✅ Правильно! Он уважительно кивает.\n";
            std::cout << "💵 Ты получил +" << reward << "$\n";
        }
        else {
            hp -= damage;
            std::cout << "❌ Неверно. Он разочарован.\n";
            std::cout << "💔 -" << damage << " HP\n";
        }

        fights++;
    }

    else if (chance < 55) {
        std::cout << "\n🍸 Бармен ставит бесплатный шот.\n";
        std::cout << "1) Выпить\n2) Отказаться\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            bac += 0.7f;
            std::cout << "Ты рискнул.\n";
        }
    }
}

int main() {

    std::srand(std::time(0));

    int hp = 100;
    float bac = 0.5f;
    int money = 100;

    int hour = 22;
    int minutes = 0;
    bool afterMidnight = false;

    int liters = 0;
    int fights = 0;
    int foodBuff = 0;

    while (true) {

        system("cls"); // Очистка консоли

        printBar();

        std::cout << "HP: " << hp
            << "  BAC: " << bac
            << "  $: " << money << "\n";

        std::cout << "Время: ";
        if (hour < 10) std::cout << "0";
        std::cout << hour << ":";
        if (minutes < 10) std::cout << "0";
        std::cout << minutes << "\n";

        std::cout << "\n1) Пиво (20$)\n";
        std::cout << "2) Виски (40$)\n";
        std::cout << "3) Чебурек (25$)\n";
        std::cout << "4) Ничего не делать\n";
        std::cout << "5) Выйти\n";

        int choice;
        std::cin >> choice;

        if (choice == 5) {
            std::cout << "Ты решил уйти.\n";
            break;
        }

        if (choice == 1 && money >= 20) {
            money -= 20;
            liters++;
            if (foodBuff > 0)
                bac += 0.2f;
            else
                bac += 0.4f;
            minutes += 20;
        }
        else if (choice == 2 && money >= 40) {
            money -= 40;
            liters++;
            if (foodBuff > 0)
                bac += 0.4f;
            else
                bac += 0.8f;
            minutes += 25;
        }
        else if (choice == 3 && money >= 25) {
            money -= 25;
            hp += 15;
            if (hp > 100) hp = 100;
            foodBuff = 3;
            minutes += 15;
            std::cout << "Ты съел чебурек. Защита на 3 хода.\n";
            system("pause");
        }
        else if (choice == 4) {
            minutes += 15;
            bac -= 0.2f;
            if (bac < 0) bac = 0;
        }
        else {
            std::cout << "Недостаточно денег!\n";
            system("pause");
            continue;
        }

        if (foodBuff > 0)
            foodBuff--;

        while (minutes >= 60) {
            minutes -= 60;
            hour++;
        }

        if (hour >= 24) {
            hour = 0;
            afterMidnight = true;
        }

        randomEvent(hp, bac, money, fights);

        if (hp <= 0) {
            std::cout << "\nПечень не выдержала.\n";
            break;
        }

        if (bac >= 4.0f) {
            std::cout << "\nТы перепил. Игра окончена.\n";
            break;
        }

        if (bac <= 0.0f) {
            std::cout << "\nСлишком трезво. Стало грустно.\n";
            break;
        }

        if (money <= 0) {
            std::cout << "\nДеньги закончились. Тебя вывели из бара.\n";
            break;
        }

        if (afterMidnight && hour >= 6) {
            printSunrise();

            std::cout << "\n===== СТАТИСТИКА =====\n";
            std::cout << "Выпито: " << liters << "\n";
            std::cout << "Драк: " << fights << "\n";
            std::cout << "Денег осталось: " << money << "\n";

            if (bac > 1.5f && bac < 3.0f)
                std::cout << "Статус: Senior Drinker\n";
            else
                std::cout << "Статус: Junior Trainee\n";

            break;
        }

        system("pause");
    }

    std::cout << "\nHave a nice compile.\n";
    return 0;
}