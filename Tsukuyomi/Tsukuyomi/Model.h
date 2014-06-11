#pragma once

#include "stdafx.h"

#include "Mesh.h"

class Model
{
public:

	Model();
	Model(const Model&);
	~Model();

	void setMesh(Mesh*);
	void setWorldMatrix(const glm::mat4&);

	Mesh* getMesh();
	glm::mat4 getWorldMatrix();

	void translate(const  glm::vec3&);
	void rotate(const glm::vec3&, const float&);
	void scale(const glm::vec3&);

private:

	Mesh* m_mesh;
	glm::mat4 m_worldMatrix;
};