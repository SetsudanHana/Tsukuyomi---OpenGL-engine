#include "stdafx.h"

#include "Renderer.h"

Renderer::Renderer()
{
	m_ogl = 0;
	m_gbuffer = 0;
}

Renderer::Renderer(const Renderer&)
{

}

Renderer::~Renderer()
{
	if(m_ogl)
	{
		delete m_ogl;
		m_ogl = 0;
	}
	if(m_gbuffer)
	{
		delete m_gbuffer;
		m_gbuffer = 0;
	}
}

bool Renderer::init(Window* wnd, const bool& debug)
{
	m_ogl = new OGL();
	if (!m_ogl)
	{
		Logger::getInstance()->write("OGL instance couldn't have been created");
		return false;
	}

	Logger::getInstance()->write("OGL instance created");

	bool result = m_ogl->init(wnd);

	if(!result)
	{
		Logger::getInstance()->write("Failed to initialize OGL instance");
		delete m_ogl;
		m_ogl = 0;
		return false;
	}

	Logger::getInstance()->write("OGL instance initialized");

	m_gbuffer = new GBuffer();
	if(!m_gbuffer)
	{
		Logger::getInstance()->write("GBuffer instance couln't have been created");
		return false;
	}

	result = m_gbuffer->Init(wnd->getWidth(), wnd->getHeight());
	if(!result)
	{
		Logger::getInstance()->write("Failed to initialize GBuffer instance");
		return false;
	}

	Logger::getInstance()->write("GBuffer instance initialized");

	if(debug)
	{
		m_ogl->enableDebug();
		Logger::getInstance()->write("OpenGL Debug Enabled");
	}

	ShaderFactory factory;

	Shader model_geo = factory.createShader("geometry_model");
	Shader terrain_geo = factory.createShader("geometry_terrain");

	m_programs.insert(std::pair<ProgramType, Shader>(ProgramType::Model_Geometry, model_geo));
	m_programs.insert(std::pair<ProgramType, Shader>(ProgramType::Terrain_Geometry, terrain_geo));

	return true;
}

void Renderer::clear(const glm::vec4& color)
{
	if(!m_ogl)
	{
		Logger::getInstance()->write("Renderer is not initialized");
		return;
	}

	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swap(Window& wnd)
{
	if(!m_ogl)
	{
		Logger::getInstance()->write("Renderer is not initialized");
		return;
	}

	SDL_GL_SwapWindow(wnd.getWindow());
}

void Renderer::render(const Scene& scene)
{
	if(!m_ogl)
	{
		Logger::getInstance()->write("Renderer is not initialized");
		return;
	}

	if(!m_gbuffer)
	{
		Logger::getInstance()->write("Gbuffer is not initialized");
	}

	Scene tmp = scene;

	m_gbuffer->BindForWriting();

	Shader program = m_programs.find(Model_Geometry)->second;
	program.useProgram();

	program.setSampler(0, "sampler");

	for(auto i : tmp.Models())
	{
		program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "pvw_matrix");
		program.setMatrix4(i->getWorldMatrix(), "world");

		auto vao = tmp.getVAOs(i->getMesh());

		unsigned counter = 0;

		for(auto j : vao)
		{
			glBindVertexArray(j.getVAO());

			MeshElement* element = i->getMesh()->getElements()[counter];

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, element->getTexture().getTextureId() );

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element->getIBO().getIBO() );

			if(element->getIBO().getType() == UNSIGNED_INT)
				glDrawElements(GL_TRIANGLES, element->getIBO().getSize(), GL_UNSIGNED_INT, (void*)0);
			else
				glDrawElements(GL_TRIANGLES, element->getIBO().getSize(), GL_UNSIGNED_SHORT, (void*)0);

			counter++;
		}
	}

	program = m_programs.find(Terrain_Geometry)->second;
	program.useProgram();

	program.setField( Terrain::maxHeight, "height");
	program.setSampler( 10, "heightmap" );
	program.setSampler( 0, "grass");
	program.setSampler( 1, "ground");
	program.setSampler( 2, "snow");

	for(auto i : tmp.Terrains())
	{
		program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "pvw_matrix");
		program.setMatrix4(i->getWorldMatrix(), "world");

		glBindVertexArray(tmp.getVAOs(i).getVAO());

		glActiveTexture(GL_TEXTURE0 + 10);
		glBindTexture(GL_TEXTURE_2D, i->getHeightmap().getTextureId());
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, i->getTexture(0).getTextureId());
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, i->getTexture(1).getTextureId());
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, i->getTexture(2).getTextureId());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i->getIBO().getIBO());

		if(i->getIBO().getType() == UNSIGNED_INT)
			glDrawElements(GL_TRIANGLES, i->getIBO().getSize(), GL_UNSIGNED_INT, (void*)0);
		else
			glDrawElements(GL_TRIANGLES, i->getIBO().getSize(), GL_UNSIGNED_SHORT, (void*)0);
	}
}

void Renderer::addProgram(const ProgramType& type, const Shader& shader)
{
	m_programs.insert(std::pair<ProgramType, Shader>(type, shader));
}