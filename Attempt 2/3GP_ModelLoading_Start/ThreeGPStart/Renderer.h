#pragma once

#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Mesh.h"
#include "Camera.h"
#include "Terrain.h"
#include "Model.h"
#include "Skybox.h"

class Renderer
{
private:
	glm::mat4 projection_xform = glm::mat4(1.0);

	GLuint m_program = 0;
	GLuint tex = 0;

	bool CreateProgram();
public:
	std::vector<Model*> modelVector;

	Renderer()=default;
	~Renderer();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	void InitRender();
	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);
};

