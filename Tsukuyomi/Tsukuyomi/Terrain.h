#pragma once

#include "stdafx.h"

#include "VertexBufferObject.h"
#include "IndexBufferObject.h"
#include "Texture.h"

class Terrain
{
public:
	Terrain();
	Terrain(const Terrain&);
	~Terrain();

	void setPosition(const VertexBufferObject&);
	void setIBO(const IndexBufferObject&);
	void setHeightmap(const Texture&);
	void setTexture(const Texture&, const unsigned&);

	VertexBufferObject getPosition();
	IndexBufferObject getIBO();
	Texture getHeightmap();
	Texture getTexture(const unsigned&);
	glm::mat4 getWorldMatrix();

	void translate(const glm::vec3&);
	void scale(const glm::vec3&);

	static float maxHeight;

private:

	Texture m_heightmap;

	Texture m_texture[3];

	VertexBufferObject m_position;
	IndexBufferObject m_ibo;

	glm::mat4 m_worldMatrix;

};