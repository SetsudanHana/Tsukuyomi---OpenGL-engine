#include "stdafx.h"

#include "MeshElement.h"

MeshElement::MeshElement()
{

}

MeshElement::MeshElement(const MeshElement&)
{

}

MeshElement::~MeshElement()
{

}

VertexBufferObject MeshElement::getPosVBO()
{
	return m_posVBO;
}

VertexBufferObject MeshElement::getNorVBO()
{
	return m_norVBO;
}

VertexBufferObject MeshElement::getCoordVBO()
{
	return m_coordVBO;
}

IndexBufferObject MeshElement::getIBO()
{
	return m_ibo;
}

Texture MeshElement::getTexture()
{
	return m_texture;
}

void MeshElement::setCoordVBO(const VertexBufferObject& vbo)
{
	m_coordVBO = vbo;
}

void MeshElement::setIBO(const IndexBufferObject& ibo)
{
	m_ibo = ibo;
}

void MeshElement::setNorVBO(const VertexBufferObject& vbo)
{
	m_norVBO = vbo;
}

void MeshElement::setPosVBO(const VertexBufferObject& vbo)
{
	m_posVBO = vbo;
}

void MeshElement::setTexture(const Texture& texture)
{
	m_texture = texture;
}