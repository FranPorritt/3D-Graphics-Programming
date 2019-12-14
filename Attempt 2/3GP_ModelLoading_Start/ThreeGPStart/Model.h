#pragma once
#include "ExternalLibraryHeaders.h"

#include <vector>
#include "Helper.h"
#include "Camera.h"
#include "MyMesh.h"
#include "Terrain.h"

class Model
{
protected:
	std::vector<MyMesh> meshVector;

public:
	void Load(std::string filename, std::string imgFilename, GLuint tex);
	void LoadTerrain(std::string filename, GLuint tex);
	void LoadSkybox(std::string filename, GLuint tex);
	virtual void Draw(GLuint& m_program, glm::mat4 view_xform, glm::mat4 view_xform2, glm::mat4 projection_xform, glm::mat4 combined_xform);
};

