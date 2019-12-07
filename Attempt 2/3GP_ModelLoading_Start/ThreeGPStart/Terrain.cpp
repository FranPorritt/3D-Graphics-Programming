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
	for (int elemIndex = 0; elemIndex < elements.size(); elemIndex += 3)
	{
		glm::vec3 vertex0 = vertices[elements[elemIndex]];		// Vertex position at first indice of triangle
		glm::vec3 vertex1 = vertices[elements[elemIndex + 1]];
		glm::vec3 vertex2 = vertices[elements[elemIndex + 2]];

		glm::vec3 norm = glm::cross((vertex1 - vertex0), (vertex2 - vertex0));

		for (auto& normal : normals)
		{
			normal += norm;
		}
	}

	// Normalize normals
	for (auto& normal : normals)
	{
		glm::normalize(normal);
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
			int imageX = vertexXtoImage * vertX;
			int imageZ = vertexZtoImage * vertZ;

			size_t offset = ((size_t)imageX + (size_t)imageZ * mapLoader.Width()) * 4;
			BYTE height = mapData[offset];

			vertices[currentVertex].y = (float)height * scaling;

			currentVertex++;
		}
	}

	return true;
}

bool Terrain::Initialise()
{
	// TERRAIN

	//Helpers::ImageLoader texLoader;
	//if (!texLoader.Load("Data\\Textures\\grass11.bmp"))
	//	return false;

	//glGenTextures(1, &tex);
	//glBindTexture(GL_TEXTURE_2D, tex);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texLoader.Width(), texLoader.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texLoader.GetData());
	//glGenerateMipmap(GL_TEXTURE_2D);

	//CreateMesh();

	//GLuint terrainPosVBO;
	//glGenBuffers(1, &terrainPosVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, terrainPosVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//GLuint terrainIndicesEBO;
	//glGenBuffers(1, &terrainIndicesEBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIndicesEBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//GLuint normalsVBO;
	//glGenBuffers(1, &normalsVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);

	//GLuint texVBO;
	//glGenBuffers(1, &texVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvcoords.size(), uvcoords.data(), GL_STATIC_DRAW);

	//glGenVertexArrays(1, &m_VAO);
	//glBindVertexArray(m_VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, terrainPosVBO);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(
	//	0,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	0,
	//	(void*)0
	//);

	//glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(
	//	1,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	0,
	//	(void*)0
	//);

	//glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(
	//	2,
	//	2,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	0,
	//	(void*)0
	//);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIndicesEBO);

	//// Good idea to check for an error now:	
	//Helpers::CheckForGLError();

	//// Clear VAO binding
	//glBindVertexArray(0);

	return true;
}
