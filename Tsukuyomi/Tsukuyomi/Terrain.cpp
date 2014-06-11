#include "stdafx.h"

#include "Terrain.h"

float Terrain::maxHeight = 0.3f;

Terrain::Terrain()
{
	m_worldMatrix = glm::mat4();
}

Terrain::Terrain(const Terrain& other)
{
	m_worldMatrix = other.m_worldMatrix;
	m_position = other.m_position;
	m_ibo = other.m_ibo;
	m_heightmap = other.m_heightmap;
	for(int i = 0; i < 3; ++i)
		m_texture[i] = other.m_texture[i];
}

Terrain::~Terrain()
{

}

void Terrain::setHeightmap(const Texture& heightmap)
{
	m_heightmap = heightmap;
}

void Terrain::setIBO(const IndexBufferObject& ibo)
{
	m_ibo = ibo;
}

void Terrain::setPosition(const VertexBufferObject& position)
{
	m_position = position;
}

Texture Terrain::getHeightmap()
{
	return m_heightmap;
}

VertexBufferObject Terrain::getPosition()
{
	return m_position;
}

IndexBufferObject Terrain::getIBO()
{
	return m_ibo;
}

void Terrain::translate(const glm::vec3& vec)
{
	m_worldMatrix = glm::translate(m_worldMatrix, vec);
}

glm::mat4 Terrain::getWorldMatrix()
{
	return m_worldMatrix;
}

void Terrain::setTexture(const Texture& texture, const unsigned& id)
{
	m_texture[id] = texture;
}

Texture Terrain::getTexture(const unsigned& id)
{
	return m_texture[id];
}

void Terrain::scale(const glm::vec3& vec)
{
	m_worldMatrix = glm::scale(m_worldMatrix, vec);
}