#include <iostream>
#include "Game.h"

int main()
{
    Game game = Game{};
    game.Run(640, 640, "Chess", 1000);

    return 0;
}
