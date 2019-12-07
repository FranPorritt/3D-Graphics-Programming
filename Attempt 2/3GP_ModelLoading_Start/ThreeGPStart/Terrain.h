#pragma once
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "ImageLoader.h"
#include "Camera.h"
#include <vector>

class Terrain
{
public:
	// Vertex positions on terrain
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec3> normals;
	std::vector <glm::vec2> uvcoords;
	std::vector <GLuint> elements;

	// Height map
	const float scaling = 0.3f;

	const int numCellsXZ = 100; // Square terrain
	const int numCellsX = numCellsXZ;
	const int numCellsZ = numCellsXZ;

	const int numVertsX = numCellsX + 1;;
	const int numVertsZ = numCellsZ + 1;;

	const int numVertices = (numCellsX * 2) + (numCellsZ * 2);;

	const int terrainSize = 1000;
	const int cellSize = terrainSize / numCellsX;

	GLuint tex;
	GLuint m_VAO = 0;
	GLuint m_numElements = 0;

	Terrain();
	~Terrain();

	void CreateMesh();
	void CreateVertices();
	void CreateTriangles();
	void CreateNormals();
	void CreateUVs();
	bool HeightMap();
	bool Initialise();
};