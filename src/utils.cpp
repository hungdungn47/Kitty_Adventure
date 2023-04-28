#include "utils.hpp"
#include "constants.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

LTexture::LTexture() {
  // Initialize
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
  mPosX = 0;
  mPosY = 0;
}

LTexture::~LTexture() {
  // Deallocate
  free();
}

void LTexture::setDimension(int w, int h) {
  mWidth = w;
  mHeight = h;
}

bool LTexture::loadFromFile(SDL_Renderer *renderer, std::string path) {
  // Get rid of preexisting texture
  free();
  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (NULL == loadedSurface) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    // Create texture from surface pixel
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (NULL == newTexture) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  // return success
  mTexture = newTexture;
  return NULL != mTexture;
}

bool LTexture::loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font,
                                    std::string textureText,
                                    SDL_Color textColor) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font, textureText.c_str(), textColor);
  if (NULL == textSurface) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
  } else {
    // Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (NULL == mTexture) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n",
             SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    // Get rid of old surface
    SDL_FreeSurface(textSurface);
  }

  // Return success
  return mTexture != NULL;
}

void LTexture::free() {
  // Free texture if it exists
  if (NULL != mTexture) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, SDL_Rect *dst_rect,
                      double angle, SDL_Point *center, SDL_RendererFlip flip) {

  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  // Set clip rendering dimensions
  if (NULL != dst_rect) {
    renderQuad.w = dst_rect->w;
    renderQuad.h = dst_rect->h;
  } else if(NULL != clip) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, -angle, center, flip);

}

void LTexture::renderCenter(SDL_Renderer *renderer, int x_center, int y_center,
                            int w, int h, SDL_Rect *clip, double angle,
                            SDL_Point *center, SDL_RendererFlip flip) {
  // Set rendering space and render to screen, w, h for sprites
  SDL_Rect renderQuad = {x_center - w / 2, y_center - h / 2, mWidth, mHeight};

  // Set clip rendering dimensions
  if (NULL != clip) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  // Render to screen
  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, -angle, center, flip);
}

void LTexture::setPosition(int newX, int newY) {
  mPosX = newX;
  mPosY = newY;
}

int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }
int LTexture::getX() { return mPosX; }
int LTexture::getY() { return mPosY; }

LTimer::LTimer() {
  // Initialize the variables
  mStartTicks = 0;
  mPausedTicks = 0;

  mPaused = false;
  mStarted = false;
}

void LTimer::start() {
  // Start the timer
  mStarted = true;

  // Unpaused the timer
  mPaused = false;

  // Get the current clock time
  mStartTicks = SDL_GetTicks();
  mPausedTicks = 0;
}

void LTimer::stop() {
  // Stop the timer
  mStarted = false;

  // Unpaused the timer
  mPaused = false;

  // Clear tick variables
  mStartTicks = 0;
  mPausedTicks = 0;
}

void LTimer::paused() {
  // if the timer is running and isn't already paused
  if (mStarted && !mPaused) {
    // Pause the timer
    mPaused = true;

    // Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
  }
}

void LTimer::unpaused() {
  if (mStarted && mPaused) {
    // Unpause the timer
    mPaused = false;

    // Reset the starting ticks
    mStartTicks = SDL_GetTicks() - mPausedTicks;

    // Reset the paused ticks
    mPausedTicks = 0;
  }
}

Uint32 LTimer::getTicks() {
  Uint32 time = 0;

  if (mStarted) {
    // Return the number of ticks when the timer was paused
    if (mPaused) {
      time = mPausedTicks;
    } else {
      // Return the current time minus the start time
      time = SDL_GetTicks() - mStartTicks;
    }
  }

  return time;
}

bool LTimer::isStarted() {
  // Timer is running and paused or unpaused
  return mStarted;
}

bool LTimer::isPaused() {
  // Timer is running and paused
  return mPaused && mStarted;
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
  return SDL_HasIntersection(&a, &b);
}


int randomNumber(int l, int r) { return l + rand() % (r - l + 1); }
pair<int, int> shiftXY(float vel, float dir) {
  return {vel * cos(dir * M_PI / 180), -vel * sin(dir * M_PI / 180)};
}

int getNumLevel() {
  ifstream input_file("data/level.txt");
  if (!input_file.is_open()) {
    cerr << "Could not open the file - '" << "data/level.txt" << "'" << endl;
    exit(EXIT_FAILURE);
  }
  return stoi(string((std::istreambuf_iterator<char>(input_file)),
                     std::istreambuf_iterator<char>()));
}


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font* gFont[TOTAL_FONT] = {NULL, NULL, NULL, NULL, NULL};
Mix_Music *gMusic;
// Level player are currently in
int gLevel = 0;
int gMenuID = 0;
LTimer gTimer;
