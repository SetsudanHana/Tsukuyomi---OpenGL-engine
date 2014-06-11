#version 400

in vec2 texture_coords;

uniform sampler2D sampler;

out vec4 colour;

void main()
{
	vec4 texel = texture2D( sampler, texture_coords );
	colour = texel;
}