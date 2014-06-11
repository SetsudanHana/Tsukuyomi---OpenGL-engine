#pragma once

#include "stdafx.h"

#include "Light.h"
#include "Model.h"
#include "Terrain.h"
#include "Camera.h"

#include "VertexArrayObject.h"

enum SceneLightning
{
	P,
	S,
	D,
	NONE
};

class Scene
{
public:
	Scene();
	Scene(const Scene&);
	~Scene();

	void addTerrain(Terrain*);
	void addModel(Model*);
	void addLight(Light*);	
	void setCamera(Camera*);

	std::vector<Terrain*> Terrains();
	std::vector<Model*> Models();
	std::vector<Light*> Lights();
	Camera* getCamera();

	SceneLightning lightningType();

	std::vector<VertexArrayObject> getVAOs(Mesh*);
	VertexArrayObject getVAOs(Terrain*);

private:

	std::vector<Terrain*> m_terrains;
	std::vector<Model*> m_models;
	std::vector<Light*> m_lights;
	Camera* m_camera;

	SceneLightning m_lightning;

	std::map<Mesh*, std::vector<VertexArrayObject> > m_meshVAOs;
	std::map<Terrain*, VertexArrayObject > m_terrainVAOs;
};
