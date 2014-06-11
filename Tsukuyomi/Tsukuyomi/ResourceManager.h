#pragma once

#include "stdafx.h"

#include "Logger.h"

#define TEXTURE_PATH "../data/textures/"
#define SHADER_PATH "../data/shaders/"
#define MODEL_PATH "../data/models/"


class ResourceManager
{
public:

	~ResourceManager();

	static ResourceManager* instance()
	{
		static ResourceManager instance;
		return &instance;
	}

	std::string loadTextFile(const std::string&);
	UINT loadTexture(const std::string&);
	const aiScene* loadScene(const std::string&);

private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
};