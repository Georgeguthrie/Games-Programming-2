#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct viewport
{
public:
	viewport()
	{
	}

	void initGameWindow(const glm::vec3& Position, float fov, float aspect, float nearClip, float farClip) //creates a camera
	{
		this->Position = Position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	glm::vec3 getPos() //gets the position of the camera
	{
		return this->Position;
	}

	inline glm::mat4 GetViewProjection() const //gets the view project of the camera
	{
		return projection * glm::lookAt(Position, Position + forward, up);
	}

protected:
private:
	glm::mat4 projection; //holds the projection of the camera
	glm::vec3 Position; //holds the position of the camera
	glm::vec3 forward;
	glm::vec3 up;
};


