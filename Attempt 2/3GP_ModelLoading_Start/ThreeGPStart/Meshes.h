#pragma once
#include "ExternalLibraryHeaders.h"
#include "Camera.h"
#include "Helper.h"

class Meshes
{
private:
	std::string filename;
	std::string imgFilename;

	GLuint mesh_VAO = 0;
	GLuint mesh_numElements = 0;
	GLuint tex;

public:
	Meshes(std::string mesh_filename, std::string img_filename);
	~Meshes();

	bool Load();
	void Draw(const Helpers::Camera& camera, GLuint m_program);
};

