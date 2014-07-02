#version 400

layout(location = 0) in vec2 TexCoord;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 WorldPos;
layout(location = 3) in float layer;

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

uniform sampler2D grass;
uniform sampler2D ground;
uniform sampler2D snow;

void main()
{
	vec4 texel;
	if( layer < 0.22 )
	{
		texel = texture2D( grass, TexCoord );
	}
	else if( layer < 0.66 )
	{
		texel = texture2D( ground, TexCoord );
	}
	else
	{
		texel = texture2D( snow, TexCoord );
	}

    WorldPosOut = WorldPos;
    NormalOut = normalize(Normal);
    TexCoordOut = vec3(TexCoord, 0.0);
    DiffuseOut = texel.xyz;
} 