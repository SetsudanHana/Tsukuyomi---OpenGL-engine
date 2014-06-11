#include "stdafx.h"

#include "Light.h"

glm::vec3 Light::m_ambient = glm::vec3(0.0f);

Light::Light()
{
	m_type = LightType::POINT_LIGHT;
	m_color = m_direction = m_position = glm::vec3(0.0f);
	m_radius = m_inner = m_outer =  m_shiness= m_specularPower = 0.0f;
}

Light::Light(const Light&)
{

}

Light::Light(const LightType& type)
{
	m_type = type;
	m_color = m_direction = m_position = glm::vec3(0.0f);
	m_radius = m_outer = m_outer = m_shiness = 0.0f;
}

Light::~Light()
{

}

void Light::setColor(const glm::vec3& color)
{
	m_color = color;
}

void Light::setDirection(const glm::vec3& direction)
{
	m_direction = direction;
}

void Light::setPosition(const glm::vec3& position)
{
	m_position = position;
}

void Light::setType(const LightType& type)
{
	m_type = type;
}

void Light::setRadius(const float& radius)
{
	m_radius = radius;
}

void Light::setInner(const float& inner)
{
	m_inner = inner;
}

void Light::setOuter(const float& outer)
{
	m_outer = outer;
}

void Light::setShiness(const float& shiness)
{
	m_shiness = shiness;
}

void Light::setSpecularPower(const float& specularPower)
{
	m_specularPower = specularPower;
}

float Light::getSpecularPower()
{
	return m_specularPower;
}

float Light::getShiness()
{
	return m_shiness;
}

float Light::getRadius()
{
	return m_radius;
}

float Light::getInner()
{
	return m_inner;
}

float Light::getOuter()
{
	return m_outer;
}

glm::vec3 Light::getDirection()
{
	return m_direction;
}

glm::vec3 Light::getPosition()
{
	return m_position;
}

glm::vec3 Light::getColor()
{
	return m_color;
}

LightType Light::getType()
{
	return m_type;
}
