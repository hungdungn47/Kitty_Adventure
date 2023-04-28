#include "utils.hpp"
#include "SDL_utils.hpp"
#include "constants.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "menu.hpp"
#include "background.hpp"
#include "mainloop.hpp"

using namespace std;

SDL_Event e;

// bool quit = false;

// Button* button = NULL;

// //Tile* level_1[TOTAL_TILES];

// Background* bg = NULL;

// //SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

// Map* level_1 = NULL;

int frame = 0;

// SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

// void update(Player* player) {
//     while(SDL_PollEvent(&e) != 0) {
//         if(e.type == SDL_QUIT) {
//             quit = true;
//         }
//         if(e.type == SDL_MOUSEBUTTONDOWN) {
//             int x, y;
//             SDL_GetMouseState(&x, &y);
//             if(button->is_pressed(x, y)) {
//                 quit = true;
//             }
//         }
//         player->handleEvent(e);
//     }
//     player->move(level_1->get_tile_set());
//     player->setCamera(camera);
// }

// void render(Player* player) {

//     //Render background
//     bg->render();

//     //Render tile map
//     // for(int i = 0; i < TOTAL_TILES; i++) {
//     //     level_1[i] -> render(camera, gTileClips);
//     // }
//     level_1->render(camera);
//     //Render the player
//     player->render(camera, frame);

//     //Render the fcking button
//     button->render();
// }

int main(int argc, char** argv) {
    //Init SDL window, renderer, ...
    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    
    //Set tile clips
    //setTiles(level_1, gTileClips, "res/Tile_map/Mossy_level.csv");

    // level_1 = new Map(1);

    // Player* player = new Player();
    // string position_text = "Player is at " + to_string(player->getPosX());
    // Textbox* player_position = new Textbox(WHITE_COLOR, position_text, {0, 0, 0, 0});
    // bg = new Background();
    // button = new Button("Quit", {SCREEN_WIDTH - 150, SCREEN_HEIGHT - 100, 150, 100});

    // Button* start_button = new Button("Play", {SCREEN_WIDTH/2 - 75, SCREEN_HEIGHT/2 - 50, 150, 100});

    MainLoop game_loop;

    while(game_loop.get_game_state() != QUITTING_THE_GAME) {
        // while(SDL_PollEvent(&e) != 0) {
        //     if(e.type == SDL_QUIT) {
        //         quit = true;
        //     }
        //     if(e.type == SDL_MOUSEBUTTONDOWN) {
        //         int x, y;
        //         SDL_GetMouseState(&x, &y);
        //         if(start_button->is_pressed(x, y)) {
        //             quit = true;
        //         }
        //     }
        // }
        // SDL_RenderClear(gRenderer);
        // bg->render();
        // start_button->render();
        // SDL_RenderPresent(gRenderer);
        game_loop.handle_event(e);

        SDL_RenderClear(gRenderer);

        game_loop.render_game();

        SDL_RenderPresent(gRenderer);
    }

    // quit = false;
    // while(!quit) {
    //     update(player);
    //     position_text = "Player is at " + to_string(player->getPosX());
    //     player_position->update_text(position_text);
    //     cout << player_position->get_text() << endl;

    //     SDL_RenderClear(gRenderer);
    //     render(player);
    //     player_position->render_text_box();
    //     SDL_RenderPresent(gRenderer);
    // }
    quitSDL(gWindow, gRenderer);
    return 0;
}

