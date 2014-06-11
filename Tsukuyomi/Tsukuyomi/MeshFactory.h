#pragma once

#include "stdafx.h"

#include "Mesh.h"
#include "ResourceManager.h"
#include "TextureFactory.h"

class MeshFactory
{
public:

	MeshFactory();
	MeshFactory(const MeshFactory&);
	~MeshFactory();

	Mesh* createMesh(const std::string&);

private:

};