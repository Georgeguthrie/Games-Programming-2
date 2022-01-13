#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex //handles the vertices of the objects
{
public:
	Vertex(const glm::vec3& Position, const glm::vec2& texCoord)
	{
		this->Position = Position;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* getVertexPosition() { return &Position; }  //getters
	glm::vec2* getVertexTexCoord() { return &texCoord; }
	glm::vec3* getVertexNormal() { return &normal; }

private:
	glm::vec3 Position; //holds the vertex position
	glm::vec2 texCoord; //holds the vertex text coordinates
	glm::vec3 normal; //holds the vertex normals
};

struct Sphere //handles the spheres of the objects
{
public:

	Sphere(){}

	glm::vec3 getVertexPosition() { return Position; } //getters
	float getSphereRadius() { return radius; }

	void setSpherePosition(glm::vec3 Position) //setters
	{
		this->Position = Position;
	}

	void setSphereRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 Position; //holds the sphere position
	float radius; //holds the sphere radius
};

class Object_Mesh
{
public:
	Object_Mesh();
	~Object_Mesh();


	void drawMesh(); //handles drawing the mesh
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadObjectModel(const std::string& filename); //loads the object model from a file
	void initObjectModel(const IndexedModel& model); //initalises the object model
	void updateSphereData(glm::vec3 Position, float radius);
	glm::vec3 getSpherePosition() { return meshSphere.getVertexPosition(); } //getters
	float getSphereRadius() { return meshSphere.getSphereRadius(); }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere meshSphere;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to drawMesh
};