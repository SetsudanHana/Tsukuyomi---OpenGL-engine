#pragma once

#include "OGL.h"
#include "Scene.h"
#include "Shader.h"
#include "GBuffer.h"
#include "ShaderFactory.h"

enum ProgramType
{
	Model_Geometry,
	Terrain_Geometry,
	Light_D,
	Light_P,
	Light_S,
	Light_N
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
	GBuffer* m_gbuffer;
	OGL* m_ogl;
	std::map<ProgramType, Shader> m_programs;
};