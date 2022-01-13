#include "Object_Shader.h"
#include <iostream>
#include <fstream>

Object_Shader::Object_Shader()
{
}


void Object_Shader::init(const std::string& filename)
{
	program = glCreateProgram(); // create objectShader program (openGL saves as ref number)
	shaders[0] = CreateShader(LoadShader("..\\res\\shader.vert"), GL_VERTEX_SHADER); // create vertex objectShader
	shaders[1] = CreateShader(LoadShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); // create fragment objectShader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]); //add all our shaders to the objectShader program "shaders" 
	}

	glBindAttribLocation(program, 0, "position"); // associate attribute variable with our objectShader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");

	glLinkProgram(program); //create executables that will runGame on the GPU shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(program); //check the entire program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform"); // associate with the location of uniform variable within a program
}

Object_Shader::~Object_Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]); //detach objectShader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(program); // delete the program
}

void Object_Shader::bindShader()
{
	glUseProgram(program); //installs the program object specified by program as part of rendering state
}

void Object_Shader::Update(const Object_Transform& transform, const viewport& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint Object_Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint objectShader = glCreateShader(type); //create objectShader based on specified type

	if (objectShader == 0) //if == 0 objectShader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(objectShader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(objectShader); //get open gl to compile objectShader code

	CheckShaderError(objectShader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return objectShader;
}

std::string Object_Shader::LoadShader(const std::string& fileName) //loads the shader from a file
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Object_Shader::CheckShaderError(GLuint objectShader, GLuint flag, bool isProgram, const std::string& errorMessage) //error handling
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(objectShader, flag, &success);
	else
		glGetShaderiv(objectShader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(objectShader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(objectShader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

