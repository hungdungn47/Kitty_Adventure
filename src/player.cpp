#include "player.hpp"
#include <iostream>
#include <cmath>
Player::Player() {
    init();
}

void Player::init() {
    mVelX = PLAYER_VEL;
    mVelY = 0;

    acceleration = abs(acceleration);

    player_state = IDLE;
    player_orientation = NORMAL;

    //load media
    idle_texture.loadFromFile(gRenderer, "res/images/idle_sprite_sheet.png");
    running_texture.loadFromFile(gRenderer, "res/images/running_sprite_sheet.png");
    
    //Initialize player box
    mBox = {80 * 5, 80 * 4, PLAYER_WIDTH, PLAYER_HEIGHT};
    
    // Set sprite clips
    idle_sprite_clips[0] = {24, 25, 200, 200};
    idle_sprite_clips[1] = {249, 25, 200, 200};
    idle_sprite_clips[2] = {474, 25, 200, 200};
    idle_sprite_clips[3] = {699, 25, 200, 200};

    for(int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        running_sprite_clips[i] = {202 * i, 25, 180, 150};
    }
}

Player::~Player() {
    idle_texture.free();
    running_texture.free();
}

void Player::handleEvent(SDL_Event& e) {
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            // If Space is pressed, reverse the gravity
            case SDLK_SPACE: 
                Mix_PlayChannel(-1, jump_sound, 0);
                acceleration = -acceleration; 
                break;
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

    if(touchesWall(mBox, tiles)) {
        mBox.y -= mVelY;
        mVelY = 0;
    }
}

bool Player::win(Map level) {
    return mBox.x + PLAYER_WIDTH >= level.LEVEL_WIDTH;
}

void Player::setCamera(SDL_Rect& camera, Map level) {

    // If the player is on the screen, the camera move a bit slower than the player
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

    // set current clip based on player state
    if(player_state == IDLE) {
        current_clip = idle_sprite_clips[frame / 5];
        idle_texture.render(gRenderer, mBox.x - camera.x, mBox.y - camera.y, &current_clip, &mBox, 0, NULL, player_flip);
        
        //modify the frame
        frame++;
        if(frame / 5 >= IDLE_ANIMATION_FRAMES) frame = 0;
    } else {
        current_clip = running_sprite_clips[frame / 4];
        running_texture.render(gRenderer, mBox.x - camera.x, mBox.y - camera.y, &current_clip, &mBox, 0, NULL, player_flip);
            
        //modify the frame
        frame++;
        if(frame / 4 >= RUNNING_ANIMATION_FRAMES) frame = 0;
    }
}

void Player::start_moving() {
    mVelX = PLAYER_VEL;
}

void Player::stop_moving() {
    mVelX = 0;
}

bool Player::is_game_over(SDL_Rect camera) {
    return !checkCollision(mBox, camera);
}

int Player::getPosX() { return mBox.x; }
int Player::getPosY() { return mBox.y; }