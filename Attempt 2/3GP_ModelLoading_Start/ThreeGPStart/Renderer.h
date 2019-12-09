#pragma once

#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Mesh.h"
#include "Camera.h"
#include "Terrain.h"
#include "Model.h"

//struct MyMesh
//{
//	GLuint mesh_VAO{ 0 };
//	GLuint mesh_numElements{ 0 };
//	GLuint mesh_tex;
//};

class Renderer
{
private:
	//std::vector<MyMesh> meshVector;
	std::vector<Model> modelVector;

	GLuint m_program{ 0 };
	GLuint tex;

	bool CreateProgram();
public:
	Renderer()=default;
	~Renderer();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);
};

