#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{

}

void Terrain::CreateMesh()
{
	CreateVertices();
	CreateTriangles();
	CreateNormals();
	CreateUVs();
	HeightMap();
}

void Terrain::CreateVertices()
{
	glm::vec3 startPos(-terrainSize / 2, 0, terrainSize / 2);

	for (int cellZ = 0; cellZ < numVertsZ; cellZ++)
	{
		for (int cellX = 0; cellX < numVertsX; cellX++)
		{
			glm::vec3 vertPos = startPos;

			vertPos.x += cellX * cellSize;
			vertPos.z -= cellZ * cellSize;

			vertices.push_back(vertPos);
		}
	}
}

void Terrain::CreateTriangles()
{
	bool toggleDiamond = true;

	for (int cellZ = 0; cellZ < numCellsZ; cellZ++)
	{
		for (int cellX = 0; cellX < numCellsX; cellX++)
		{
			int startVert = cellZ * numVertsX + cellX;

			if (!toggleDiamond)
			{
				// Triangle 1
				elements.push_back(startVert);
				elements.push_back(startVert + 1);
				elements.push_back(startVert + numVertsX + 1);

				//Triangle 2
				elements.push_back(startVert);
				elements.push_back(startVert + numVertsX + 1);
				elements.push_back(startVert + numVertsX);
			}
			else
			{
				elements.push_back(startVert);
				elements.push_back(startVert + 1);
				elements.push_back(startVert + numVertsX);

				elements.push_back(startVert + 1);
				elements.push_back(startVert + numVertsX + 1);
				elements.push_back(startVert + numVertsX);
			}
			toggleDiamond = !toggleDiamond;
		}
		toggleDiamond = !toggleDiamond;
	}
}

void Terrain::CreateNormals()
{
	// Creates normals
	for (int posIndex = 0; posIndex < vertices.size(); posIndex++)
	{
		glm::vec3 normal = glm::vec3(0, 0, 0);
		normals.push_back(normal);
	}

	// Calculate face normal
	for (GLuint elemIndex = 0; elemIndex < elements.size(); elemIndex += 3)
	{
		GLuint index1 = elements[elemIndex];
		GLuint index2 = elements[elemIndex + 1];
		GLuint index3 = elements[elemIndex + 2];

		glm::vec3 vertex0 = vertices[index1];		// Vertex position at first indice of triangle, ect.
		glm::vec3 vertex1 = vertices[index2];
		glm::vec3 vertex2 = vertices[index3];

		glm::vec3 norm = glm::normalize(glm::cross((vertex1 - vertex0), (vertex2 - vertex0)));

		normals[index1] += norm;
		normals[index2] += norm;
		normals[index3] += norm;
	}

	for (auto& normal : normals)
	{
		normal = glm::normalize(normal);
	}
}

void Terrain::CreateUVs()
{
	for (int cellZ = 0; cellZ < numVertsZ; cellZ++)
	{
		for (int cellX = 0; cellX < numVertsX; cellX++)
		{
			glm::vec2 uv = glm::vec2(((float)cellX * cellSize / numCellsX), ((float)cellZ * cellSize / numCellsZ));
			uvcoords.push_back(uv);
		}
	}
}

bool Terrain::HeightMap()
{
	Helpers::ImageLoader mapLoader;
	if (!mapLoader.Load("Data\\Textures\\curvy.gif"))
		return false;

	GLbyte* mapData = mapLoader.GetData();

	const float vertexXtoImage = (float)mapLoader.Width() / numVertsX;
	const float vertexZtoImage = (float)mapLoader.Height() / numVertsZ;

	int currentVertex = 0;
	for (int vertZ = 0; vertZ < numVertsZ; vertZ++)
	{
		for (int vertX = 0; vertX < numVertsX; vertX++)
		{
			float imageX = vertexXtoImage * vertX;
			float imageZ = vertexZtoImage * vertZ;

			size_t offset = ((size_t)imageX + (size_t)imageZ * mapLoader.Width()) * 4;
			BYTE height = mapData[offset];

			vertices[currentVertex].y = (float)height * scaling;

			currentVertex++;
		}
	}

	return true;
}