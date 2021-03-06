#include "game.hpp"

#define EMPTY_CHAR        ' '
#define WALL_CHAR         '#'
#define CRATE_CHAR        '$'
#define CRATE_SOLVED_CHAR '*'
#define PAYLOAD_CHAR      '.'
#define MARIO_CHAR        '@'

Game::Game(std::string fmt)
    : m_playerDirection(DirectionDown)
{
    construct(fmt);
}

Game::Game(std::ifstream &file)
    : m_playerDirection(DirectionDown)
{
    std::string fmt;
    std::string line;

    if (!file)
        exit(1);
    while (getline(file, line))
        fmt += line + "\n";
    construct(fmt);
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
    std::vector<Position> cratePosSaved = m_cratePos;
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
        if (!tryMoveCrate(*std::find(
                m_cratePos.begin(), m_cratePos.end(), m_playerPos),
                direction))
        {
            m_playerPos = saved;
            return;
        }
    m_history.push(std::make_pair(saved, cratePosSaved));
}

void Game::undo()
{
    if (m_history.size() < 1)
        return;
    m_playerPos = m_history.top().first;
    m_cratePos = m_history.top().second;
    m_history.pop();
}

void Game::reset()
{
    while (m_history.size() > 0)
        undo();
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

Game::Direction Game::getPlayerDirection() const
{
    return m_playerDirection;
}

void Game::construct(std::string fmt)
{
    size_t p;

    m_height = std::count(fmt.begin(), fmt.end(), '\n');
    m_grid = new Cell*[m_height];
    findWidth(fmt);
    for (int i = 0; (p = fmt.find("\n")) != std::string::npos; i++)
    {
        std::string token = fmt.substr(0, p);
        m_grid[i] = new Cell[m_width];
        for (size_t j = 0; j < m_width; j++)
            m_grid[i][j] = CellEmpty;
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
                case CRATE_SOLVED_CHAR:
                    m_grid[i][j] = CellEmpty;
                    m_cratePos.push_back(makePos(i, j));
                    m_payloadPos.push_back(makePos(i, j));
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
                    std::cerr << "Cannot parse map" << std::endl;
                    exit(1);
            }
        }
        fmt.erase(0, p + 1);
    }
}

void Game::findWidth(std::string fmt)
{
    size_t p;
    m_width = 0;

    for (int i = 0; (p = fmt.find("\n")) != std::string::npos; i++)
    {
        m_width = std::max(m_width, p);
        fmt.erase(0, p + 1);
    }
}

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
    if (!validPosition(clone) || get(clone) == CellCrate
            || get(clone) == CellCrateSolved || get(clone) == CellWall)
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
