#include "mainloop.hpp"
#include "SDL_mixer_functions.hpp"

MainLoop::MainLoop() { 
    game_state = STARTING_SCREEN;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    frame = 0;

    title = new Textbox(WHITE_COLOR, "KITTY'S ADVENTURE", {SCREEN_WIDTH / 2 - 200, 50, 400, 100}, 100, "res/fonts/Pacifico.ttf");
    you_won = new Textbox(WHITE_COLOR, "Congratulations!!! You won", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");
    you_lost = new Textbox(WHITE_COLOR, "You lost bro", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");

    play_button = new Button("Play", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 50, 200, 100});
    resume_button = new Button("Resume", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 50, 200, 100});
    
    quit_button = new Button("Quit", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 30, 200, 100});
    restart_button = new Button("Replay", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 130, 200, 100});

    level1_button = new Button("Level 1", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 130, 200, 100});
    level2_button = new Button("Level 2", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 30, 200, 100});

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
                    };
                }
                break;
            case CHOOSING_LEVEL:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(level1_button->is_pressed(x, y)) {
                        map = Map(1);
                        update_game_state(PLAYING_THE_GAME);                        
                        Mix_PlayChannel(-1, button_select_sound, 0);
                        Mix_PlayMusic(background_music, -1);
                    } else if(level2_button->is_pressed(x, y)) {
                        map = Map(2);
                        update_game_state(PLAYING_THE_GAME);
                        Mix_PlayChannel(-1, button_select_sound, 0);
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
                        Mix_PlayChannel(-1, button_select_sound, 0);
                        update_game_state(QUITTING_THE_GAME);
                    }
                    if(restart_button->is_pressed(x, y)) {
                        Mix_PlayChannel(-1, button_select_sound, 0);
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
                        Mix_PlayChannel(-1, button_select_sound, 0);
                        update_game_state(PLAYING_THE_GAME);
                    }
                }
                break;
            case WIN:
                Mix_HaltMusic();
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) {
                        Mix_PlayChannel(-1, button_select_sound, 0);
                        update_game_state(QUITTING_THE_GAME);
                    }
                    if(restart_button->is_pressed(x, y)) {
                        Mix_PlayChannel(-1, button_select_sound, 0);
                        update_game_state(RESTARTING);
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