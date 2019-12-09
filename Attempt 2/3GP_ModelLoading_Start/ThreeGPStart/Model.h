#pragma once
#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Camera.h"
#include <vector>
#include "MyMesh.h"
#include "Skybox.h"
#include "Terrain.h"

class Model
{
private:
	std::vector<MyMesh> meshVector;
	Skybox newSkybox;

public:
	void Load(std::string filename, std::string imgFilename, GLuint tex);
	void LoadTerrain(std::string filename, GLuint tex);
	void LoadSkybox(std::string filename, GLuint tex);
	void Draw(GLuint& m_program);
};

