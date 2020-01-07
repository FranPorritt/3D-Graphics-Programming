#version 330

uniform sampler2D sampler_tex;
//uniform vec3 cameraPos;
uniform int light;
//uniform float materialShininess;

in vec3 varying_normal;
in vec3 varying_position;
in vec2 texCoord;

out vec4 fragment_colour;

void main(void)
{	
	vec3 lightPos = vec3(-300, 1250, -500);
	vec3 texColour = texture(sampler_tex, texCoord).rgb;
	vec3 lightColour = vec3(0.8,0.6,0.4);
	float lightRange = 6500.0f;

	vec3 fragPos = varying_position;
	vec3 lightDirection = fragPos - lightPos;

	vec3 L = normalize(lightPos - fragPos);
	vec3 N = normalize(varying_normal);
	float diffuseIntensity = max(0, dot(L,N));
	vec3 diffuseColour = texColour * diffuseIntensity;

	vec3 reflectedLight = texColour * diffuseIntensity;

	float lightDistance = distance(lightPos, fragPos);
	float attenuation = 1.0 - smoothstep(0, lightRange, lightDistance);

	vec3 ambientColour = texColour * lightColour;

	// Doesn't affect skybox
	if (light == 1)
	{
		vec3 finalColour = ambientColour + lightColour * diffuseColour * attenuation;

		fragment_colour = vec4(finalColour, 1); 
		
	}
	else
	{		
		vec3 finalColour = texColour;

		fragment_colour = vec4(finalColour, 1); 
	}
}