#version 330

uniform sampler2D sampler_tex;
uniform vec3 lightPos;
uniform vec3 cameraPos;

in vec3 varying_normal;
in vec3 varying_position;
in vec2 texCoord;

out vec4 fragment_colour;

void main(void)
{
	// Lighting
	vec3 light_ambient_colour = vec3(0.7, 0.8, 0.4);
	float lightRange = 8000;

	vec3 material_diffuse_colour = texture(sampler_tex, texCoord).rgb;
	vec3 fragment_position = varying_position;
	vec3 fragment_normal = normalize(varying_normal);

	vec3 material_ambient_colour = material_diffuse_colour;
	vec3 material_specular_colour = material_diffuse_colour;

	// Direction Vectors
	vec3 light_direction = normalize(lightPos - fragment_position);
	vec3 camera_direction = normalize(cameraPos - fragment_position);

	// Attenuation
	float lightDistance = distance(lightPos, fragment_position);
	float attenuation = 1.0f - smoothstep(0, lightRange, lightDistance);

	// Diffuse Colour
	float lightAmount = max(0, dot(light_direction, fragment_normal));
	vec3 diffuseColour = material_diffuse_colour * lightAmount;

	vec3 ambientColour = light_ambient_colour * material_ambient_colour;

	vec3 finalColour = (ambientColour + diffuseColour + attenuation) * material_diffuse_colour;

	vec3 norm = normalize(varying_normal);
	fragment_colour = vec4(finalColour, 1); 
}