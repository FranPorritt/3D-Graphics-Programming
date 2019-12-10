#pragma once
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "Mesh.h"
#include "Model.h"

class Skybox : public Model
{
public:
	void Draw(GLuint& m_program, glm::mat4 view_xform, glm::mat4 view_xform2, glm::mat4 combined_xform) override;
};

