#pragma once

#include "stdafx.h"

#include "BufferDeleter.h"

enum VertexBufferType
{
	POSITION_2,
	POSITION_3,
	TEXTURE_COORDS,
	NORMALS
};

class VertexBufferObject
{
public:

	VertexBufferObject();
	VertexBufferObject(const unsigned&, float[],const VertexBufferType&);
	VertexBufferObject(const VertexBufferObject&);
	~VertexBufferObject();

	unsigned getVBO();
	VertexBufferType getType();
	unsigned getSize();

private:
	unsigned m_vbo;
	unsigned m_size;
	VertexBufferType m_type;
};