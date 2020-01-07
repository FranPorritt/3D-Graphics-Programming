#include "Model.h"

void Model::Load(std::string filename, std::string imgFilename, GLuint tex, glm::vec3 posTransfrom)
{
	MyMesh newMesh;
	newMesh.Load(filename, imgFilename, tex, posTransfrom);
	meshVector.push_back(newMesh);
	modelPos = posTransfrom;
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
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	combined_xform = projection_xform * view_xform;

	GLuint combined_xform_id = glGetUniformLocation(m_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));

	GLuint light_id = glGetUniformLocation(m_program, "light");
	glUniform1i(light_id, 1);

	for (auto& mesh : meshVector)
	{
		//glm::mat4 transform = glm::translate(mesh.model_xform, glm::vec3(modelPos));
		//mesh.model_xform = glm::translate(mesh.model_xform, modelPos);

		GLuint model_xform_id = glGetUniformLocation(m_program, "model_xform");
		glUniformMatrix4fv(model_xform_id, 1, GL_FALSE, glm::value_ptr(mesh.model_xform));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.mesh_tex);
		glUniform1i(glGetUniformLocation(m_program, "sampler_tex"), 0);

		glBindVertexArray(mesh.mesh_VAO);
		glDrawElements(GL_TRIANGLES, mesh.mesh_numElements, GL_UNSIGNED_INT, (void*)0);
	}

	// Always a good idea, when debugging at least, to check for GL errors
	Helpers::CheckForGLError();
}

//void Model::Movement(const float& x, const float& y, const float& z)
//{
//	modelPos.x += x;
//	modelPos.y += y;
//	modelPos.z += z;
//}