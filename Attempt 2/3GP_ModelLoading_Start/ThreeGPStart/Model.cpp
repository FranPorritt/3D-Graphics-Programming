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
	newSkybox.LoadSkybox(filename, tex);
}

void Model::Draw(GLuint& m_program)
{
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


