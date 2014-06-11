#include "stdafx.h"

#include "Renderer.h"

Renderer::Renderer()
{
	m_ogl = 0;
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

	if(debug)
	{
		m_ogl->enableDebug();
		Logger::getInstance()->write("OpenGL Debug Enabled");
	}

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

	Scene tmp = scene;

	Shader program;

	switch (tmp.lightningType())
	{
	case NONE:

		if(m_programs.find(Model_NONE) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Model NONE");
			return;
		}

		program = m_programs.find(Model_NONE)->second;
		glUseProgram(program.getProgramme());

		program.setSampler( 0, "sampler");

		for(auto i : tmp.Models())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");

			auto vao = tmp.getVAOs(i->getMesh());

			UINT counter = 0;

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

		if(m_programs.find(Terrain_NONE) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Terrain NONE");
			return;
		}

		program = m_programs.find(Terrain_NONE)->second;
		glUseProgram(program.getProgramme());

		program.setField( Terrain::maxHeight, "height");
		program.setSampler( 10, "heightmap" );
		program.setSampler( 0, "grass");
		program.setSampler( 1, "ground");
		program.setSampler( 2, "snow");

		for(auto i : tmp.Terrains())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");

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

		break;

	case D:

		if(m_programs.find(Model_D) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Model D");
			return;
		}

		program = m_programs.find(Model_D)->second;
		glUseProgram(program.getProgramme());

		program.setSampler( 0, "sampler");
		program.setVector3( tmp.getCamera()->getPosition(), "viewPos");
		program.setVector3( tmp.Lights().front()->getDirection(), "lightDir");
		program.setVector3( tmp.Lights().front()->getColor(), "lightColor");
		program.setVector3( Light::m_ambient, "lightAmbient");
		program.setField( tmp.Lights().front()->getSpecularPower(), "specularPower");
		program.setField( tmp.Lights().front()->getShiness(), "specularShiness");

		for(auto i : tmp.Models())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");
			program.setMatrix4(i->getWorldMatrix(), "matWorld");
			program.setMatrix4(glm::inverse(glm::transpose(i->getWorldMatrix())), "invTransMatrix");

			auto vao = tmp.getVAOs(i->getMesh());

			UINT counter = 0;

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

		if(m_programs.find(Terrain_D) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Terrain D");
			return;
		}

		program = m_programs.find(Terrain_D)->second;
		glUseProgram(program.getProgramme());

		program.setField( Terrain::maxHeight, "height");
		program.setSampler( 10, "heightmap" );
		program.setSampler( 0, "grass");
		program.setSampler( 1, "ground");
		program.setSampler( 2, "snow");
		program.setVector3( tmp.getCamera()->getPosition(), "viewPos");
		program.setVector3( tmp.Lights().front()->getDirection(), "lightDir");
		program.setVector3( tmp.Lights().front()->getColor(), "lightColor");
		program.setVector3( Light::m_ambient, "lightAmbient");
		program.setField( tmp.Lights().front()->getSpecularPower(), "specularPower");
		program.setField( tmp.Lights().front()->getShiness(), "specularShiness");

		for(auto i : tmp.Terrains())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");
			program.setMatrix4(i->getWorldMatrix(), "matWorld");
			program.setMatrix4(glm::inverse(glm::transpose(i->getWorldMatrix())), "invTransMatrix");

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
		break;
	
	case P:

		if(m_programs.find(Model_P) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Model P");
			return;
		}

		program = m_programs.find(Model_P)->second;
		glUseProgram(program.getProgramme());

		program.setSampler( 0, "sampler");
		program.setVector3( tmp.getCamera()->getPosition(), "viewPos");
		program.setVector3( tmp.Lights().front()->getPosition(), "lightPos");
		program.setVector3( tmp.Lights().front()->getColor(), "lightColor");
		program.setVector3( Light::m_ambient, "lightAmbient");
		program.setField( tmp.Lights().front()->getRadius(), "lightRadius");
		program.setField( tmp.Lights().front()->getSpecularPower(), "specularPower");
		program.setField( tmp.Lights().front()->getShiness(), "specularShiness");

		for(auto i : tmp.Models())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");
			program.setMatrix4(i->getWorldMatrix(), "matWorld");
			program.setMatrix4(glm::inverse(glm::transpose(i->getWorldMatrix())), "invTransMatrix");

			auto vao = tmp.getVAOs(i->getMesh());

			UINT counter = 0;

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

		if(m_programs.find(Terrain_P) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Terrain P");
			return;
		}

		program = m_programs.find(Terrain_P)->second;
		glUseProgram(program.getProgramme());

		program.setField( Terrain::maxHeight, "height");
		program.setSampler( 10, "heightmap" );
		program.setSampler( 0, "grass");
		program.setSampler( 1, "ground");
		program.setSampler( 2, "snow");
		program.setVector3( tmp.getCamera()->getPosition(), "viewPos");
		program.setVector3( tmp.Lights().front()->getPosition(), "lightPos");
		program.setVector3( tmp.Lights().front()->getColor(), "lightColor");
		program.setVector3( Light::m_ambient, "lightAmbient");
		program.setField( tmp.Lights().front()->getRadius(), "lightRadius");
		program.setField( tmp.Lights().front()->getSpecularPower(), "specularPower");
		program.setField( tmp.Lights().front()->getShiness(), "specularShiness");

		for(auto i : tmp.Terrains())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");
			program.setMatrix4(i->getWorldMatrix(), "matWorld");
			program.setMatrix4(glm::inverse(glm::transpose(i->getWorldMatrix())), "invTransMatrix");

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
		break;

	case S:

		if(m_programs.find(Model_S) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Model S");
			return;
		}

		program = m_programs.find(Model_S)->second;
		glUseProgram(program.getProgramme());

		program.setSampler( 0, "sampler");
		program.setVector3( tmp.getCamera()->getPosition(), "viewPos");
		program.setVector3( tmp.Lights().front()->getPosition(), "lightPos");
		program.setVector3( tmp.Lights().front()->getColor(), "lightColor");
		program.setVector3( Light::m_ambient, "lightAmbient");
		program.setVector3( tmp.Lights().front()->getDirection(), "spotDir");
		program.setField(glm::cos(tmp.Lights().front()->getInner() * DAG2RAD), "cosInner");
		program.setField(glm::cos(tmp.Lights().front()->getOuter() * DAG2RAD), "cosOuter");
		program.setField( tmp.Lights().front()->getRadius(), "lightRadius");
		program.setField( tmp.Lights().front()->getSpecularPower(), "specularPower");
		program.setField( tmp.Lights().front()->getShiness(), "specularShiness");

		for(auto i : tmp.Models())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");
			program.setMatrix4(i->getWorldMatrix(), "matWorld");
			program.setMatrix4(glm::inverse(glm::transpose(i->getWorldMatrix())), "invTransMatrix");

			auto vao = tmp.getVAOs(i->getMesh());

			UINT counter = 0;

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

		if(m_programs.find(Terrain_S) == m_programs.end())
		{
			Logger::getInstance()->write("No matching shader for set: Terrain S");
			return;
		}

		program = m_programs.find(Terrain_S)->second;
		glUseProgram(program.getProgramme());

		program.setField( Terrain::maxHeight, "height");
		program.setSampler( 10, "heightmap" );
		program.setSampler( 0, "grass");
		program.setSampler( 1, "ground");
		program.setSampler( 2, "snow");
		program.setVector3( tmp.getCamera()->getPosition(), "viewPos");
		program.setVector3( tmp.Lights().front()->getPosition(), "lightPos");
		program.setVector3( tmp.Lights().front()->getColor(), "lightColor");
		program.setVector3( Light::m_ambient, "lightAmbient");
		program.setVector3( tmp.Lights().front()->getDirection(), "spotDir");
		program.setField(glm::cos(tmp.Lights().front()->getInner() * DAG2RAD), "cosInner");
		program.setField(glm::cos(tmp.Lights().front()->getOuter() * DAG2RAD), "cosOuter");
		program.setField( tmp.Lights().front()->getRadius(), "lightRadius");
		program.setField( tmp.Lights().front()->getSpecularPower(), "specularPower");
		program.setField( tmp.Lights().front()->getShiness(), "specularShiness");

		for(auto i : tmp.Terrains())
		{
			program.setMatrix4(tmp.getCamera()->getProjectionMatrix() * tmp.getCamera()->getViewMatrix() * i->getWorldMatrix(), "matrix");
			program.setMatrix4(i->getWorldMatrix(), "matWorld");
			program.setMatrix4(glm::inverse(glm::transpose(i->getWorldMatrix())), "invTransMatrix");

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
		break;

	default:
		break;
	}

}

void Renderer::addProgram(const ProgramType& type, const Shader& shader)
{
	m_programs.insert(std::pair<ProgramType, Shader>(type, shader));
}