#pragma once

struct GameState {
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
};

extern const char* SAVE_FILE;

void normalizeStats(int& hp, float& bac, int& money);
void normalizeState(GameState& s);

bool saveGame(const GameState& s);
bool loadGame(GameState& s);
bool hasSaveFile();
void clearSaveFile();
