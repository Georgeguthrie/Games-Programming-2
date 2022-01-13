#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include "Game_Window.h" 
#include "Object_Shader.h"
#include "Object_Mesh.h"
#include "Object_Texture.h"
#include "Object_Transform.h"
#include "BGMusic.h"


enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void runGame(); //functions that run on game start

private:

	void initGameSystems(); //initialises all the required systems of the game
	void processUserInput(); //handles any user input to the game
	void gameLoop(); //code that will constantly run until the game exits
	void drawGameScene(); //draws object in the game world
	bool objectCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad); //returns the distance of objects if they collide with each other
	void playMusic(unsigned int Source, glm::vec3 Position); //plays audio track from the location of a specific object sphere

	Game_Window _gameWindow; //holds a new display window
	GameState _gameState; //holds the game state
	Object_Mesh objectMesh1; //holds the first object mesh
	Object_Mesh objectMesh2; //holds the second object mesh
	Object_Mesh objectMesh3; //holds the third object mesh
	viewport myViewport; //holds a new camera
	Object_Shader objectShader; //holds a new object shader
	BGMusic BGMusic; //holds new audio

	float counter; //used in handling rotation of the objects
};

