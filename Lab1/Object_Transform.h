#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Viewport.h"

struct Object_Transform
{
public:
	Object_Transform(const glm::vec3& Position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->Position = Position;
		this->rotation = rotation;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const //gets details about the model
	{
		glm::mat4 positionMatrix = glm::translate(Position);
		glm::mat4 scaleMatrix = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotationMatrix = rotX * rotY * rotZ;

		return positionMatrix * rotationMatrix * scaleMatrix; //returns the position, rotation and scale matrixes of the object
	}

	inline glm::vec3* getPosition() { return &Position; } //getters
	inline glm::vec3* getRotation() { return &rotation; }
	inline glm::vec3* getScale() { return &scale; }

	inline void setPosition(glm::vec3& Position) { this->Position = Position; } // setters
	inline void setRotation(glm::vec3& rotation) { this->rotation = rotation; }
	inline void setScale(glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 Position; //holds the position of the model
	glm::vec3 rotation; //holds the rotation of the model
	glm::vec3 scale; //holds the scale of the model
};


