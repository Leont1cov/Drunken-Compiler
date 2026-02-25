#include "events.h"

#include "game_state.h"
#include "questions.h"

#include <cstdlib>
#include <iostream>

bool runBossBattle(const std::string& name, int& hp, float& bac, int& money, int& fights, int legacyTier) {
    std::cout << "\nБОСС: " << name << " выходит на арену!\n";
    const int rounds = 5;
    int good = 0;

    for (int i = 1; i <= rounds; ++i) {
        int ans = 0;
        int correct = 0;
        std::cout << "\nРаунд " << i << "/" << rounds << "\n";

        if (name == "Гуру Кода") askGuruQuestion(i, correct);
        else if (name == "Духовный Мудрец") askSageQuestion(i, correct);
        else if (name.find("Legacy Code") != std::string::npos) askLegacyQuestion(legacyTier, i, correct);
        else askDesignerBossQuestion(i, correct);

        std::cin >> ans;
        if (ans == correct) {
            ++good;
            std::cout << "Верно!\n";
        } else {
            hp -= 10;
            bac += 0.10f;
            std::cout << "Неверно: -10 HP, +0.10 BAC\n";
        }
    }

    fights++;

    if (good >= 3) {
        int reward = 40 + std::rand() % 31;
        money += reward;
        hp += 8;
        std::cout << "\nПобеда над боссом \"" << name << "\"!\n";
        std::cout << "Награда: +" << reward << "$\n";

        if (name.find("Legacy Code") != std::string::npos) {
            hp += (std::rand() % 51) - 25;
            bac += (static_cast<float>(std::rand() % 141) - 70.0f) / 100.0f;
            money += (std::rand() % 101) - 50;
            normalizeStats(hp, bac, money);
            if (hp == 0) hp = 1;
            if (bac <= 0.0f) bac = 0.1f;
            std::cout << "Legacy-эффект: статы хаотично изменились.\n";
        }

        if (name == "Босс Дизайнеров") {
            int fee = 10 + std::rand() % 31;
            money -= fee;
            if (money < 0) money = 0;
            std::cout << "Штраф за правки макетов: -" << fee << "$\n";
        }

        normalizeStats(hp, bac, money);
        return true;
    }

    money -= 20;
    normalizeStats(hp, bac, money);
    std::cout << "\nБосс победил. Штраф: -20$\n";
    return false;
}

void unpredictableRandomEvent(int& hp, float& bac, int& money, int& fights, int hour) {
    int t = std::rand() % 6;

    if (t == 0) {
        int dmg = 5 + std::rand() % (10 + hour / 2);
        hp -= dmg;
        fights++;
        std::cout << "Внезапная драка у стойки: -" << dmg << " HP\n";
    } else if (t == 1) {
        int plus = 5 + std::rand() % 36;
        money += plus;
        std::cout << "Удача в мини-турнире: +" << plus << "$\n";
    } else if (t == 2) {
        float d = (static_cast<float>(std::rand() % 121) - 40.0f) / 100.0f;
        bac += d;
        std::cout << "Странный коктейль изменил BAC на " << (d >= 0 ? "+" : "") << d << "\n";
    } else if (t == 3) {
        bac += (std::rand() % 2 == 0) ? -0.1f : 0.1f;
        std::cout << "Реальность дрогнула. BAC изменился.\n";
    } else if (t == 4) {
        int stake = 15 + std::rand() % 31;
        std::cout << "Подпольная ставка: 1) Рискнуть " << stake << "$  2) Отказаться\n";
        int c = 2;
        std::cin >> c;
        if (c == 1 && money >= stake) {
            money -= stake;
            if (std::rand() % 100 < 45) {
                int gain = stake * (2 + std::rand() % 2);
                money += gain;
                std::cout << "Ставка сыграла! Выигрыш: +" << gain << "$\n";
            } else {
                int dmg = 6 + std::rand() % 10;
                hp -= dmg;
                std::cout << "Ставка не зашла. Тебя задело в толпе: -" << dmg << " HP\n";
            }
        } else if (c == 1) {
            std::cout << "Недостаточно денег для ставки.\n";
        } else {
            std::cout << "Ты не стал рисковать деньгами.\n";
        }
    } else {
        int stress = 4 + std::rand() % 12;
        hp -= stress;
        bac += 0.25f;
        std::cout << "Прод упал: -" << stress << " HP, +0.25 BAC\n";
    }

    normalizeStats(hp, bac, money);
}

bool rollBossSpawn(bool alreadySpawned, int chancePercent) {
    if (alreadySpawned || chancePercent <= 0) return false;
    if (chancePercent > 100) chancePercent = 100;
    return (std::rand() % 100) < chancePercent;
}

void randomEvent(int& hp, float& bac, int& money, int& fights,
                 bool& guru, bool& sage,
                 bool& l1, bool& l2, bool& l3,
                 bool& designBoss,
                 bool afterMidnight, int hour) {
    int bossGate = std::rand() % 100;
    if (bossGate < 28) {
        if (fights >= 3 && rollBossSpawn(guru, 14 + fights * 2)) {
            guru = true;
            runBossBattle("Гуру Кода", hp, bac, money, fights);
            return;
        }
        if (fights >= 5 && rollBossSpawn(l1, 12 + fights * 2)) {
            l1 = true;
            runBossBattle("Legacy Code I", hp, bac, money, fights, 1);
            return;
        }
        if (afterMidnight && hour >= 1 && rollBossSpawn(sage, 16 + hour * 3)) {
            sage = true;
            runBossBattle("Духовный Мудрец", hp, bac, money, fights);
            return;
        }
        if (afterMidnight && hour >= 2 && rollBossSpawn(l2, 11 + hour * 3)) {
            l2 = true;
            runBossBattle("Legacy Code II", hp, bac, money, fights, 2);
            return;
        }
        if (afterMidnight && hour >= 4 && fights >= 8 && rollBossSpawn(designBoss, 10 + fights)) {
            designBoss = true;
            runBossBattle("Босс Дизайнеров", hp, bac, money, fights);
            return;
        }
        if (afterMidnight && hour >= 5 && rollBossSpawn(l3, 12 + hour * 4)) {
            l3 = true;
            runBossBattle("Legacy Code III", hp, bac, money, fights, 3);
            return;
        }
    }

    int chance = std::rand() % 100;

    if (chance < 32) {
        int level = std::rand() % 3;
        int q = std::rand() % 3;
        int damage = (level == 0) ? 5 : (level == 1 ? 10 : 20);
        int ans = 0;
        int correct = 0;

        if (level == 0) {
            std::cout << "Junior задает вопрос.\n";
            if (q == 0) { std::cout << "Что такое переменная?\n1) Контейнер для данных\n2) Цикл\n3) Ошибка\n"; correct = 1; }
            else if (q == 1) { std::cout << "5 + 5 = ?\n1) 55\n2) 10\n3) 5\n"; correct = 2; }
            else { std::cout << "console.log - это...\n1) Вывод в консоль\n2) Ошибка\n3) Тип данных\n"; correct = 1; }
        } else if (level == 1) {
            std::cout << "Middle задает вопрос.\n";
            if (q == 0) { std::cout << "Что делает new в C++?\n1) Удаляет память\n2) Выделяет память в куче\n3) Создает цикл\n"; correct = 2; }
            else if (q == 1) { std::cout << "=== в JS это...\n1) Без разницы\n2) С проверкой типа\n3) Всегда быстрее\n"; correct = 2; }
            else { std::cout << "Что такое указатель?\n1) Адрес переменной\n2) Цикл\n3) Функция\n"; correct = 1; }
        } else {
            std::cout << "Senior задает вопрос.\n";
            if (q == 0) { std::cout << "RAII - это...\n1) Управление ресурсами временем жизни объекта\n2) Тип цикла\n3) Шаблон\n"; correct = 1; }
            else if (q == 1) { std::cout << "typeof null в JS = ?\n1) null\n2) object\n3) undefined\n"; correct = 2; }
            else { std::cout << "virtual в C++ нужен для...\n1) Запрета наследования\n2) Полиморфизма\n3) Удаления функции\n"; correct = 2; }
        }

        std::cin >> ans;
        if (ans == correct) {
            int reward = 4 + std::rand() % 10;
            money += reward;
            std::cout << "Верный ответ! +" << reward << "$\n";
        } else {
            hp -= damage;
            std::cout << "Неверно. -" << damage << " HP\n";
        }
        fights++;
    } else if (chance < 45) {
        std::cout << "Бесплатный шот: 1) Выпить  2) Отказаться\n";
        int c = 2;
        std::cin >> c;
        if (c == 1) {
            bac += 0.7f;
            std::cout << "Ты выпил шот. BAC резко вырос.\n";
        } else {
            std::cout << "Ты отказался от шота. Разумный выбор.\n";
        }
    } else if (chance < 63) {
        std::cout << "Случайный дизайнер тянется к кошельку!\n";
        std::cout << "Выбери действие: 1) Левый хук  2) Правый хук  3) Пинок по макету\n";
        int move = 1;
        std::cin >> move;
        int enemy = 1 + std::rand() % 3;

        if (move == enemy) {
            int stolen = 15 + std::rand() % 36;
            money -= stolen;
            std::cout << "Дизайнер увернулся и украл " << stolen << "$!\n";
        } else {
            int reward = 6 + std::rand() % 15;
            money += reward;
            std::cout << "Ты отбился! Дизайнер оставил " << reward << "$ и сбежал.\n";
        }
        fights++;
    } else {
        unpredictableRandomEvent(hp, bac, money, fights, hour);
    }

    normalizeStats(hp, bac, money);
}
