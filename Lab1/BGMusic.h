#pragma once
#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>

class BGMusic
{
public:
	BGMusic();
	~BGMusic();

	void addMusicTrack(const char* path); //handles adding the music track from a file
	void playMusicTrack(); //handles playing the music track in game

private:
	Mix_Music* backgroundAudio; //holds the music track
};
