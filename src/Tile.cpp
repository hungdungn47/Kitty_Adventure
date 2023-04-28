#include "Tile.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Tile::Tile(int x, int y, int tileType) {
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;

    gTileTexture.loadFromFile(gRenderer, "res/Mossy_Tileset/Mossy_TileSet_2.png");
}

Tile::~Tile() {
    gTileTexture.free();
}

void Tile::render(SDL_Rect& camera, SDL_Rect gTileClips[]) {
    //If the tile is on screen
    if(checkCollision(mBox, camera) && mType != -1) {
        //Show the tile
        gTileTexture.render(gRenderer, mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
    }
}

int Tile::getType() {
    return mType;
}

SDL_Rect Tile::getBox() {
    return mBox;
}

bool touchesWall( SDL_Rect box, vector<Tile*> tiles )
{
    //Go through the tiles
    for(Tile* tile : tiles)
    {
        //If the tile is a wall type tile
        if(tile->getType() != -1)
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tile->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

Map::Map(int _level) {
    level = _level;
    set_tiles("res/Tile_map/Mossy_level.csv");
}

bool Map::set_tiles(std::string file_path) {
        //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( file_path.c_str() );

    //If the map couldn't be loaded
    if( map.fail() )
    {
        printf( "Unable to load map map!\n" );
        tilesLoaded = false;
    }
        else
    {
        string line, word;
        Tile* new_tile = NULL;
        int tile_type = -1;
        int tile_index = 0;
        int row = 0, total_tiles = 0;
        while(getline(map, line)) {
            stringstream str(line);
            while(getline(str, word, ' ')) {
                tile_type = stoi(word.c_str());
                new_tile = new Tile(x, y, tile_type);
                tile_set.push_back(new_tile);
                x += TILE_WIDTH;
                total_tiles++;
            }
            x = 0;
            y += TILE_HEIGHT;
            row++;
        }
        int col = total_tiles / row;

        LEVEL_WIDTH = col * TILE_WIDTH;
        LEVEL_HEIGHT = col * TILE_HEIGHT;

        //Clip the sprite sheet
        if( tilesLoaded )
        {
            for(int i = 0; i < 7; i++) {
                for(int j = 0; j < 7; j++) {
                    tile_clips[i * 7 + j].x = j * TILE_CLIP_WIDTH;
                    tile_clips[i * 7 + j].y = i * TILE_CLIP_WIDTH;
                    tile_clips[i * 7 + j].w = TILE_CLIP_WIDTH;
                    tile_clips[i * 7 + j].h = TILE_CLIP_WIDTH;
                }
            }
        }
    }

    //Close the map
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

void Map::render(SDL_Rect& camera) {
    for(Tile* tile : tile_set) {
        tile -> render(camera, tile_clips);
    }
}