#include "MyMesh.h"

bool MyMesh::Load(std::string filename, std::string imgFilename, GLuint tex, glm::vec3 posTransfrom)
{
	Helpers::ModelLoader loader;
	if (!loader.LoadFromFile(filename))
		return false;

	loader.GetMeshVector();

	Helpers::ImageLoader imageLoader;
	if (!imageLoader.Load(imgFilename))
		return false;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageLoader.Width(), imageLoader.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageLoader.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	// Creates VBOs and VAO
	for (const Helpers::Mesh& mesh : loader.GetMeshVector())
	{
		GLuint positionsVBO;
		glGenBuffers(1, &positionsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

		GLuint normalsVBO;
		glGenBuffers(1, &normalsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.normals.size(), mesh.normals.data(), GL_STATIC_DRAW);

		GLuint elementsEBO;
		glGenBuffers(1, &elementsEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.elements.size(), mesh.elements.data(), GL_STATIC_DRAW);

		GLuint texVBO;
		glGenBuffers(1, &texVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.uvCoords.size(), mesh.uvCoords.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mesh_VAO);
		glBindVertexArray(mesh_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsEBO);

		mesh_numElements = mesh.elements.size();
		mesh_tex = tex;

		model_xform = glm::translate(model_xform, posTransfrom);

		glBindVertexArray(0);
	}

	return true;
}

bool MyMesh::LoadTerrain(std::string filename, GLuint tex)
{
	Terrain newTerrain;
	newTerrain.CreateMesh();

	Helpers::ImageLoader terrainImageLoader;
	if (!terrainImageLoader.Load(filename))
		return false;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, terrainImageLoader.Width(), terrainImageLoader.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, terrainImageLoader.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	// Creates VBOs and VAO
	GLuint terrainPosVBO;
	glGenBuffers(1, &terrainPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, terrainPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * newTerrain.vertices.size(), newTerrain.vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint terrainElementsEBO;
	glGenBuffers(1, &terrainElementsEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainElementsEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * newTerrain.elements.size(), newTerrain.elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint normalsVBO;
	glGenBuffers(1, &normalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * newTerrain.normals.size(), newTerrain.normals.data(), GL_STATIC_DRAW);

	GLuint texVBO;
	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * newTerrain.uvcoords.size(), newTerrain.uvcoords.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &mesh_VAO);
	glBindVertexArray(mesh_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, terrainPosVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainElementsEBO);

	// Good idea to check for an error now:	
	Helpers::CheckForGLError();

	mesh_numElements = newTerrain.elements.size();
	mesh_tex = tex;

	// Clear VAO binding
	glBindVertexArray(0);

	return true;
}

//CLAMP NEEDS TO BE DONE
bool MyMesh::LoadSkybox(std::string filename, GLuint tex, std::vector<MyMesh>& meshVector)
{
	std::vector<std::string> skyboxImgVector =
	{
		//"Data\\Sky\\Mountains\\6.jpg",
		//"Data\\Sky\\Mountains\\4.jpg",
		//"Data\\Sky\\Mountains\\2.jpg",
		//"Data\\Sky\\Mountains\\1.jpg",
		//"Data\\Sky\\Mountains\\3.jpg",
		//"Data\\Sky\\Mountains\\5.jpg",

		"Data\\Sky\\Hills\\skybox_top.jpg",
		"Data\\Sky\\Hills\\skybox_front.jpg",
		"Data\\Sky\\Hills\\skybox_back.jpg",
		"Data\\Sky\\Hills\\skybox_left.jpg",
		"Data\\Sky\\Hills\\skybox_right.jpg",
		"Data\\Sky\\Hills\\skybox_bottom.jpg",
	};

	Helpers::ModelLoader loader;
	if (!loader.LoadFromFile(filename))
		return false;

	loader.GetMeshVector();

	int i = 0;

	// Creates VBOs and VAO
	for (const Helpers::Mesh& mesh : loader.GetMeshVector())
	{
		Helpers::ImageLoader imageLoader;
		if (!imageLoader.Load(skyboxImgVector[i]))
			return false;

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageLoader.Width(), imageLoader.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageLoader.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		i++;

		GLuint positionsVBO;
		glGenBuffers(1, &positionsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

		GLuint normalsVBO;
		glGenBuffers(1, &normalsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.normals.size(), mesh.normals.data(), GL_STATIC_DRAW);

		GLuint elementsEBO;
		glGenBuffers(1, &elementsEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.elements.size(), mesh.elements.data(), GL_STATIC_DRAW);

		GLuint texVBO;
		glGenBuffers(1, &texVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.uvCoords.size(), mesh.uvCoords.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint tempVAO;
		glGenVertexArrays(1, &tempVAO);
		glBindVertexArray(tempVAO);

		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, texVBO);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsEBO);

		MyMesh tempMesh;
		tempMesh.mesh_VAO = tempVAO;
		tempMesh.mesh_numElements = mesh.elements.size();
		tempMesh.mesh_tex = tex;
		meshVector.push_back(tempMesh);

		glBindVertexArray(0);
	}

	return true;
}