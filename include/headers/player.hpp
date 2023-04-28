#pragma once
#include "utils.hpp"
#include "constants.hpp"
#include "Tile.hpp"

class Player {
public:
    enum State {
        IDLE,
        RUN,
        JUMP
    };
    enum Orientation {
        NORMAL,
        FLIPPED
    };
    //Number of frames of the animation
    static const int IDLE_ANIMATION_FRAMES = 4;
    static const int RUNNING_ANIMATION_FRAMES = 8;
    
    //Sprite's dimension (to cut from sprite sheet)
    static const int SPRITE_WIDTH = 13;
    static const int SPRITE_HEIGHT = 13;
    
    //Rendering dimension
    static const int PLAYER_WIDTH = 75;
    static const int PLAYER_HEIGHT = 75;
    
    //Running velocity
    static const int PLAYER_VEL = 10;

    Player();
    ~Player();

    void handleEvent(SDL_Event& e);

    void move(vector<Tile*> tiles, Map level);

    void setCamera(SDL_Rect& camera, Map level);

    void render(SDL_Rect& camera, int& frame);

    void set_velocity(float _mVelX);

    bool is_game_over(SDL_Rect camera);

    bool win(Map level);

    int getPosX();
    int getPosY();

private:
    //Hit box
    SDL_Rect mBox;

    //Source rectangle for creating animation
    SDL_Rect idle_sprite_clips[IDLE_ANIMATION_FRAMES];
    SDL_Rect running_sprite_clips[RUNNING_ANIMATION_FRAMES];

    SDL_Rect current_clip;

    //flipping enum
    SDL_RendererFlip player_flip;

    State player_state;
    Orientation player_orientation;

    float mVelX, mVelY;

    float acceleration = 2;

    LTexture mTexture;
};
