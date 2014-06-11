#pragma once

#include "stdafx.h"

#define DAG2RAD M_PI/180.0f

class Camera
{
public:

	Camera();
	Camera(const Camera&);
	~Camera();

	void setAlfa(const float&);
	void setBeta(const float&);
	void setPosition(const glm::vec3&);

	float getAlfa();
	float getBeta();
	glm::vec3 getPosition();

	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	
	glm::vec3 direction();

private:

	void update();

private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	float m_alfa, m_beta;
	glm::vec3 m_position;
};