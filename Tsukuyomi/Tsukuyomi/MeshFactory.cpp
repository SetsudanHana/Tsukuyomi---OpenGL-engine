#include "stdafx.h"

#include "MeshFactory.h"

MeshFactory::MeshFactory()
{

}

MeshFactory::MeshFactory(const MeshFactory&)
{

}

MeshFactory::~MeshFactory()
{

}

Mesh* MeshFactory::createMesh(const std::string& name)
{
	const aiScene* scene = ResourceManager::instance()->loadScene(MODEL_PATH + name);

	if( !scene )
	{
		Logger::getInstance()->write("Failed to load " + name + " Mesh");
		return nullptr;
	}

	UINT mNumSubsets = scene->mNumMeshes;

	Mesh* out = new Mesh( mNumSubsets );

	for(UINT i = 0; i < mNumSubsets; ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];

		unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];

		UINT counter = 0;

		for (unsigned int x = 0; x < mesh->mNumFaces; ++x)
		{
			for (unsigned int a = 0; a < 3; ++a)
			{
				indices[counter++] = mesh->mFaces[x].mIndices[a];
			}
		}

		out->getElements()[i]->setIBO( IndexBufferObject( counter, indices ));

		unsigned numVertices = mesh->mNumVertices;

		float* verticesPos = new float[numVertices*3];
		float* verticesNormal = new float[numVertices*3];
		float* verticesTextCoord = new float[numVertices*2];

		for(UINT x = 0; x < numVertices; ++x)
		{
			verticesPos[3*x + 0] = mesh->mVertices[x].x;
			verticesPos[3*x + 1] = mesh->mVertices[x].y;
			verticesPos[3*x + 2] = mesh->mVertices[x].z;

			if(mesh->HasNormals())
			{
				verticesNormal[3*x + 0] = mesh->mNormals[x].x;
				verticesNormal[3*x + 1] = mesh->mNormals[x].y;
				verticesNormal[3*x + 2] = mesh->mNormals[x].z;
			}

			if(mesh->HasTextureCoords(0))
			{
				verticesTextCoord[2*x + 0] = mesh->mTextureCoords[0][x].x;
				verticesTextCoord[2*x + 1] = mesh->mTextureCoords[0][x].y;
			}

		}

		if( mesh->HasPositions() )
		{
			out->getElements()[i]->setPosVBO(VertexBufferObject(numVertices, verticesPos, VertexBufferType::POSITION_3 ));
		}

		if( mesh->HasNormals() )
		{
			out->getElements()[i]->setNorVBO(VertexBufferObject(numVertices, verticesNormal, VertexBufferType::NORMALS ));
		}

		if( mesh->HasTextureCoords(0) )
		{
			out->getElements()[i]->setCoordVBO(VertexBufferObject(numVertices, verticesTextCoord, VertexBufferType::TEXTURE_COORDS));
		}

		delete [] indices;
		delete [] verticesNormal;
		delete [] verticesPos;
		delete [] verticesTextCoord;

		const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		aiString szPath;

		if (AI_SUCCESS == aiGetMaterialString(material, AI_MATKEY_TEXTURE_DIFFUSE(0), &szPath))

		{
			std::string strPath(szPath.data, szPath.length);

			TextureFactory factory;

			out->getElements()[i]->setTexture(factory.createTexture(strPath)); 
		}
	}

	return out;
}