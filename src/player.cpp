#include "player.hpp"
#include <iostream>
#include <cmath>
Player::Player() {
    init();
}

void Player::init() {
    mVelX = PLAYER_VEL;
    mVelY = 0;

    player_state = IDLE;
    player_orientation = NORMAL;

    //renderQuad = {mPosX, mPosY, PLAYER_WIDTH, PLAYER_HEIGHT};

    //load media
    mTexture.loadFromFile(gRenderer, "res/Cat Sprite Sheet.png");
    
    //Initialize player box
    mBox = {80 * 5, 80 * 4, PLAYER_WIDTH, PLAYER_HEIGHT};
    
    //Initialize sprite clips
    for(int i = 0; i < IDLE_ANIMATION_FRAMES; i++) {
        idle_sprite_clips[i] = {9 + 32 * i, 19, SPRITE_WIDTH, SPRITE_HEIGHT};
    } 

    for(int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        running_sprite_clips[i] = {7 + 32 * i, 19 + 32 * 4, 16, 13};
    }
}

Player::~Player() {
    mTexture.free();
}

void Player::handleEvent(SDL_Event& e) {
        //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= PLAYER_VEL; break;
            case SDLK_DOWN: mVelY += PLAYER_VEL; break;
            case SDLK_SPACE: acceleration = -acceleration; break;
        }
    }
        //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PLAYER_VEL; break;
            case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
            //case SDLK_SPACE: mVelY += JUMP_VEL; break;
        }
    }
}

void Player::move(vector<Tile*> tiles, Map level) {
    //Increase the velocity
    mVelY += acceleration;

    mBox.x += mVelX;
    if(touchesWall(mBox, tiles)) {
        mBox.x -= mVelX;
    }

    mBox.y += mVelY;

    // if(mBox.y + PLAYER_HEIGHT > level.LEVEL_HEIGHT) {
    //     mBox.y = level.LEVEL_HEIGHT - PLAYER_HEIGHT;
    //     mVelY = 0;
    // }
    if(touchesWall(mBox, tiles)) {
        mBox.y -= mVelY;
        mVelY = 0;
    }
}

bool Player::win(Map level) {
    return mBox.x + PLAYER_WIDTH >= level.LEVEL_WIDTH;
}

void Player::setCamera(SDL_Rect& camera, Map level) {
    //Center the camera over the dot
    // camera.x = ( mBox.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    // camera.y = ( mBox.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
    if(mBox.x + PLAYER_WIDTH > camera.x + SCREEN_WIDTH) camera.x += PLAYER_VEL;
    else camera.x += PLAYER_VEL - 2;
    //Keep the camera in bounds
    if( camera.x < 0 )
    { 
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > level.LEVEL_WIDTH - camera.w )
    {
        camera.x = level.LEVEL_WIDTH - camera.w;
    }
    if( camera.y > level.LEVEL_HEIGHT - camera.h )
    {
        camera.y = level.LEVEL_HEIGHT - camera.h;
    }
}

void Player::render(SDL_Rect& camera, int& frame) {
    //detect player orientation
    if(acceleration > 0) player_orientation = NORMAL;
    else player_orientation = FLIPPED;

    //detect player state
    if(mVelX != 0) {
        player_state = RUN;
        if(mVelX < 0) {
            if(player_orientation == FLIPPED) {
                player_flip = SDL_RendererFlip(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
            } else {
                player_flip = SDL_FLIP_HORIZONTAL;
            }
        } else {
            if(player_orientation == FLIPPED) {
                player_flip = SDL_FLIP_VERTICAL;
            } else {
                player_flip = SDL_FLIP_NONE;
            }
        }
    }
    else {
        player_state = IDLE;
        if(player_orientation == FLIPPED) {
            player_flip = SDL_FLIP_VERTICAL;
        } else {
            player_flip = SDL_FLIP_NONE;
        }
    }

    //set current clip based on player state
    if(player_state == IDLE) {
        current_clip = idle_sprite_clips[frame / 5];
    } else {
        current_clip = running_sprite_clips[frame / 5];
    }

    //render
    mTexture.render(gRenderer, mBox.x - camera.x, mBox.y - camera.y, &current_clip, &mBox, 0, NULL, player_flip);
    
    //modify the frame
    frame++;
    if(frame / 5 >= IDLE_ANIMATION_FRAMES) frame = 0;
}

void Player::set_velocity(float _mVelX) {
    mVelX = _mVelX;
}

bool Player::is_game_over(SDL_Rect camera) {
    return !checkCollision(mBox, camera);
}

int Player::getPosX() { return mBox.x; }
int Player::getPosY() { return mBox.y; }