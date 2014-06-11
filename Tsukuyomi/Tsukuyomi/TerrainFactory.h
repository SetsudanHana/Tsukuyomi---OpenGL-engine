#pragma once

#include "stdafx.h"

#include "TextureFactory.h"
#include "Terrain.h"
#include "Logger.h"

class TerrainFactory
{
public:

	TerrainFactory();
	TerrainFactory(const TerrainFactory&);
	~TerrainFactory();

	Terrain createTerrain(const std::string&, const unsigned&);

private:

};
