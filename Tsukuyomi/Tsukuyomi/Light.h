#pragma once

#include "stdafx.h"

enum LightType
{
	POINT_LIGHT,
	SPOT_LIGHT,
	DIRECTION_LIGHT
};

class Light
{
public:

	Light();
	Light(const LightType&);
	Light(const Light&);
	~Light();

	void setType(const LightType&);
	void setDirection(const glm::vec3&);
	void setPosition(const glm::vec3&);
	void setColor(const glm::vec3&);
	void setRadius(const float&);
	void setInner(const float&);
	void setOuter(const float&);
	void setShiness(const float&);
	void setSpecularPower(const float&);

	LightType getType();
	glm::vec3 getDirection();
	glm::vec3 getPosition();
	glm::vec3 getColor();
	float getRadius();
	float getInner();
	float getOuter();
	float getShiness();
	float getSpecularPower();

	static glm::vec3 m_ambient;

private:
	LightType m_type;

	float m_radius;
	float m_inner;
	float m_outer;
	float m_shiness;
	float m_specularPower;

	glm::vec3 m_direction;
	glm::vec3 m_position;

	glm::vec3 m_color;


};