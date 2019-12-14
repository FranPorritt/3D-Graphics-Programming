#include "Model.h"

void Model::Load(std::string filename, std::string imgFilename, GLuint tex)
{
	MyMesh newMesh;
	newMesh.Load(filename, imgFilename, tex);
	meshVector.push_back(newMesh);
}

void Model::LoadTerrain(std::string filename, GLuint tex)
{
	MyMesh newTerrain;
	newTerrain.LoadTerrain(filename, tex);
	meshVector.push_back(newTerrain);
}

void Model::LoadSkybox(std::string filename, GLuint tex)
{
	MyMesh newSkybox;
	newSkybox.LoadSkybox(filename, tex, meshVector);
	meshVector.push_back(newSkybox);
}

void Model::Draw(GLuint& m_program, glm::mat4 view_xform, glm::mat4 view_xform2, glm::mat4 projection_xform, glm::mat4 combined_xform)
{
	combined_xform = projection_xform * view_xform;

	GLuint combined_xform_id = glGetUniformLocation(m_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));

	for (auto& mesh : meshVector)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.mesh_tex);
		glUniform1i(glGetUniformLocation(m_program, "sampler_tex"), 0);

		glBindVertexArray(mesh.mesh_VAO);
		glDrawElements(GL_TRIANGLES, mesh.mesh_numElements, GL_UNSIGNED_INT, (void*)0);
	}

	// Always a good idea, when debugging at least, to check for GL errors
	Helpers::CheckForGLError();
}


