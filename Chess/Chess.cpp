#include <iostream>
#include "Game.h"

Game* game;

int main()
{
    game = new Game();
    game->run(640, 640, "Chess", 1000);

    return 0;
}
