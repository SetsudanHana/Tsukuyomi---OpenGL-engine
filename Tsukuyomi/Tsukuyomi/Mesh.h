#pragma once

#include "stdafx.h"

#include "MeshElement.h"

class Mesh
{
public:

	Mesh();
	Mesh(const unsigned&);
	Mesh(const Mesh&);
	~Mesh();

	std::vector<MeshElement*> getElements();

private:

	std::vector<MeshElement*> m_elements;
};