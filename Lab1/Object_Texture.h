#pragma once
#include <string>
#include <GL\glew.h>

class Object_Texture
{
public:
	Object_Texture(const std::string& fileName); //handles loading and storing textures from files

	void bindShader(unsigned int unit); // bind up to 32 textures

	~Object_Texture();

protected:
private:

	GLuint textureHandler;
};

