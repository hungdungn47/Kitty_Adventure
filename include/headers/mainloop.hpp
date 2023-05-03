#pragma once
#include "utils.hpp"
#include "SDL_utils.hpp"
#include "constants.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "menu.hpp"
#include "background.hpp"

class MainLoop {
private:
    Button *play_button, *pause_button, *quit_button, *resume_button, *restart_button;
    Textbox *title, *you_won, *you_lost;
    Background bg;
    Player cat;
    Map map;
    SDL_Rect camera;
    int frame;

    GameState game_state;
public:
    MainLoop();
    void render_game();
    void handle_event(SDL_Event e);
    GameState get_game_state();
    void update_game_state(GameState new_state);
}; 