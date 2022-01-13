#include "BGMusic.h"
#include <iostream>
#include <fstream>

BGMusic::BGMusic() //sets up the settings of the audio
{
    int music_rate = 22050;
    Uint16 music_format = AUDIO_S16SYS;
    int music_channels = 2;
    int music_buffers = 4096;

    if (Mix_OpenAudio(music_rate, music_format, music_channels, music_buffers) != 0) //error handling
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init music: %s", Mix_GetError()); 
        exit(-1);
    }
}

BGMusic::~BGMusic()
{
    SDL_Quit();
}

void BGMusic::addMusicTrack(const char* path) //loads the music track from a file
{
    backgroundAudio = Mix_LoadMUS(path);

    if (backgroundAudio == NULL) //error handling
    {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    }

}

void BGMusic::playMusicTrack() //plays the music loaded from the file
{
    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(backgroundAudio, -1);
    }

}