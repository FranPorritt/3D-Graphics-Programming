#version 330

uniform sampler2D sampler_tex;

in vec4 varying_normal;
in vec2 texCoord;

out vec4 fragment_colour;

void main(void)
{
	vec4 norm = normalize(varying_normal);

	fragment_colour = vec4(texture(sampler_tex, texCoord).rgb * norm.y, 0.5); 
}