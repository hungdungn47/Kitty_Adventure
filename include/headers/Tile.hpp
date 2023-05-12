#pragma once
#include "utils.hpp"
#include "constants.hpp"

//Tile constants
const int TILE_CLIP_WIDTH = 40;
const int TILE_CLIP_HEIGHT = 40;
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILE_SPRITES = 49;

//The tile
class Tile
{
    public:
        //Initializes position and type
        Tile( int x, int y, int tileType );
        ~Tile();

        //Shows the tile
        void render( SDL_Rect& camera, SDL_Rect gTileClips[] );

        //Get the tile type
        int getType();

        //Get the collision box
        SDL_Rect getBox();

    private:
        //The attributes of the tile
        SDL_Rect mBox;

        LTexture gTileTexture;

        //The tile type
        int mType;
};

bool touchesWall( SDL_Rect box, vector<Tile*> tiles);

class Map {
    // Map is a set of tiles
private:
    vector<Tile*> tile_set;
    SDL_Rect tile_clips[TOTAL_TILE_SPRITES];
    int level;
    Fish fish;
public:
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    Map() {}
    Map(int _level);
    vector<Tile*> get_tile_set() {return tile_set;};
    bool set_tiles(std::string file_path);
    void render(SDL_Rect& camera);
};