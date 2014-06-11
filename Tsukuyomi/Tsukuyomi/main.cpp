#include "stdafx.h"

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "EventCatcher.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"
#include "MeshFactory.h"
#include "TerrainFactory.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	Window wnd;
	wnd.createWindow();
	Renderer renderer;
	renderer.init(&wnd, true);

	float time = 0.0f;

	Input input;

	EventCatcher eventCatcher;

	eventCatcher.setInput(&input);

	bool end = false;

	input.setFunctionOnKeyDown([&end](){
		end = true;
	}, SDL_GetScancodeFromKey(SDLK_ESCAPE));

	ShaderFactory shader_factory;

	Shader shader = shader_factory.createShader("test_direction");

	renderer.addProgram(Model_D, shader);

	Shader terrain_none = shader_factory.createShader("terrain_direction");

	renderer.addProgram(Terrain_D, terrain_none);

	Scene scene;

	Camera camera;
	camera.setPosition(glm::vec3(180.0, 340.0, 420.0));
	camera.setAlfa(180.0f);

	scene.setCamera(&camera);

	MeshFactory mesh_factory;

	Mesh* mesh = mesh_factory.createMesh("dwarf.x");

	Model dwarf;
	dwarf.scale(glm::vec3(1.0f));
	dwarf.translate(glm::vec3(180.0, 310.0, 420.0));
	dwarf.setMesh(mesh);

	scene.addModel(&dwarf);
	
	Light light(DIRECTION_LIGHT);

	light.setPosition(glm::vec3(180.0f, 400.0f, 420.0f));
	light.setInner( 20.0f );
	light.setOuter( 35.0f );
	light.setRadius( 1000.0f );
	light.setColor(glm::vec3(1.0f));
	light.setDirection( glm::vec3(0.0f, -1.0f, 0.0f));
	light.m_ambient = glm::vec3( 0.0f );
	light.setShiness( 100.0f );
	light.setSpecularPower( 0.05f );

	scene.addLight(&light);
	
	TerrainFactory terrainFactory;

	Terrain terrain = terrainFactory.createTerrain("heightmap.jpg", 1000);

	terrain.translate(glm::vec3(-0.5f, 0.0f, -0.5f));
	terrain.scale(glm::vec3(1000.0f));

	scene.addTerrain(&terrain);

	input.setFunctionOnKeyDown([&camera, &time]()
		{
			camera.setBeta(camera.getBeta()-time*40.0f);
	}, SDL_GetScancodeFromKey(SDLK_UP));

	input.setFunctionOnKeyDown([&camera, &time]()
	{
		camera.setBeta(camera.getBeta()+time*40.0f);
	}, SDL_GetScancodeFromKey(SDLK_DOWN));

	input.setFunctionOnKeyDown([&camera, &time]()
	{
		camera.setAlfa(camera.getAlfa()+time*40.0f);
	}, SDL_GetScancodeFromKey(SDLK_RIGHT));

	input.setFunctionOnKeyDown([&camera, &time]()
	{
		camera.setAlfa(camera.getAlfa()-time*40.0f);
	}, SDL_GetScancodeFromKey(SDLK_LEFT));

	input.setFunctionOnKeyDown([&camera, &time]()
	{
		camera.setPosition(camera.getPosition()+time*40*camera.direction());
	}, SDL_GetScancodeFromKey(SDLK_w));

	input.setFunctionOnKeyDown([&camera, &time]()
	{
		camera.setPosition(camera.getPosition()-time*40*camera.direction());
	}, SDL_GetScancodeFromKey(SDLK_s));

	while(!end)
	{

		end = eventCatcher.catchEvents();

		input.execKeysDown();

		auto start = std::chrono::system_clock::now();

		renderer.clear(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

		renderer.render(scene);

		renderer.swap(wnd);

		auto finish = std::chrono::system_clock::now();

		time = 0.000001f * std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

	}

	delete mesh;

	BufferDeleter::instance()->release();
	TextureDeleter::instance()->release();
	ShaderDeleter::instance()->release();

	return 0;
}