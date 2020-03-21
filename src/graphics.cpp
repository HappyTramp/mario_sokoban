#include "graphics.hpp"

#define UPDATE_DELAY 3

Graphics::Graphics(Game &game, std::string title, int width, int height):
    m_running(true), m_game(game), m_title(title), m_width(width), m_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error();
    if ((m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, 0)) == NULL)
        error();
    if ((m_renderer = SDL_CreateRenderer(m_window, -1, 0)) == NULL)
        error();
    m_wallTex = loadImage("sprite/wall.jpg");
    m_crateTex = loadImage("sprite/crate.jpg");
    m_crateSolvedTex = loadImage("sprite/crate_solved.jpg");
    m_payloadTex = loadImage("sprite/payload.png");
    m_playerUpTex = loadImage("sprite/mario_up.gif");
    m_playerDownTex = loadImage("sprite/mario_down.gif");
    m_playerLeftTex = loadImage("sprite/mario_left.gif");
    m_playerRightTex = loadImage("sprite/mario_right.gif");
}

Graphics::~Graphics()
{
    SDL_DestroyTexture(m_playerRightTex);
    SDL_DestroyTexture(m_playerLeftTex);
    SDL_DestroyTexture(m_playerDownTex);
    SDL_DestroyTexture(m_playerUpTex);
    SDL_DestroyTexture(m_payloadTex);
    SDL_DestroyTexture(m_crateSolvedTex);
    SDL_DestroyTexture(m_crateTex);
    SDL_DestroyTexture(m_wallTex);
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
    drawPlayer();
}

void Graphics::drawCell(Game::Cell cell, int y, int x)
{
    SDL_Rect r;

    r.x = x * (m_width / m_game.getWidth());
    r.y = y * (m_height / m_game.getHeight());
    r.w = m_width / m_game.getWidth();
    r.h = m_height / m_game.getHeight();

    switch (cell)
    {
        case Game::CellEmpty:
            SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(m_renderer, &r);
            break;
        case Game::CellWall:
            putImage(m_wallTex, &r);
            break;
        case Game::CellCrate:
            putImage(m_crateTex, &r);
            break;
        case Game::CellCrateSolved:
            putImage(m_crateSolvedTex, &r);
            break;
        case Game::CellPayload:
            SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(m_renderer, &r);
            putImage(m_payloadTex, &r);
            break;
        default:
            break;
            // SDL_SetRenderDrawColor(m_renderer, 150, 150, 150, 255);
    }
}

void Graphics::drawPlayer()
{
    SDL_Rect r;
    Game::Position pos = m_game.getPlayer();

    r.x = pos.x * (m_width / m_game.getWidth());
    r.y = pos.y * (m_height / m_game.getHeight());
    r.w = m_width / m_game.getWidth();
    r.h = m_height / m_game.getHeight();
    switch (m_game.getPlayerDirection())
    {
        case Game::DirectionUp:
            putImage(m_playerUpTex, &r);
            break;
        case Game::DirectionDown:
            putImage(m_playerDownTex, &r);
            break;
        case Game::DirectionLeft:
            putImage(m_playerLeftTex, &r);
            break;
        case Game::DirectionRight:
            putImage(m_playerRightTex, &r);
            break;
    }
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
                    case SDLK_UP:
                        m_game.move(Game::DirectionUp);
                        break;
                    case SDLK_DOWN:
                        m_game.move(Game::DirectionDown);
                        break;
                    case SDLK_LEFT:
                        m_game.move(Game::DirectionLeft);
                        break;
                    case SDLK_RIGHT:
                        m_game.move(Game::DirectionRight);
                        break;
                }
                if (m_game.won())
                    m_running = false;
        }
    }
}

SDL_Texture *Graphics::loadImage(std::string filename)
{
    SDL_Surface *tmpSurface;
    SDL_Texture *tex;

    tmpSurface = IMG_Load(filename.c_str());
    if (tmpSurface == NULL)
        error();
    tex = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);
    if (tex == NULL)
        error();
    SDL_FreeSurface(tmpSurface);
    return tex;
}

void Graphics::putImage(SDL_Texture *tex, SDL_Rect *destRect)
{
    SDL_Rect srcRect;

    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(tex, NULL, NULL, &srcRect.w, &srcRect.h);
    SDL_RenderCopy(m_renderer, tex, &srcRect, destRect);
}

void Graphics::error() const
{
    std::cerr << SDL_GetError() << std::endl;
    exit(1);
}
