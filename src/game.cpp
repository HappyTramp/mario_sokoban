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
                    m_grid[i][j] = CellCrate;
                    break;
                case PAYLOAD_CHAR:
                    m_grid[i][j] = CellPayload;
                    break;
                case MARIO_CHAR:
                    m_grid[i][j] = CellEmpty;
                    m_playerPos.y = i;
                    m_playerPos.x = j;
                    break;
                default:
                    m_grid[i][j] = CellEmpty;
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

void Game::move(Direction direction)
{
    m_playerDirection = direction;
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
}

Game::Cell Game::get(int y, int x) const
{
    return m_grid[y][x];
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
