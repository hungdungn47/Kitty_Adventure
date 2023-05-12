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


int main(int argc, char** argv) {
    //Init SDL window, renderer, ...
    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    
    MainLoop game_loop;

    while(game_loop.get_game_state() != QUITTING_THE_GAME) {

        game_loop.handle_event(e);

        SDL_RenderClear(gRenderer);

        game_loop.render_game();

        SDL_RenderPresent(gRenderer);
    }

    quitSDL(gWindow, gRenderer);
    return 0;
}

