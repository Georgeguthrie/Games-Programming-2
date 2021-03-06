#include "Game_Window.h"


Game_Window::Game_Window()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenResolutionWidth = 1024.0f;
	screenResolutionHeight = 768.0f; 
}

Game_Window::~Game_Window()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(sdlWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initGame_Window())
	SDL_Quit();
}

float Game_Window::getScreenWidth() { return screenResolutionWidth; } //getters
float Game_Window::getScreenHeight() { return screenResolutionHeight; }

void Game_Window::returnError(std::string errorString) //error handling
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void Game_Window::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow); //swap buffers
}

void Game_Window::clearGame_Window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void Game_Window::initGame_Window()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenResolutionWidth, (int)screenResolutionHeight, SDL_WINDOW_OPENGL); // create window

	if (sdlWindow == nullptr) //error handling
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr) //error handling
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) //error handling
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont drawMesh faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}