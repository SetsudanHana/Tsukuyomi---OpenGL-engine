#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <fstream>
#include <string>
#include <chrono>
#include <time.h>
#include <sstream>
#include <functional>
#include <map>
#include <vector>

#include <gl/glew.h>
#include <gl/GL.h> 

#pragma comment(lib, "opengl32.lib")	
#pragma comment(lib, "glew32.lib")

#include <SDL.h>
#include <SDL_opengl.h>

#pragma comment (lib, "SDL2.lib")

#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <FreeImage.h>

#pragma comment (lib, "FreeImage.lib")

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp.lib")