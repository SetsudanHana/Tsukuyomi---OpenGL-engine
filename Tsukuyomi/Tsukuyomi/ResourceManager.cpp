#include "stdafx.h"

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::ResourceManager(const ResourceManager&)
{

}

ResourceManager::~ResourceManager()
{

}

std::string ResourceManager::loadTextFile(const std::string& path)
{
	std::ifstream file(path);

	if(!file.good())
	{
		Logger::getInstance()->write("Opening Text file: " + path + " failed");
		return "";
	}

	std::stringstream stream ;
	stream << file.rdbuf();

	file.close();

	return stream.str();
}

UINT ResourceManager::loadTexture(const std::string& path)
{
	UINT texture = 0;

	FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(path.c_str()), path.c_str());

	if(!bitmap)
	{
		Logger::getInstance()->write("Failed to load texture: " + path);
		return UINT_MAX;
	}

	FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	FreeImage_Unload(bitmap);

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));



	FreeImage_Unload(pImage);

	return texture;
}

const aiScene* ResourceManager::loadScene(const std::string& path)
{
	static Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile( path.c_str(), 
		aiProcess_Triangulate |
		aiProcess_MakeLeftHanded |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenSmoothNormals |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_GenUVCoords |
		aiProcess_TransformUVCoords |
		//aiProcess_FlipUVs |
		aiProcess_OptimizeMeshes); 

	if(!scene)
	{
		std::string err = importer.GetErrorString();
		Logger::getInstance()->write(err.c_str());
		return nullptr;
	}

	return scene;
}