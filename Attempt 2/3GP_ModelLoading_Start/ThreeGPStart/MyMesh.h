#pragma once
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "Mesh.h"
#include "ImageLoader.h"
#include "Terrain.h"

class MyMesh
{
public:
	GLuint mesh_VAO{ 0 };
	GLuint mesh_numElements{ 0 };
	GLuint mesh_tex;

	bool Load(std::string filename, std::string imgFilename, GLuint tex);
	bool LoadTerrain(std::string filename, GLuint tex);
	bool LoadSkybox(std::string filename, std::string imgFilename, GLuint tex);
};

