#include "mainloop.hpp"
#include "SDL_mixer_functions.hpp"

MainLoop::MainLoop() { 
    map = Map(1);
    game_state = STARTING_SCREEN;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    frame = 0;

    title = new Textbox(WHITE_COLOR, "KITTY'S ADVENTURE", {SCREEN_WIDTH / 2 - 200, 50, 400, 100}, 100, "res/fonts/Pacifico.ttf");
    you_won = new Textbox(WHITE_COLOR, "Congratulations!!! You won", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");
    you_lost = new Textbox(WHITE_COLOR, "You lost bro", {SCREEN_WIDTH / 2 - 250, 50, 500, 100}, 100, "res/fonts/Pacifico.ttf");

    play_button = new Button("Play", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 50, 200, 100});
    quit_button = new Button("Quit", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 50, 200, 100});
    resume_button = new Button("Resume", {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 50, 200, 100});

    if(!LoadMusic()) {
        std::cout << "Failed to load music" << std::endl;
    } else {
        Mix_PlayMusic(background_music, -1);
        std::cout << "Music is playing" << std::endl;
    }
}

void MainLoop::render_game() {
    bg.render();
    switch (game_state)
    {
        case STARTING_SCREEN:
            play_button->render();
            title->render_text_box();
            break;
        case PLAYING_THE_GAME:
            map.render(camera);
            cat.render(camera, frame);
            break;
        case PAUSING:
            map.render(camera);
            cat.render(camera, frame);
            resume_button->render();
            break;
        case GAME_OVER:
            you_lost->render_text_box();
            quit_button->render();
            break;
        case WIN:
            you_won->render_text_box();
            quit_button->render();
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
                        update_game_state(PLAYING_THE_GAME);
                        Mix_PlayChannel(-1, button_select_sound, 0);
                    };
                }
                break;
            case PLAYING_THE_GAME:
                cat.set_velocity(10);
                cat.handleEvent(e);
                if(e.type == SDL_KEYDOWN) {
                    if(e.key.keysym.sym == SDLK_ESCAPE) update_game_state(PAUSING);
                }
                break;
            case GAME_OVER:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) update_game_state(QUITTING_THE_GAME);
                }
                break;
            case PAUSING:
                cat.set_velocity(0);
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(resume_button->is_pressed(x, y)) update_game_state(PLAYING_THE_GAME);
                }
                break;
            case WIN:
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(quit_button->is_pressed(x, y)) update_game_state(QUITTING_THE_GAME);
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
}

GameState MainLoop::get_game_state() {
    return game_state;
}

void MainLoop::update_game_state(GameState new_state) {
    game_state = new_state;
}