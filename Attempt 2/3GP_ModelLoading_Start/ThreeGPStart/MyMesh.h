#pragma once
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "Mesh.h"
#include "ImageLoader.h"
#include "Terrain.h"

class MyMesh
{
public:
	glm::mat4 model_xform = glm::mat4(1.0);

	GLuint mesh_VAO = 0;
	GLuint mesh_numElements = 0;
	GLuint mesh_tex = 0;

	bool Load(std::string filename, std::string imgFilename, GLuint tex, glm::vec3 posTransfrom);
	bool LoadTerrain(std::string filename, GLuint tex);
	bool LoadSkybox(std::string filename, GLuint tex, std::vector<MyMesh>& meshVector);
};

