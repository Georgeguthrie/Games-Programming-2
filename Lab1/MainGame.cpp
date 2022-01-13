#include "MainGame.h"
#include "viewport.h"
#include <iostream>
#include <string>


Object_Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Game_Window* _gameWindow = new Game_Window(); //new display
    Object_Mesh* objectMesh1(); //Creates a new object mesh
	Object_Mesh* objectMesh2(); //Creates a new object mesh
	Object_Mesh* objectMesh3(); //Creates a new object mesh
}

MainGame::~MainGame()
{
}

void MainGame::runGame() //functions that run on game start
{
	initGameSystems(); 
	gameLoop();
}

void MainGame::initGameSystems() //initialises all the required systems of the game
{
	_gameWindow.initGame_Window(); //new display window
	
	BGMusic.addMusicTrack("..\\res\\Music.wav"); //new music track

	objectMesh1.loadObjectModel("..\\res\\monkey3.obj"); //new object model
	objectMesh2.loadObjectModel("..\\res\\skull.obj"); //new object model
	objectMesh3.loadObjectModel("..\\res\\bone.obj"); //new object model
	
	myViewport.initGameWindow(glm::vec3(0, 0, -5), 70.0f, (float)_gameWindow.getScreenWidth()/_gameWindow.getScreenHeight(), 0.01f, 1000.0f); //new camera

	objectShader.init("..\\res\\shader"); //new objectShader

	counter = 1.0f;
}

void MainGame::gameLoop() //code that will constantly run until the game exits
{
	while (_gameState != GameState::EXIT)
	{
		playMusic(0, objectMesh3.getSpherePosition());
		processUserInput();
		drawGameScene();
		objectCollision(objectMesh1.getSpherePosition(), objectMesh1.getSphereRadius(), objectMesh2.getSpherePosition(), objectMesh2.getSphereRadius());
	}
}

void MainGame::processUserInput() //handles any user input to the game
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::objectCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad) //returns the distance of objects if they collide with each other
{
	float distance = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));
	
	if (distance*distance < (m1Rad + m2Rad))
	{
		cout << distance << '\n';
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::playMusic(unsigned int Source, glm::vec3 Position) //plays audio track from the location of a specific object sphere
{
	BGMusic.playMusicTrack();
}

void MainGame::drawGameScene() //draws object in the game world
{
	_gameWindow.clearGame_Window(0.0f, 0.0f, 0.0f, 1.0f);

	Object_Texture objectTexture1("..\\res\\Wood.jpg"); //load texture
	Object_Texture objectTexture2("..\\res\\Gold.jpg"); //load texture
	Object_Texture objectTexture3("..\\res\\Metal.jpg"); //load texture
	
	transform.setPosition(glm::vec3(sinf(counter), sinf(counter), 0.0)); //sets the position of the first object
	transform.setRotation(glm::vec3(0.0, counter * 5, counter * 5)); //sets the rotation of the first object
	transform.setScale(glm::vec3(0.6, 0.6, 0.6)); //sets the scale of the first object

	objectShader.bindShader(); //binds the shader to the first object
	objectShader.Update(transform, myViewport);
	objectTexture1.bindShader(0); //adds the first texture to the first object
	objectMesh1.drawMesh(); //draws the mesh of the first object
	objectMesh1.updateSphereData(*transform.getPosition(), 0.6f);
	

	transform.setPosition(glm::vec3(-sinf(counter), -0.5, -sinf(counter)*5)); //sets the position of the second object
	transform.setRotation(glm::vec3(counter * 5, counter * 5, 0.0)); //sets the rotation of the second object
	transform.setScale(glm::vec3(0.005, 0.005, 0.005)); //sets the scale of the second object

	objectShader.bindShader(); //binds the shader to the second object
	objectShader.Update(transform, myViewport);
	objectTexture2.bindShader(0); //adds the second texture to the second object
	objectMesh2.drawMesh(); //draws the mesh of the second object
	objectMesh2.updateSphereData(*transform.getPosition(), 0.6f);
	counter = counter + 0.05f;

	transform.setPosition(glm::vec3(-0.8, -0.5, 0.8)); //sets the position of the third object
	transform.setRotation(glm::vec3(0.0, counter * 5, 0.0)); //sets the rotation of the third object
	transform.setScale(glm::vec3(0.005, 0.005, 0.005)); //sets the scale of the third object

	objectShader.bindShader(); //binds the shader to the third object
	objectShader.Update(transform, myViewport);
	objectTexture3.bindShader(0); //adds the third texture to the third object
	objectMesh3.drawMesh(); //draws the mesh of the third object
	objectMesh3.updateSphereData(*transform.getPosition(), 0.6f);
	counter = counter + 0.05f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameWindow.swapBuffer();
} 