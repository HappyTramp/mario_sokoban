#ifndef GAME_HPP
# define GAME_HPP

#include <string>
#include <algorithm>

class Game
{
public:
    Game(std::string fmt);
    ~Game();

    enum Direction
    {
        DirectionUp,
        DirectionDown,
        DirectionLeft,
        DirectionRight,
    };

    enum Cell
    {
        CellEmpty = 0,
        CellWall,
        CellCrate,
        CellPayload,
    };

    Cell get(int y, int x);
    size_t getHeight();
    size_t getWidth();

private:

    struct Position
    {
        int y, x;
    };

    size_t m_width;
    size_t m_height;
    Cell **m_grid;
    Position m_playerPos;
};

#endif
