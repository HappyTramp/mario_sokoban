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
