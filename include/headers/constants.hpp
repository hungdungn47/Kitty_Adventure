#pragma once

#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
const SDL_Color DEEP_GREEN_COLOR = {0, 26, 0};

enum GameState {
    STARTING_SCREEN,
    INSTRUCTION,
    PLAYING_THE_GAME,
    QUITTING_THE_GAME,
    WIN,
    GAME_OVER,
    PAUSING,
    RESTARTING,
    CHOOSING_LEVEL,
    CHOOSING_SOUND_TRACK,
    RETRYING
};

const char WINDOW_TITLE[] = "Kitty's Adventure";

const char southern_font[] = "res/fonts/Southern.ttf";
const char pacifico_font[] = "res/fonts/Pacifico.ttf";
const char josefin_font[] = "res/fonts/josefin-sans/JosefinSans-Regular.ttf";
const char ostrich_font[] = "res/fonts/ostrich-sans/ostrich-regular.ttf";
const char caviar_dream_font[] = "res/fonts/Caviar-Dreams/CaviarDreams.ttf";
const char arcade_classic_font[] = "res/fonts/arcadeclassic/ARCADECLASSIC.TTF";
const char back_to_1982_font[] = "res/fonts/back-to-1982/BACKTO1982.TTF";
const char karmatic_arcade_font[] = "res/fonts/karmatic-arcade/ka1.ttf";