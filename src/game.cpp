#include "game.hpp"

#define EMPTY_CHAR ' '
#define WALL_CHAR '#'
#define CRATE_CHAR 'U'
#define PAYLOAD_CHAR '*'
#define MARIO_CHAR 'm'

#include <iostream>
Game::Game(std::string fmt)
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

Game::Cell Game::get(int y, int x)
{
    return m_grid[y][x];
}

size_t Game::getHeight()
{
    return m_height;
}

size_t Game::getWidth()
{
    return m_width;
}
