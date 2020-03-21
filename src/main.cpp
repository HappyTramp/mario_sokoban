#include <iostream>
#include <fstream>
#include "game.hpp"
#include "graphics.hpp"

#define DEFAULT_MAP_FILENAME "map/square.sokoban"

int main(int argc, char **argv)
{
    std::ifstream file;
    if (argc == 1)
        file.open(DEFAULT_MAP_FILENAME);
    else if (argc == 2)
        file.open(argv[1]);
    else
    {
        std::cout << "Usage: " << argv[0] << " [mapfile]" << std::endl;
        return 0;
    }
    Game game(file);
    Graphics graphics(game, "mario sokoban", 500, 500);
    while (graphics.isRunning())
        graphics.update();
    return 0;
}
