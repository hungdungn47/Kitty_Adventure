#include "background.hpp"
#include <iostream>

Background::Background() {
    load_texture();
}

Background::~Background() {
    background_texture.free();
}

void Background::load_texture() {
    background_texture.loadFromFile(gRenderer, "res/images/background.png");
}

void Background::render() {
    SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    background_texture.render(gRenderer, 0, 0, NULL, &renderQuad);
}