#pragma once
#include "player.h"

class Game {
public:
    void run();

private:
    Player player;

    bool checkEnding();
    void processAction(int choice);
};
