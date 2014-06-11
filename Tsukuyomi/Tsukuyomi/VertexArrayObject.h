#pragma once

#include "VertexBufferObject.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	VertexArrayObject(const VertexArrayObject&);
	~VertexArrayObject();

	unsigned getVAO();
	void bindVBO(VertexBufferObject&, const VertexBufferType&);
	void enableVBO(const VertexBufferType&);
	void disableVBO(const VertexBufferType&);

private:
	unsigned m_vao;
};