#version 400

in vec2 texture_coords;
in float layer;

uniform sampler2D grass;
uniform sampler2D ground;
uniform sampler2D snow;

out vec4 colour;

void main()
{
	vec4 texel;

	if( layer < 0.22 )
	{
		texel = texture2D( grass, texture_coords );
	}
	else if( layer < 0.66 )
	{
		texel = texture2D( ground, texture_coords );
	}
	else
	{
		texel = texture2D( snow, texture_coords );
	}
	colour = texel;
}