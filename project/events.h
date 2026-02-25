#pragma once

#include <string>

bool runBossBattle(const std::string& name, int& hp, float& bac, int& money, int& fights, int legacyTier = 0);
void unpredictableRandomEvent(int& hp, float& bac, int& money, int& fights, int hour);
bool rollBossSpawn(bool alreadySpawned, int chancePercent);
void randomEvent(int& hp, float& bac, int& money, int& fights,
                 bool& guru, bool& sage,
                 bool& l1, bool& l2, bool& l3,
                 bool& designBoss,
                 bool afterMidnight, int hour);
