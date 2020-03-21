#include "game.hpp"

#define EMPTY_CHAR ' '
#define WALL_CHAR '#'
#define CRATE_CHAR 'U'
#define PAYLOAD_CHAR '*'
#define MARIO_CHAR 'm'

Game::Game(std::string fmt)
    : m_playerDirection(DirectionDown)
{
    size_t p;

    m_height = std::count(fmt.begin(), fmt.end(), '\n');
    m_grid = new Cell*[m_height];
    m_width = fmt.find("\n");
    for (int i = 0; (p = fmt.find("\n")) != std::string::npos; i++)
    {
        std::string token = fmt.substr(0, p);
        m_grid[i] = new Cell[m_width];
        for (size_t j = 0; j < token.size(); j++)
        {
            switch (token[j])
            {
                case EMPTY_CHAR:
                    m_grid[i][j] = CellEmpty;
                    break;
                case WALL_CHAR:
                    m_grid[i][j] = CellWall;
                    break;
                case CRATE_CHAR:
                    m_grid[i][j] = CellEmpty;
                    m_cratePos.push_back(makePos(i, j));
                    break;
                case PAYLOAD_CHAR:
                    m_grid[i][j] = CellEmpty;
                    m_payloadPos.push_back(makePos(i, j));
                    break;
                case MARIO_CHAR:
                    m_grid[i][j] = CellEmpty;
                    m_playerPos.y = i;
                    m_playerPos.x = j;
                    break;
                default:
                    exit(1);
            }
        }
        fmt.erase(0, p + 1);
    }
}

Game::~Game()
{
    for (size_t i = 0; i < m_height; i++)
        delete []m_grid[i];
    delete []m_grid;
}

bool Game::won()
{
    for (std::vector<Position>::iterator it = m_payloadPos.begin(); it != m_payloadPos.end(); it++)
        if (std::find(m_cratePos.begin(), m_cratePos.end(), *it) == m_cratePos.end())
            return false;
    return true;
}

void Game::move(Direction direction)
{
    m_playerDirection = direction;
    Position saved = m_playerPos;
    switch (direction)
    {
        case DirectionUp:
            m_playerPos.y--;
            break;
        case DirectionDown:
            m_playerPos.y++;
            break;
        case DirectionLeft:
            m_playerPos.x--;
            break;
        case DirectionRight:
            m_playerPos.x++;
    }
    if (!validPosition(m_playerPos) || get(m_playerPos) == CellWall)
    {
        m_playerPos = saved;
        return;
    }

    if (get(m_playerPos) == CellCrate || get(m_playerPos) == CellCrateSolved)
    {
        if (!tryMoveCrate(*std::find(
                m_cratePos.begin(), m_cratePos.end(), m_playerPos),
                direction))
            m_playerPos = saved;
    }
}

Game::Cell Game::get(int y, int x) const
{
    return get(makePos(y, x));
}

Game::Cell Game::get(const Position pos) const
{
    bool isCrate = std::find(m_cratePos.begin(), m_cratePos.end(), pos) != m_cratePos.end();
    bool isPayload = std::find(m_payloadPos.begin(), m_payloadPos.end(), pos) != m_payloadPos.end();

    if (isCrate && isPayload)
        return CellCrateSolved;
    if (isCrate)
        return CellCrate;
    if (isPayload)
        return CellPayload;
    return m_grid[pos.y][pos.x];
}

size_t Game::getHeight() const
{
    return m_height;
}

size_t Game::getWidth() const
{
    return m_width;
}

Game::Position const &Game::getPlayer() const
{
    return m_playerPos;
}

#include <iostream>
bool Game::tryMoveCrate(Position &pos, Direction direction)
{
    Position clone = pos;

    switch (direction)
    {
        case DirectionUp:
            clone.y--;
            break;
        case DirectionDown:
            clone.y++;
            break;
        case DirectionLeft:
            clone.x--;
            break;
        case DirectionRight:
            clone.x++;
    }
    // std::cout << pos.y << ", " << pos.x << "\n";
    // std::cout << get(pos) << std::endl;
    if (!validPosition(clone) || get(clone) == CellCrate || get(clone) == CellWall)
        return false;
    pos = clone;
    return true;
}

bool Game::validPosition(Position pos)
{
    return pos.x < m_width && pos.y < m_height; // < 0 overflow
}

Game::Position Game::makePos(int y, int x)
{
    Position p;

    p.y = y;
    p.x = x;
    return p;
}

bool operator==(Game::Position const &a, Game::Position const &b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(Game::Position const &a, Game::Position const &b)
{
    return !(a == b);
}
