#include "Skybox.h"
#include "Model.h"

void Skybox::Draw(GLuint& m_program, glm::mat4 view_xform)
{
	/*glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glm::mat4 view_xform2 = glm::mat4(glm::mat3(view_xform));	*/

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