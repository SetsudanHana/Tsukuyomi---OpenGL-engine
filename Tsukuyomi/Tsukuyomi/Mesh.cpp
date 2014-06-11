#include "stdafx.h"

#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(const unsigned& elementsNum)
{
	for(UINT i = 0; i < elementsNum; ++i)
	{
		m_elements.push_back(new MeshElement());
	}
}

Mesh::Mesh(const Mesh&)
{
	
}

Mesh::~Mesh()
{
	for(auto i : m_elements)
		delete i;
}

std::vector<MeshElement*> Mesh::getElements()
{
	return m_elements;
}