#include "Meshes.h"
#include "Helper.h"
#include "Mesh.h"
#include "ImageLoader.h"

Meshes::Meshes(std::string mesh_filename, std::string img_filename)
{
	filename = mesh_filename;
	imgFilename = img_filename;
}

Meshes::~Meshes()
{
}

bool Meshes::Load()
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

		mesh_numElements = mesh.elements.size();
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

		GLuint mesh_VAO;

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

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}

void Meshes::Draw(const Helpers::Camera& camera, GLuint m_program)
{
	// Configure pipeline settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// TODO: Compute viewport and projection matrix
	GLint viewportSize[4];
	glGetIntegerv(GL_VIEWPORT, viewportSize);
	const float aspect_ratio = viewportSize[2] / (float)viewportSize[3];
	glm::mat4 projection_xform = glm::perspective(glm::radians(45.0f), aspect_ratio, 1.0f, 2000.0f);

	// TODO: Compute camera view matrix and combine with projection matrix for passing to shader
	glm::mat4 view_xform = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetLookVector(), camera.GetUpVector());
	glm::mat4 combined_xform = projection_xform * view_xform;

	glUseProgram(m_program);

	// TODO: Send the combined matrix to the shader in a uniform
	GLuint combined_xform_id = glGetUniformLocation(m_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));

	glm::mat4 model_xform = glm::mat4(1);

	// Send the model matrix to the shader in a uniform
	GLuint model_xform_id = glGetUniformLocation(m_program, "model_xform");
	glUniformMatrix4fv(model_xform_id, 1, GL_FALSE, glm::value_ptr(model_xform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(m_program, "sampler_tex"), 0);

	// TODO: render each mesh. Send the correct model matrix to the shader in a uniform
	glBindVertexArray(mesh_VAO);
	glDrawElements(GL_TRIANGLES, mesh_numElements, GL_UNSIGNED_INT, (void*)0);

	// Always a good idea, when debugging at least, to check for GL errors
	Helpers::CheckForGLError();
}