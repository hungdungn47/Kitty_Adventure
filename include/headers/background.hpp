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
    LTexture instruction_texture;
    SDL_Rect background_rect, instruction_rect;
public:
    Background();
    ~Background();
    void load_texture();
    void render();
    void render_wallpaper();
    void render_instruction();
};