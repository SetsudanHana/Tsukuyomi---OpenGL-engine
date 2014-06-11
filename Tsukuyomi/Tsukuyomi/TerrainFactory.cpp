#include "stdafx.h"

#include "TerrainFactory.h"

TerrainFactory::TerrainFactory()
{

}

TerrainFactory::TerrainFactory(const TerrainFactory&)
{

}

TerrainFactory::~TerrainFactory()
{

}

Terrain TerrainFactory::createTerrain(const std::string& name, const unsigned& parts)
{
	Terrain terrain;

	TextureFactory textureFactory;

	Texture heightmap = textureFactory.createTexture(name);

	terrain.setHeightmap( heightmap );

	Texture ground = textureFactory.createTexture("ground.jpg");

	terrain.setTexture( ground, 1 );

	Texture grass = textureFactory.createTexture("grass.jpg");

	terrain.setTexture( grass, 0 );

	Texture snow = textureFactory.createTexture("snow.jpg");

	terrain.setTexture( snow, 2 );

	unsigned sizeOfHeightmap = (parts-1)*(parts-1);

	float * positions = new float[parts*parts*2];

	for(int i = 0; i < parts; ++i)
	{
		for(int j = 0; j < parts; ++j)
		{
			positions[2*(parts*i +j)] = (float)(i)/parts;
			positions[2*(parts*i +j)+1] = (float)(j)/parts;
		}
	}

	unsigned * indices = new unsigned[sizeOfHeightmap*6];

	int counter = 0;

	for(int j = 0; j < parts-1; ++j)
	{
		for(int i = 0 ; i < parts-1; ++i)
		{
			indices[counter++] = i + 1 + (j + 1)*parts;
			indices[counter++] = i + 1 + j*parts;
			indices[counter++] = i + j*parts;

			indices[counter++] = i + (j + 1)*parts;
			indices[counter++] = i + 1 + (j + 1)*parts;
			indices[counter++] = i + j*parts;
		}
	}

	VertexBufferObject posVBO(parts*parts, positions, VertexBufferType::POSITION_2);
	IndexBufferObject ibo( sizeOfHeightmap*6, indices );

	terrain.setPosition(posVBO);
	terrain.setIBO(ibo);

	delete [] positions;
	delete [] indices;

	return terrain;
}