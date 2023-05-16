#include "mainloop.hpp"
#include "SDL_mixer_functions.hpp"

MainLoop::MainLoop() { 
    level1 = new Map(1);
    level2 = new Map(2);
    level3 = new Map(3);
    game_state = STARTING_SCREEN;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    frame = 0;

    // Textbox(SDL_Color _text_color, std::string _text_string, int x, int y, int font_size, std::string _font_path)
    title = new Textbox(DEEP_GREEN_COLOR, "KITTY'S  ADVENTURE", 0, 70, 70, karmatic_arcade_font);
    you_won = new Textbox(BLACK_COLOR, "Congratulations!!! You won", 0, 70, 50, karmatic_arcade_font);
    you_lost = new Textbox(BLACK_COLOR, "Oops!!! You lost", 0, 70, 50, karmatic_arcade_font);
    choose_sound_track = new Textbox(BLACK_COLOR, "Choose background music", 0, 70, 50, karmatic_arcade_font);

    play_button = new Button("Play   ", 700, 250);
    option_button = new Button("Option", 700, 400);
    instruction_button = new Button("Instruction", 700, 550);
    quit_button_0 = new Button("Quit   ", 700, 700);
    back_button = new Button("Back", 50, 50);

    resume_button = new Button("Resume", 450, 400);
    menu_button = new Button(" Menu ", 330, 550);
    retry_button_0 = new Button("Retry", 600,  550);
    
    retry_button = new Button("Retry", 700, 300);
    restart_button = new Button("Menu ", 700, 450);
    quit_button = new Button("Quit ", 700, 600);

    level1_button = new Button("Level 1", 700, 300);
    level2_button = new Button("Level 2", 700, 450);
    level3_button = new Button("Level 3", 700, 600);

    giai_dieu_to_quoc_button = new Button("Giai dieu To quoc", 100, 200);
    hanh_khuc_ngay_va_dem_button = new Button("Hanh khuc ngay va dem", 100, 350);
    dat_nuoc_tron_niem_vui_button = new Button("Dat nuoc tron niem vui", 100, 500);
    no_music_button = new Button("Default background music", 100, 650);

    if(!LoadMusic()) {
        std::cout << "Failed to load music" << std::endl;
    }
    background_music = wii_music;
    Mix_PlayMusic(wii_music, -1);
}

void MainLoop::render_game() {
    bg.render();
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    switch (game_state)
    {
        case STARTING_SCREEN:
            bg.render_wallpaper();
            play_button->render(mouseX, mouseY);
            option_button->render(mouseX, mouseY);
            instruction_button->render(mouseX, mouseY);
            quit_button_0->render(mouseX, mouseY);
            title->render_center();
            break;
        case INSTRUCTION:
            bg.render_instruction();
            back_button->render(mouseX, mouseY);
            break;
        case CHOOSING_LEVEL:
            bg.render_wallpaper();
            title->render_center();
            level1_button->render(mouseX, mouseY);
            level2_button->render(mouseX, mouseY);
            level3_button->render(mouseX, mouseY);
            break;
        case PLAYING_THE_GAME:
            map->render(camera);
            cat.render(camera, frame);
            break;
        case PAUSING:
            map->render(camera);
            cat.render(camera, frame);
            resume_button->render(mouseX, mouseY);
            menu_button->render(mouseX, mouseY);
            retry_button_0->render(mouseX, mouseY);
            break;
        case GAME_OVER:
            bg.render_wallpaper();
            you_lost->render_center();
            quit_button->render(mouseX, mouseY);
            restart_button->render(mouseX, mouseY);
            retry_button->render(mouseX, mouseY);
            break;
        case WIN:
            bg.render_wallpaper();
            you_won->render_center();
            quit_button->render(mouseX, mouseY);
            restart_button->render(mouseX, mouseY);
            retry_button->render(mouseX, mouseY);
            break;
        case CHOOSING_SOUND_TRACK:
            choose_sound_track->render_center();
            giai_dieu_to_quoc_button->render(mouseX, mouseY);
            hanh_khuc_ngay_va_dem_button->render(mouseX, mouseY);
            dat_nuoc_tron_niem_vui_button->render(mouseX, mouseY);
            no_music_button->render(mouseX, mouseY);
            break;
        default:
            break;
    }
}

void MainLoop::handle_event(SDL_Event e) {
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            update_game_state(QUITTING_THE_GAME);
        }
        switch(game_state) {
            case STARTING_SCREEN:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(play_button->is_pressed(x, y)) {
                        update_game_state(CHOOSING_LEVEL);
                    }
                    if(option_button->is_pressed(x, y)) {
                        update_game_state(CHOOSING_SOUND_TRACK);
                    }
                    if(instruction_button->is_pressed(x, y)) {
                        update_game_state(INSTRUCTION);
                    }
                    if(quit_button_0->is_pressed(x, y) ) {
                        update_game_state(QUITTING_THE_GAME);
                    }
                }
                break;
            case INSTRUCTION: 
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(back_button->is_pressed(x, y)) {
                        update_game_state(STARTING_SCREEN);
                    }
                }
            case CHOOSING_LEVEL:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    Mix_HaltMusic();
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(level1_button->is_pressed(x, y)) {
                        map = level1;
                        update_game_state(PLAYING_THE_GAME);              
                        Mix_PlayMusic(background_music, -1);
                    } else if(level2_button->is_pressed(x, y)) {
                        map = level2;
                        update_game_state(PLAYING_THE_GAME);
                        Mix_PlayMusic(background_music, -1);
                    } else if(level3_button->is_pressed(x, y)) {
                        map = level3;
                        update_game_state(PLAYING_THE_GAME);
                        Mix_PlayMusic(background_music, -1);
                    }
                }
                break;
            case PLAYING_THE_GAME:
                //If the music is paused
                if( Mix_PausedMusic() == 1 )
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                cat.handleEvent(e);
                if(e.type == SDL_KEYDOWN) {
                    if(e.key.keysym.sym == SDLK_ESCAPE) update_game_state(PAUSING);
                }
                break;
            case GAME_OVER:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) {
                        update_game_state(QUITTING_THE_GAME);
                    }
                    if(restart_button->is_pressed(x, y)) {
                        update_game_state(RESTARTING);
                    }
                    if(retry_button->is_pressed(x, y)) {
                        update_game_state(RETRYING);
                    }
                }
                break;
            case PAUSING:
                Mix_PauseMusic();
                cat.stop_moving();
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(resume_button->is_pressed(x, y)) {
                        cat.start_moving();
                        update_game_state(PLAYING_THE_GAME);
                    }
                    if(menu_button->is_pressed(x, y)) {
                        update_game_state(RESTARTING);
                    }
                    if(retry_button_0->is_pressed(x, y)) {
                        update_game_state(RETRYING);
                    }
                }
                break;
            case WIN:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) {
                        update_game_state(QUITTING_THE_GAME);
                    }
                    if(restart_button->is_pressed(x, y)) {
                        update_game_state(RESTARTING);
                    }
                    if(retry_button->is_pressed(x, y)) {
                        update_game_state(RETRYING);
                    }
                }
                break;
            case CHOOSING_SOUND_TRACK:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(giai_dieu_to_quoc_button->is_pressed(x, y)) {
                        background_music = giai_dieu_to_quoc;
                        update_game_state(STARTING_SCREEN);
                    }
                    if(hanh_khuc_ngay_va_dem_button->is_pressed(x, y)) {
                        background_music = hanh_khuc_ngay_va_dem;
                        update_game_state(STARTING_SCREEN);
                    }
                    if(dat_nuoc_tron_niem_vui_button->is_pressed(x, y)) {
                        background_music = dat_nuoc_tron_niem_vui;
                        update_game_state(STARTING_SCREEN);
                    }
                    if(no_music_button->is_pressed(x, y)) {
                        background_music = wii_music;
                        update_game_state(STARTING_SCREEN);
                    }
                }
                break;
            default:
                break;
        }
    }
    if(game_state == PLAYING_THE_GAME) {
        cat.move(map->get_tile_set(), *map);
        cat.setCamera(camera, *map);
        if(cat.is_game_over(camera)) {
            Mix_HaltMusic();
            Mix_PlayChannel(-1, game_over_sound, 0);
            update_game_state(GAME_OVER);
        }
        if(cat.win(*map)) {
            Mix_HaltMusic();
            Mix_PlayChannel(-1, win_sound, 0);
            update_game_state(WIN);
        }
    }
    if(game_state == RESTARTING) {
        camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        cat.init();
        update_game_state(STARTING_SCREEN);
    }
    if(game_state == RETRYING) {
        camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        cat.init();
        Mix_PlayMusic(background_music, -1);
        update_game_state(PLAYING_THE_GAME);
    }
}

GameState MainLoop::get_game_state() {
    return game_state;
}

void MainLoop::update_game_state(GameState new_state) {
    game_state = new_state;
}