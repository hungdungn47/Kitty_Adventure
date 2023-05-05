#pragma once

#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

enum GameState {
    STARTING_SCREEN,
    PLAYING_THE_GAME,
    QUITTING_THE_GAME,
    WIN,
    GAME_OVER,
    PAUSING,
    RESTARTING,
    CHOOSING_LEVEL
};

const static char WINDOW_TITLE[] = "Geometry dumb";