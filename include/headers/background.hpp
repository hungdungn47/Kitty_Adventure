#pragma once
#include "constants.hpp"
#include "utils.hpp"
#include "SDL.h"
#include "SDL_image.h"

class Background {
private:
    LTexture background_texture;
public:
    Background();
    ~Background();
    void load_texture();
    void render();
};