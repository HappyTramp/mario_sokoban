#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"

class Graphics
{
public:
    Graphics(Game &game, std::string title, int width, int height);
    ~Graphics();

    void update();
    bool isRunning() const;

private:
    bool         m_running;
    Game         &m_game;
    std::string  m_title;
    int          m_width;
    int          m_height;
    SDL_Renderer *m_renderer;
    SDL_Window   *m_window;
    SDL_Texture  *m_wallTex;
    SDL_Texture  *m_crateTex;
    SDL_Texture  *m_crateSolvedTex;
    SDL_Texture  *m_payloadTex;
    SDL_Texture  *m_playerTex;

    void        drawGame();
    void        drawCell(Game::Cell cell, int y, int x);
    void        drawPlayer();
    void        handleEvent();
    SDL_Texture *loadImage(std::string filename);
    void        putImage(SDL_Texture *tex, SDL_Rect *destRect);
    void        error() const;
};

#endif
