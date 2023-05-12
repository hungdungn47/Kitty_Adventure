#include "background.hpp"
#include <iostream>

Background::Background() {
    load_texture();
    background_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Background::~Background() {
    background_texture.free();
}

void Background::load_texture() {
    background_texture.loadFromFile(gRenderer, "res/images/background_0.png");
    wallpaper_texture.loadFromFile(gRenderer, "res/images/Background.png");
}

void Background::render() {
    background_texture.render(gRenderer, 0, 0, NULL, &background_rect);
}

void Background::render_wallpaper() {
    wallpaper_texture.render(gRenderer, 0, 0, NULL, &background_rect);
}