#include "Skybox.h"
#include "Model.h"

void Skybox::Draw(GLuint& m_program, glm::mat4 view_xform, glm::mat4 view_xform2, glm::mat4 projection_xform, glm::mat4 combined_xform)
{
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	combined_xform = projection_xform * view_xform2;

	GLuint combined_xform_id = glGetUniformLocation(m_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));

	GLuint light_id = glGetUniformLocation(m_program, "light");
	glUniform1i(light_id, 0);

	for (auto& mesh : meshVector)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.mesh_tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glUniform1i(glGetUniformLocation(m_program, "sampler_tex"), 0);

		if (mesh.mesh_VAO != 0) // IS LOOPING FROM 1 - 6 AND THEN GOING TO 0 -- FOR SOME REASON MESH VECTOR HAS 7 ELEMENTS WHEN IT SHOULD ONLY HAVE 6????
		{
			glBindVertexArray(mesh.mesh_VAO);
			glDrawElements(GL_TRIANGLES, mesh.mesh_numElements, GL_UNSIGNED_INT, (void*)0);
		}
	}

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	// Always a good idea, when debugging at least, to check for GL errors
	Helpers::CheckForGLError();
}