#pragma once
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "Mesh.h"
#include "Model.h"

class Skybox : public Model
{
public:
	void Draw(GLuint& m_program, glm::mat4 view_xform) override;
};

