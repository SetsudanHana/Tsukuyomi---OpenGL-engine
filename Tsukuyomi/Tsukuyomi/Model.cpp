#include "stdafx.h"

#include "Model.h"

Model::Model()
{
	m_mesh = nullptr;
	m_worldMatrix = glm::mat4(1.0f);
}

Model::Model(const Model& other)
{
	m_mesh = other.m_mesh;
	m_worldMatrix = other.m_worldMatrix;	
}

Model::~Model()
{

}

void Model::setMesh(Mesh* mesh)
{
	m_mesh = mesh;
}

void Model::setWorldMatrix(const glm::mat4& matrix)
{
	m_worldMatrix = matrix;
}

Mesh* Model::getMesh()
{
	return m_mesh;
}

glm::mat4 Model::getWorldMatrix()
{
	return m_worldMatrix;
}

void Model::translate(const glm::vec3& v)
{
	m_worldMatrix = glm::translate( m_worldMatrix, v );
}

void Model::rotate(const glm::vec3& v, const float& angle)
{
	m_worldMatrix = glm::rotate( m_worldMatrix, angle, v );
}

void Model::scale(const glm::vec3& v)
{
	m_worldMatrix = glm::scale( m_worldMatrix, v );
}
