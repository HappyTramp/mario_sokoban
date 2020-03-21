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

    struct Position
    {
        int y, x;
    };

    void     move(Direction direction);
    Cell     get(int y, int x) const;
    size_t   getHeight() const;
    size_t   getWidth() const;
    Position const &getPlayer() const;

private:

    size_t    m_width;
    size_t    m_height;
    Cell      **m_grid;
    Position  m_playerPos;
    Direction m_playerDirection;
};

#endif
