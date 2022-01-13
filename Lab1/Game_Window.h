#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Game_Window
{
public:
	Game_Window();
	~Game_Window();
	void initGame_Window(); //creates a new display window
	void swapBuffer();
	void clearGame_Window(float r, float g, float b, float a); //clears the game window

	float getScreenWidth(); //gets the width of the screen
	float getScreenHeight(); //gets the height of the screen

private:

	void returnError(std::string errorString);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float screenResolutionWidth; //holds the width of the screen
	float screenResolutionHeight; //holds the height of the screen
};

