#pragma once
#include <string>
#include <GL\glew.h>
#include "Object_Transform.h"
#include "Viewport.h"

class Object_Shader
{
public:
	Object_Shader();

	void bindShader(); //Set gpu to use our shaders
	void Update(const Object_Transform& transform, const viewport& viewport);
	void init(const std::string& filename);

	std::string Object_Shader::LoadShader(const std::string& fileName); //loads the shaders
	void Object_Shader::CheckShaderError(GLuint objectShader, GLuint flag, bool isProgram, const std::string& errorMessage); //checks for errors with the shaders
	GLuint Object_Shader::CreateShader(const std::string& text, unsigned int type); //creates shaders

    ~Object_Shader();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the objectShader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
