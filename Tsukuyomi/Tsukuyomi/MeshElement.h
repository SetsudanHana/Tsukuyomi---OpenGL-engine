#pragma once

#include "stdafx.h"

#include "IndexBufferObject.h"
#include "VertexBufferObject.h"
#include "Texture.h"

class MeshElement
{
public:
	MeshElement();
	MeshElement(const MeshElement&);
	~MeshElement();

	VertexBufferObject getPosVBO();
	VertexBufferObject getCoordVBO();
	VertexBufferObject getNorVBO();

	IndexBufferObject getIBO();

	Texture getTexture();

	void setPosVBO(const VertexBufferObject&);
	void setCoordVBO(const VertexBufferObject&);
	void setNorVBO(const VertexBufferObject&);

	void setIBO(const IndexBufferObject&);

	void setTexture(const Texture&);

private:

	VertexBufferObject m_posVBO;
	VertexBufferObject m_coordVBO;
	VertexBufferObject m_norVBO;

	IndexBufferObject m_ibo;

	Texture m_texture;
};
