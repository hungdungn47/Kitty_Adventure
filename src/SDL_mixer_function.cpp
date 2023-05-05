#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "SDL_mixer_functions.hpp"

using namespace std;

Mix_Music* background_music = NULL;
Mix_Music* giai_dieu_to_quoc = NULL;
Mix_Music* dat_nuoc_tron_niem_vui = NULL;
Mix_Music* hanh_khuc_ngay_va_dem = NULL;

Mix_Chunk* button_select_sound = NULL;
Mix_Chunk* reverse_sound = NULL;
Mix_Chunk* eatable_sound = NULL;

bool LoadMusic()
{
	bool success = true;
	dat_nuoc_tron_niem_vui = Mix_LoadMUS("res/sounds/dat-nuoc-tron-niem-vui-nsut-ta-minh-tam.mp3");
	if(dat_nuoc_tron_niem_vui == NULL) {
		cout << "Failed to load Dat nuoc tron niem vui. " << Mix_GetError() << endl;
		success = false;
	}
	hanh_khuc_ngay_va_dem = Mix_LoadMUS("res/sounds/HanhKhucNgayVaDem.mp3");
	if(hanh_khuc_ngay_va_dem == NULL) {
		cout << "Failed to load Hanh khuc ngay va dem. " << Mix_GetError() << endl;
		success = false;
	}
	giai_dieu_to_quoc = Mix_LoadMUS("res/sounds/GiaiDieuToQuoc_TrongTan.mp3");
	if(giai_dieu_to_quoc == NULL) {
		cout << "Failed to load Giai dieu to quoc. " << Mix_GetError() << endl;
		success = false;
	}
	button_select_sound = Mix_LoadWAV("res/sounds/button_pressed.wav");
	if (button_select_sound == NULL)
	{
		cout << "Failed to load button select sound! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}
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
