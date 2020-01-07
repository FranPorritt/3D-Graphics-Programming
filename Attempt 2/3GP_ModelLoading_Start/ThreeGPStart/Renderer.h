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
	std::vector<Model*> modelVector;

	glm::mat4 projection_xform;

	GLuint m_program = 0;
	GLuint tex = 0;

	bool CreateProgram();
public:
	Renderer()=default;
	~Renderer();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	void InitRender();
	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);
};

