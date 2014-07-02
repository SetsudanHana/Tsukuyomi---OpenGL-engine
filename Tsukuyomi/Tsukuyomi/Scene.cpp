#include "stdafx.h"

#include "Scene.h"

Scene::Scene()
{

}

Scene::Scene(const Scene& other)
{
	m_lights = other.m_lights;
	m_models = other.m_models;
	m_terrains = other.m_terrains;
	m_meshVAOs = other.m_meshVAOs;
	m_camera = other.m_camera;
	m_terrainVAOs = other.m_terrainVAOs;
}

Scene::~Scene()
{

}

void Scene::addLight(Light* light)
{
	m_lights.push_back(light);
}

void Scene::addModel(Model* model)
{
	m_models.push_back(model);
	std::vector< VertexArrayObject > vao;

	if(m_meshVAOs.find(model->getMesh()) != m_meshVAOs.end())
		return;

	for(auto i : model->getMesh()->getElements())
	{
		VertexArrayObject object;
		object.bindVBO(i->getPosVBO(), i->getPosVBO().getType());
		object.bindVBO(i->getCoordVBO(), i->getCoordVBO().getType());
		object.bindVBO(i->getNorVBO(), i->getNorVBO().getType());

		vao.push_back( object );
	}
	m_meshVAOs.insert(std::pair<Mesh*, std::vector<VertexArrayObject>>(model->getMesh(), vao));
}

void Scene::addTerrain(Terrain* terrain)
{
	m_terrains.push_back(terrain);

	VertexArrayObject object;

	object.bindVBO( terrain->getPosition(), VertexBufferType::POSITION_2);

	m_terrainVAOs.insert(std::pair<Terrain*, VertexArrayObject>(terrain, object));
}

void Scene::setCamera(Camera* camera)
{
	m_camera = camera;
}

std::vector<Light*> Scene::Lights()
{
	return m_lights;
}

std::vector<Model*> Scene::Models()
{
	return m_models;
}

std::vector<Terrain*> Scene::Terrains()
{
	return m_terrains;
}

Camera* Scene::getCamera()
{
	return m_camera;
}

std::vector<VertexArrayObject> Scene::getVAOs(Mesh* mesh)
{
	return m_meshVAOs.find(mesh)->second;
}

VertexArrayObject Scene::getVAOs(Terrain* terrain)
{
	return m_terrainVAOs.find(terrain)->second;
}