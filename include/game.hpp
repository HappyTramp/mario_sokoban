#ifndef GAME_HPP
# define GAME_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

class Game
{
public:
    Game(std::string fmt);
    Game(std::ifstream &file);
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
        CellCrateSolved
    };

    struct Position
    {
        size_t y, x;
    };

    bool     won();
    void     move(Direction direction);
    void     undo();
    void     reset();
    Cell     get(int y, int x) const;
    Cell     get(Position pos) const;
    size_t   getHeight() const;
    size_t   getWidth() const;
    Position const &getPlayer() const;
    Direction getPlayerDirection() const;

private:

    size_t    m_width;
    size_t    m_height;
    Cell      **m_grid;
    Position  m_playerPos;
    Direction m_playerDirection;
    std::vector<Position> m_cratePos;
    std::vector<Position> m_payloadPos;
    std::stack< std::pair<Position, std::vector<Position> > > m_history;

    void construct(std::string fmt);
    void findWidth(std::string fmt);
    bool tryMoveCrate(Position &pos, Direction direction);
    bool validPosition(Position pos);

    static Position makePos(int y, int x);
};

bool operator==(Game::Position const &a, Game::Position const &b);
bool operator!=(Game::Position const &a, Game::Position const &b);

#endif
