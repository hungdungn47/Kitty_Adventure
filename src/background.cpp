#include "background.hpp"
#include <iostream>

Background::Background() {
    load_texture();
    background_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int w = menu_background_texture.getWidth();
    int h = menu_background_texture.getHeight();
    menu_background_rect = {SCREEN_WIDTH / 2 - w, SCREEN_HEIGHT / 2 - h, w * 2, h * 2};
}

Background::~Background() {
    background_texture.free();
}

void Background::load_texture() {
    background_texture.loadFromFile(gRenderer, "res/images/background.png");
    menu_background_texture.loadFromFile(gRenderer, "res/images/menu_background.png");
}

void Background::render() {
    background_texture.render(gRenderer, 0, 0, NULL, &background_rect);
}

void Background::render_menu() {
    menu_background_texture.render(gRenderer, menu_background_rect.x, menu_background_rect.y, NULL, &menu_background_rect);
}