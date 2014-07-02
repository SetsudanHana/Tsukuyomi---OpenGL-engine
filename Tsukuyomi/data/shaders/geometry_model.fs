#version 400

layout(location = 0) in vec2 TexCoord;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 WorldPos;

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

uniform sampler2D sampler;  

void main()
{
	vec4 texel = texture(sampler, TexCoord);
	WorldPosOut = WorldPos; 
	DiffuseOut = texel.xyz;
	NormalOut = normalize(Normal);
	TexCoordOut = vec3(TexCoord, 0.0);
}