#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class LTexture {
public:
  // Initializes variables
  LTexture();
  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(SDL_Renderer *renderer, std::string path);
  // Create image from font string
  bool loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font,
                            std::string textureText, SDL_Color textColor);
  // Deallocates texture
  void free();

  // Set alpha modulation
  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL, SDL_Rect* dst_rect = NULL,
              double angle = 0.0, SDL_Point *center = NULL,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Renders texture at given center
  void renderCenter(SDL_Renderer *renderer, int x_center, int y_center, int w,
                    int h, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Gets image dimensions
  int getWidth();
  int getHeight();
  int getX();
  int getY();

  void setDimension(int w, int h);
  void setPosition(int newX, int newY);

// protected:
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
  int mPosX;
  int mPosY;
};

class LTimer {
public:
  // Initializes variables
  LTimer();

  // The various clock actions
  void start();
  void stop();
  void paused();
  void unpaused();

  // Gets the timer's time
  Uint32 getTicks();

  // Checks the status of the timer
  bool isStarted();
  bool isPaused();

private:
  // The clock time when the timer started
  Uint32 mStartTicks;

  // The ticks stored when the timer was paused
  Uint32 mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;
};

// Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

struct Song {
  string file;
  string file_preview;
  string name;
  string author;
  int duration;
};

const int TOTAL_SONGS = 3;

const Song SONG[TOTAL_SONGS] = {
  {"cYsmix - Peer Gynt.wav", "cYsmix - Peer Gynt_preview.wav", "PEER GYNT", "eYsmix", 141479},
  {"Pico.wav", "Pico_preview.wav", "PICO (FNF)", "Kawai Sprite", 84820},
  {"Fresh.wav", "Fresh_preview.wav", "FRESH (FNF)", "Kawai Sprite", 81920}
};

int getNumLevel();

// The window we'll be rendering to and the window renderer
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

enum FontType {
  NEXA_LIGHT = 0,
  NEXA_BOLD,
  NEXA_LIGHT_10,
  NEXA_BOLD_10,
  NEXA_BOLD_20,
  TOTAL_FONT
};
extern TTF_Font *gFont[TOTAL_FONT];

extern Mix_Music *gMusic;
// Level player are currently in
extern int gLevel;
extern int gMenuID;
// All textures need to be render
extern vector<LTexture> allTextures;
extern LTimer gTimer;
