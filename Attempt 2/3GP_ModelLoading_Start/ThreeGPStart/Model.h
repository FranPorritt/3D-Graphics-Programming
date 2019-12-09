#pragma once
#include <vector>
#include "MyMesh.h"
#include "Terrain.h"

class Model
{
private:
	std::vector<MyMesh> meshVector;

public:
	void Load(std::string filename, std::string imgFilename, GLuint tex);
	void LoadTerrain(std::string filename, GLuint tex);
	void LoadSkybox(std::string filename, std::string imgFilename, GLuint tex);
	void Draw(GLuint& m_program);
};

