#include "game_state.h"

#include <cstdio>
#include <fstream>
#include <string>

const char* SAVE_FILE = "savegame.txt";

void normalizeStats(int& hp, float& bac, int& money) {
    if (hp > 100) hp = 100;
    if (hp < 0) hp = 0;
    if (bac < 0.0f) bac = 0.0f;
    if (bac > 5.0f) bac = 5.0f;
    if (money < 0) money = 0;
}

void normalizeState(GameState& s) {
    normalizeStats(s.hp, s.bac, s.money);
    if (s.minutes < 0) s.minutes = 0;
    while (s.minutes >= 60) {
        s.minutes -= 60;
        s.hour++;
    }
    if (s.hour >= 24) {
        s.hour %= 24;
        s.afterMidnight = true;
    }
    if (s.hour < 0) s.hour = 0;
}

bool saveGame(const GameState& s) {
    std::ofstream out(SAVE_FILE);
    if (!out.is_open()) return false;

    out << "DRUNKEN_COMPILER_SAVE_V1\n";
    out << s.hp << ' ' << s.bac << ' ' << s.money << '\n';
    out << s.hour << ' ' << s.minutes << ' ' << s.afterMidnight << '\n';
    out << s.liters << ' ' << s.fights << ' ' << s.foodBuff << '\n';
    out << s.guru << ' ' << s.sage << ' ' << s.l1 << ' ' << s.l2 << ' ' << s.l3 << ' ' << s.designBoss << '\n';

    return out.good();
}

bool loadGame(GameState& s) {
    std::ifstream in(SAVE_FILE);
    if (!in.is_open()) return false;

    std::string header;
    in >> header;
    if (header != "DRUNKEN_COMPILER_SAVE_V1") return false;

    in >> s.hp >> s.bac >> s.money;
    in >> s.hour >> s.minutes >> s.afterMidnight;
    in >> s.liters >> s.fights >> s.foodBuff;
    in >> s.guru >> s.sage >> s.l1 >> s.l2 >> s.l3 >> s.designBoss;

    if (!in.good() && !in.eof()) return false;

    normalizeState(s);
    return true;
}

bool hasSaveFile() {
    std::ifstream in(SAVE_FILE);
    return in.good();
}

void clearSaveFile() {
    std::remove(SAVE_FILE);
}