#include "graphics.hpp"

#define UPDATE_DELAY 3

Graphics::Graphics(Game &game, std::string title, int width, int height):
    m_running(true), m_game(game), m_title(title), m_width(width), m_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error();
    if ((m_window = SDL_CreateWindow(m_title.c_str(), 0, 0, m_width, m_height, 0)) == NULL)
        error();
    if ((m_renderer = SDL_CreateRenderer(m_window, -1, 0)) == NULL)
        error();
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Graphics::isRunning() const
{
    return m_running;
}

void Graphics::update()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    handleEvent();
    drawGame();
    SDL_RenderPresent(m_renderer);
    SDL_Delay(UPDATE_DELAY);
}

void Graphics::drawGame()
{
    for (size_t i = 0; i < m_game.getHeight(); i++)
        for (size_t j = 0; j < m_game.getWidth(); j++)
            drawCell(m_game.get(i, j), i, j);
}

void Graphics::drawCell(Game::Cell cell, int y, int x)
{
    SDL_Rect r;

    switch (cell)
    {
        case Game::CellWall:
            SDL_SetRenderDrawColor(m_renderer, 40, 40, 100, 255);
            break;
        case Game::CellEmpty:
            SDL_SetRenderDrawColor(m_renderer, 10, 10, 10, 255);
            break;
        default:
            SDL_SetRenderDrawColor(m_renderer, 150, 150, 150, 255);
    }
    r.x = x * (m_width / m_game.getWidth());
    r.y = y * (m_height / m_game.getHeight());
    r.w = m_width / m_game.getWidth();
    r.h = m_height / m_game.getHeight();
    SDL_RenderFillRect(m_renderer, &r);
}

void Graphics::handleEvent()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_UP:
                        break;
                }
        }
    }
}

void Graphics::error() const
{
    std::cerr << SDL_GetError() << std::endl;
    exit(1);
}
