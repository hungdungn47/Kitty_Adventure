#include "background.hpp"
#include <iostream>

Background::Background() {
    load_texture();
    background_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    instruction_rect = {100, 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200};
}

Background::~Background() {
    background_texture.free();
}

void Background::load_texture() {
    background_texture.loadFromFile(gRenderer, "res/images/background_0.png");
    wallpaper_texture.loadFromFile(gRenderer, "res/images/Background.png");
    instruction_texture.loadFromFile(gRenderer, "res/images/instruction.png");
}

void Background::render() {
    background_texture.render(gRenderer, 0, 0, NULL, &background_rect);
}

void Background::render_wallpaper() {
    wallpaper_texture.render(gRenderer, 0, 0, NULL, &background_rect);
}

void Background::render_instruction() {
    instruction_texture.render(gRenderer, SCREEN_WIDTH / 2 - instruction_texture.getWidth() / 2, SCREEN_HEIGHT / 2 - instruction_texture.getHeight() / 2);
}