#pragma once
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "ImageLoader.h"
#include "Camera.h"
#include <vector>

class Terrain
{
protected:
	// Height map
	const float scaling = 6.0f;

	const int numCellsXZ = 250;
	const int numCellsX = numCellsXZ;
	const int numCellsZ = numCellsXZ;

	const int numVertsX = numCellsX + 1;;
	const int numVertsZ = numCellsZ + 1;;

	const int numVertices = (numCellsX * 2) + (numCellsZ * 2);;

	const int terrainSize = 12000;
	const int cellSize = terrainSize / numCellsXZ;

public:
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec3> normals;
	std::vector <glm::vec2> uvcoords;
	std::vector <GLuint> elements;
	
	Terrain();
	~Terrain();

	void CreateMesh();
	void CreateVertices();
	void CreateTriangles();
	void CreateNormals();
	void CreateUVs();
	bool HeightMap();
};