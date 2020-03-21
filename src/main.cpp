#include "game.hpp"
#include "graphics.hpp"

int main()
{
    Game game;
    Graphics graphics(game, "mario sokoban", 640, 480);

    while (graphics.isRunning())
        graphics.update();
    return 0;
}
