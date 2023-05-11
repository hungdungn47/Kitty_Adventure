#pragma once
#include "constants.hpp"
#include "utils.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "player.hpp"

class Background {
private:
    LTexture background_texture;
    LTexture wallpaper_texture;
    LTexture menu_background_texture;
    SDL_Rect background_rect;
    SDL_Rect menu_background_rect;
public:
    Background();
    ~Background();
    void load_texture();
    void render();
    void render_menu();
    void render_wallpaper();
};