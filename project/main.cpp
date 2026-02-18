#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

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

void normalizeStats(int& hp, float& bac, int& money) {
    if (hp > 100) hp = 100;
    if (hp < 0) hp = 0;
    if (bac < 0.0f) bac = 0.0f;
    if (bac > 5.0f) bac = 5.0f;
    if (money < 0) money = 0;
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

void askGuruQuestion(int r, int& c) {
    if (r == 1) { std::cout << "Что такое strict weak ordering в std::sort?\n1) Требование к компаратору\n2) Тип контейнера\n3) Флаг компилятора\n"; c = 1; }
    else if (r == 2) { std::cout << "Чем опасен dangling reference?\n1) Неопределенным поведением\n2) Ускорением CPU\n3) Экономией RAM\n"; c = 1; }
    else if (r == 3) { std::cout << "Что дает move semantics?\n1) Лишние копии\n2) Передачу ресурсов без копий\n3) Отключение RAII\n"; c = 2; }
    else if (r == 4) { std::cout << "Зачем virtual деструктор?\n1) Для корректного delete через base*\n2) Для красоты\n3) Для запрета наследования\n"; c = 1; }
    else { std::cout << "Что сильнее ломает OCP?\n1) if(type==...) по всему проекту\n2) Интерфейсы\n3) DI\n"; c = 1; }
}

void askSageQuestion(int r, int& c) {
    if (r == 1) { std::cout << "Что ближе к инженерной мудрости?\n1) Сложность ради эго\n2) Простота, которую можно объяснить\n3) Игнор ревью\n"; c = 2; }
    else if (r == 2) { std::cout << "Метрика растет, а пользователи страдают. Что делать?\n1) Верить только графику\n2) Проверять контекст и фидбек\n3) Скрыть дашборд\n"; c = 2; }
    else if (r == 3) { std::cout << "Техдолг - это...\n1) Цена скорости без осознанности\n2) Просто баг\n3) Вид зарплаты\n"; c = 1; }
    else if (r == 4) { std::cout << "Главное в архитектурном споре?\n1) Выиграть спор\n2) Снизить риск и стоимость изменений\n3) Делать как в блоге\n"; c = 2; }
    else { std::cout << "Когда оправдан полный rewrite?\n1) Когда доказано, что постепенный рефактор хуже\n2) Всегда\n3) Никогда\n"; c = 1; }
}

void askLegacyQuestion(int tier, int r, int& c) {
    c = 1;
    if (tier == 1) {
        if (r == 1) std::cout << "Первое правило legacy?\n1) Зафиксировать поведение тестами\n2) Переписать все\n3) Катить без проверки\n";
        else if (r == 2) std::cout << "Опаснее всего в старом C++?\n1) Неявное владение памятью\n2) constexpr\n3) std::array\n";
        else if (r == 3) std::cout << "Как снижать риск релиза?\n1) Canary/feature flags\n2) 100% rollout\n3) Без мониторинга\n";
        else if (r == 4) { std::cout << "Observability помогает...\n1) Декорировать код\n2) Быстро находить причины инцидентов\n3) Магией чинить баги\n"; c = 2; }
        else std::cout << "Какой smell критичен?\n1) God object\n2) README\n3) Unit-тесты\n";
    } else if (tier == 2) {
        if (r == 1) std::cout << "Что такое strangler pattern?\n1) Постепенная замена старой системы\n2) SQL-инъекция\n3) Вид GC\n";
        else if (r == 2) std::cout << "Почему big-bang миграция рискованна?\n1) Большой blast radius\n2) Меньше работы\n3) Всегда быстрее\n";
        else if (r == 3) std::cout << "Неизвестное поведение legacy - что делать?\n1) Characterization tests\n2) Гадать\n3) Удалить логи\n";
        else if (r == 4) std::cout << "Устойчивый рефакторинг - это...\n1) Малые обратимые шаги\n2) Один гигантский PR\n3) Никак\n";
        else { std::cout << "При падении продакшена сначала...\n1) Искать виноватых\n2) Стабилизировать, потом разбирать\n3) Отключить алерты\n"; c = 2; }
    } else {
        if (r == 1) std::cout << "Data race приводит к...\n1) Неопределенному поведению\n2) Только warning\n3) Всегда безопасно\n";
        else if (r == 2) std::cout << "Idempotency нужна для...\n1) Безопасных ретраев\n2) Красоты кода\n3) Меньше логов\n";
        else if (r == 3) std::cout << "Зачем ограничивать coupling?\n1) Чтобы удешевить изменения\n2) Ради моды\n3) Для хаоса\n";
        else if (r == 4) std::cout << "Опасность high-load legacy?\n1) Непредсказуемые latency spikes\n2) Комментарии\n3) CI\n";
        else std::cout << "Как побеждать хаос?\n1) Границы, метрики, дисциплина\n2) Hero coding\n3) Случайные решения\n";
    }
}

void askDesignerBossQuestion(int r, int& c) {
    c = 1;
    if (r == 1) std::cout << "Что важнее в продукте?\n1) UX + стабильность\n2) Только красота\n3) Только бэкенд\n";
    else if (r == 2) std::cout << "Здоровый компромисс - это...\n1) MVP с измеримой ценностью\n2) Бесконечный пиксель-перфект\n3) Без релиза\n";
    else if (r == 3) std::cout << "Что спасает от спорных редизайнов?\n1) A/B тесты и метрики\n2) Интуиция одного человека\n3) Игнор исследований\n";
    else if (r == 4) std::cout << "Design system нужна для...\n1) Консистентности и скорости\n2) Только презентаций\n3) Хаоса\n";
    else std::cout << "Финал: релиз должен максимизировать...\n1) Ценность для пользователя\n2) Цвет кнопки любой ценой\n3) Хаос\n";
}

bool runBossBattle(const std::string& name, int& hp, float& bac, int& money, int& fights, int legacyTier = 0) {
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
    if (alreadySpawned || chancePercent <= 0) {
        return false;
    }
    if (chancePercent > 100) {
        chancePercent = 100;
    }
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

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    int hp = 100;
    float bac = 0.5f;
    int money = 100;

    int hour = 22;
    int minutes = 0;
    bool afterMidnight = false;

    int liters = 0;
    int fights = 0;
    int foodBuff = 0;

    bool guru = false;
    bool sage = false;
    bool l1 = false;
    bool l2 = false;
    bool l3 = false;
    bool designBoss = false;

    while (true) {
        clearScreen();
        printHeader();

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "HP: " << hp << "  BAC: " << bac << "  $: " << money << "\n";

        std::cout << "Время: ";
        if (hour < 10) std::cout << '0';
        std::cout << hour << ':';
        if (minutes < 10) std::cout << '0';
        std::cout << minutes << "\n\n";

        std::cout << "1) Пиво (20$)\n2) Виски (40$)\n3) Закуски (25$)\n4) Подождать\n5) Выйти\n";

        int choice = 0;
        std::cin >> choice;
        if (choice == 5) { std::cout << "Ты решил уйти.\n"; break; }

        if (choice == 1 && money >= 20) {
            money -= 20;
            liters++;
            bac += (foodBuff > 0) ? 0.2f : 0.4f;
            minutes += 20;
            std::cout << "Ты выпил пиво. +BAC и -20$.\n";
        } else if (choice == 2 && money >= 40) {
            money -= 40;
            liters++;
            bac += (foodBuff > 0) ? 0.4f : 0.8f;
            minutes += 25;
            std::cout << "Ты выпил виски. Крепко! +BAC и -40$.\n";
        } else if (choice == 3 && money >= 25) {
            money -= 25;
            hp += 15;
            foodBuff = 1;
            minutes += 15;
            std::cout << "Ты взял закуски. Защита от алкоголя: 1 ход.\n";
            waitForEnter();
        } else if (choice == 4) {
            minutes += 15;
            bac -= 0.2f;
            std::cout << "Ты немного перевел дух. BAC снизился.\n";
        } else {
            std::cout << "Недостаточно денег или неверный выбор.\n";
            waitForEnter();
            continue;
        }

        if (foodBuff > 0) foodBuff--;

        while (minutes >= 60) {
            minutes -= 60;
            hour++;
        }
        if (hour >= 24) {
            hour = 0;
            afterMidnight = true;
        }

        randomEvent(hp, bac, money, fights, guru, sage, l1, l2, l3, designBoss, afterMidnight, hour);
        normalizeStats(hp, bac, money);

        if (hp <= 0) { std::cout << "\nИгра окончена: здоровье на нуле.\n"; break; }
        if (bac >= 4.0f) { std::cout << "\nИгра окончена: перебор по BAC.\n"; break; }
        if (bac <= 0.0f) { std::cout << "\nИгра окончена: слишком трезво.\n"; break; }
        if (money <= 0) { std::cout << "\nИгра окончена: денег нет.\n"; break; }

        if (afterMidnight && hour >= 6) {
            printSunrise();
            std::cout << "\n===== СТАТИСТИКА =====\n";
            std::cout << "Выпито: " << liters << "\n";
            std::cout << "Драк/схваток: " << fights << "\n";
            std::cout << "Денег: " << money << "\n";
            std::cout << "Финальный BAC: " << bac << "\n";
            std::cout << "Статус: " << (bac < 1.5f ? "Junior" : "Senior") << "\n";
            std::cout << "Гуру Кода: " << (guru ? "встречен" : "нет") << "\n";
            std::cout << "Духовный Мудрец: " << (sage ? "встречен" : "нет") << "\n";
            std::cout << "Босс Дизайнеров: " << (designBoss ? "встречен" : "нет") << "\n";
            std::cout << "Legacy I/II/III: " << (l1 ? "I " : "") << (l2 ? "II " : "") << (l3 ? "III" : "нет") << "\n";
            break;
        }

        waitForEnter();
    }

    std::cout << "\nHave a nice compile.\n";
    return 0;
}
