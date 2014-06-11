#include "stdafx.h"

#include "Camera.h"

Camera::Camera()
{
	m_projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.f);
	m_viewMatrix = glm::mat4(1.0f);
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_alfa = m_beta = 0.0f;
}

Camera::Camera(const Camera& other)
{
	m_projectionMatrix = other.m_projectionMatrix;
	m_alfa = other.m_alfa;
	m_beta = other.m_beta;
	m_position = other.m_position;
	m_viewMatrix = other.m_viewMatrix;
}

Camera::~Camera()
{

}

glm::mat4 Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

void Camera::setAlfa(const float& alfa)
{
	m_alfa = alfa;
	update();
}

void Camera::setBeta(const float& beta)
{
	m_beta = beta;
	update();
}

void Camera::setPosition(const glm::vec3& position)
{
	m_position = position;
	update();
}

float Camera::getAlfa()
{
	return m_alfa;
}

float Camera::getBeta()
{
	return m_beta;
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::update()
{
	double sinAlfa = glm::sin(m_alfa * DAG2RAD);
	double sinBeta = glm::sin(m_beta * DAG2RAD);
	double cosAlfa = glm::cos(m_alfa * DAG2RAD);
	double cosBeta = glm::cos(m_beta * DAG2RAD);

	m_viewMatrix = glm::lookAt( m_position, glm::vec3(m_position.x + sinAlfa*cosBeta, m_position.y - sinBeta, m_position.z - cosAlfa*cosBeta), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::direction()
{
	double sinAlfa = glm::sin(m_alfa * DAG2RAD);
	double sinBeta = glm::sin(m_beta * DAG2RAD);
	double cosAlfa = glm::cos(m_alfa * DAG2RAD);
	double cosBeta = glm::cos(m_beta * DAG2RAD);

	return glm::vec3(sinAlfa*cosBeta, -sinBeta, -cosAlfa*cosBeta);
}