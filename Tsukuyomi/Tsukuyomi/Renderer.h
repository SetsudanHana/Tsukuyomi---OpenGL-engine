#pragma once

#include "OGL.h"
#include "Scene.h"
#include "Shader.h"

enum ProgramType
{
	Model_NONE,
	Model_D,
	Model_P,
	Model_S,
	Terrain_NONE,
	Terrain_D,
	Terrain_P,
	Terrain_S
};

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&);
	~Renderer();

	bool init(Window*, const bool& = false);

	void addProgram(const ProgramType&, const Shader&);

	void clear(const glm::vec4&);
	void swap(Window&);

	void render(const Scene&);

private:
	OGL* m_ogl;
	std::map<ProgramType, Shader> m_programs;
};