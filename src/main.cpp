#include "game.hpp"
#include "graphics.hpp"

int main()
{
    Game game(
        "#######\n"
        "#   m #\n"
        "#*    #\n"
        "#     #\n"
        "#  U  #\n"
        "#  U  #\n"
        "#######\n"
    );

    Graphics graphics(game, "mario sokoban", 500, 500);

    while (graphics.isRunning())
        graphics.update();
    return 0;
}
