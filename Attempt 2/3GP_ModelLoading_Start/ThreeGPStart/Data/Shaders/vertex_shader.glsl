#version 330

uniform mat4 combined_xform;
uniform mat4 model_xform;
uniform sampler2D sampler_tex;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 TexCoord;

out vec4 varying_normal;
out vec2 texCoord;

void main(void)
{
	vec4 normal_transform = model_xform * vec4(vertex_normal, 0);
	varying_normal = (normal_transform + 1) / 2;
	texCoord = TexCoord;

	gl_Position = combined_xform * model_xform * vec4(vertex_position, 1.0); 
}