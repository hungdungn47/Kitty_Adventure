#include "mainloop.hpp"
#include "SDL_mixer_functions.hpp"

MainLoop::MainLoop() { 
    level1 = Map(1);
    level2 = Map(2);
    game_state = STARTING_SCREEN;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    frame = 0;

    title = new Textbox(WHITE_COLOR, "KITTY'S ADVENTURE", {SCREEN_WIDTH / 2 - 200, 50, 400, 100}, 100, "res/fonts/Pacifico.ttf");
    you_won = new Textbox(WHITE_COLOR, "Congratulations!!! You won", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");
    you_lost = new Textbox(WHITE_COLOR, "Oops!!! You lost", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");
    choose_sound_track = new Textbox(WHITE_COLOR, "Choose sound track", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");

    play_button = new Button("Play", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 130, 200, 100});
    option_button = new Button("Option", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 30, 200, 100});

    resume_button = new Button("Resume", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 130, 200, 100});
    menu_button = new Button("Menu", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 30, 200, 100});
    
    quit_button = new Button("Quit", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 30, 200, 100});
    restart_button = new Button("Menu", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 130, 200, 100});

    level1_button = new Button("Level 1", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 130, 200, 100});
    level2_button = new Button("Level 2", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 30, 200, 100});

    giai_dieu_to_quoc_button = new Button("Giai dieu To quoc", {SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 150, 400, 100});
    hanh_khuc_ngay_va_dem_button = new Button("Hanh khuc ngay va dem", {SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2, 400, 100});
    dat_nuoc_tron_niem_vui_button = new Button("Dat nuoc tron niem vui", {SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 150, 400, 100});

    if(!LoadMusic()) {
        std::cout << "Failed to load music" << std::endl;
    }
}

void MainLoop::render_game() {
    bg.render();
    switch (game_state)
    {
        case STARTING_SCREEN:
            bg.render_menu();
            play_button->render();
            option_button->render();
            title->render_text_box();
            break;
        case CHOOSING_LEVEL:
            title->render_text_box();
            bg.render_menu();
            level1_button->render();
            level2_button->render();
            break;
        case PLAYING_THE_GAME:
            map.render(camera);
            cat.render(camera, frame);
            break;
        case PAUSING:
            map.render(camera);
            cat.render(camera, frame);
            bg.render_menu();
            resume_button->render();
            menu_button->render();
            break;
        case GAME_OVER:
            you_lost->render_text_box();
            bg.render_menu();
            quit_button->render();
            restart_button->render();
            break;
        case WIN:
            you_won->render_text_box();
            bg.render_menu();
            quit_button->render();
            restart_button->render();
            break;
        case CHOOSING_SOUND_TRACK:
            choose_sound_track->render_text_box();
            giai_dieu_to_quoc_button->render();
            hanh_khuc_ngay_va_dem_button->render();
            dat_nuoc_tron_niem_vui_button->render();
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
                }
                break;
            case CHOOSING_LEVEL:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
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
                cat.set_velocity(10);
                cat.handleEvent(e);
                if(e.type == SDL_KEYDOWN) {
                    if(e.key.keysym.sym == SDLK_ESCAPE) update_game_state(PAUSING);
                }
                break;
            case GAME_OVER:
                Mix_HaltMusic();
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) {
                        update_game_state(QUITTING_THE_GAME);
                    }
                    if(restart_button->is_pressed(x, y)) {
                        update_game_state(RESTARTING);
                    }
                }
                break;
            case PAUSING:
                Mix_PauseMusic();
                cat.set_velocity(0);
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(resume_button->is_pressed(x, y)) {
                        update_game_state(PLAYING_THE_GAME);
                    }
                    if(menu_button->is_pressed(x, y)) {
                        update_game_state(RESTARTING);
                    }
                }
                break;
            case WIN:
                Mix_HaltMusic();
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) {
                        update_game_state(QUITTING_THE_GAME);
                    }
                    if(restart_button->is_pressed(x, y)) {
                        update_game_state(RESTARTING);
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
                }
                break;
            default:
                break;
        }
    }
    if(game_state == PLAYING_THE_GAME) {
        cat.move(map.get_tile_set(), map);
        cat.setCamera(camera, map);
        if(cat.is_game_over(camera)) update_game_state(GAME_OVER);
        if(cat.win(map)) update_game_state(WIN);
    }
    if(game_state == RESTARTING) {
        std::cout << "Restarting" << std::endl;
        camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        cat.init();
        update_game_state(STARTING_SCREEN);
    }
}

GameState MainLoop::get_game_state() {
    return game_state;
}

void MainLoop::update_game_state(GameState new_state) {
    game_state = new_state;
}