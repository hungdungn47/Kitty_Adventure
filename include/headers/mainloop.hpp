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
    Button *play_button, *pause_button, *quit_button, *resume_button, *restart_button, *quit_button_0, *retry_button,
         *menu_button, *level1_button, *level2_button, *level3_button, *option_button, 
         *giai_dieu_to_quoc_button, *hanh_khuc_ngay_va_dem_button, *dat_nuoc_tron_niem_vui_button, *no_music_button;
    Textbox *title, *you_won, *you_lost, *choose_sound_track;
    Background bg;
    Player cat;
    Map *map, *level1, *level2, *level3;
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