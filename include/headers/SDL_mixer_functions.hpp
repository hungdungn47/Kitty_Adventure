#ifndef SDL_MIXER_FUNCTION_H
#define SDL_MIXER_FUNCTION_H
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

extern Mix_Music* background_music;
extern Mix_Music* dat_nuoc_tron_niem_vui;
extern Mix_Music* hanh_khuc_ngay_va_dem;
extern Mix_Music* giai_dieu_to_quoc;

extern Mix_Chunk* button_select_sound;
extern Mix_Chunk* reverse_sound;
extern Mix_Chunk* eatable_sound;

bool LoadMusic();
void CloseMusic();

#endif // !SDL_MIXER_FUNCTION_H
