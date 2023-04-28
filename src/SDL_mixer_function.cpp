#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_mixer_functions.hpp"

using namespace std;

Mix_Music* background_music = NULL;

Mix_Chunk* button_select_sound = NULL;
Mix_Chunk* reverse_sound = NULL;
Mix_Chunk* eatable_sound = NULL;

bool LoadMusic()
{
	bool success = true;
	background_music = Mix_LoadMUS("res/sounds/XuanThi-HaAnhTuan.mp3");
	if (background_music == NULL)
	{
		cerr << "Failed to load background music! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	button_select_sound = Mix_LoadWAV("res/sounds/button_pressed.wav");
	if (background_music == NULL)
	{
		cerr << "Failed to load button select sound! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	// selected_sound = Mix_LoadWAV("audio/selectedSound.mp3");
	// if (selected_sound == NULL)
	// {
	// 	cerr << "Failed to load selected sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
	// 	success = false;
	// }

	// reverse_sound = Mix_LoadWAV("audio/reverseSound.wav");
	// if (reverse_sound == NULL)
	// {
	// 	cerr << "Failed to load reverse sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
	// 	success = false;
	// }

	// eatable_sound = Mix_LoadWAV("audio/eatableSound.mp3");
	// if (eatable_sound == NULL)
	// {
	// 	cerr << "Failed to load eat sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
	// 	success = false;
	// }
	return success;
}
void CloseMusic()
{
	Mix_FreeChunk(eatable_sound);
	Mix_FreeChunk(reverse_sound);
	Mix_FreeChunk(button_select_sound);
	eatable_sound = NULL;
	reverse_sound = NULL;
	button_select_sound = NULL;
	Mix_FreeMusic(background_music);
	background_music = NULL;
	Mix_Quit();
}
