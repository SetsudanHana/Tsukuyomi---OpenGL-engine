#version 400
layout(location = 0) in vec2 vertex_position;

uniform mat4 matrix;
uniform mat4 matWorld;
uniform mat4 invTransMatrix;
uniform sampler2D heightmap;
uniform float height;

layout(location = 20) out vec4 worldVertex;
layout(location = 30) out vec2 texture_coords;
layout(location = 40) out vec4 Normal;
out float layer;

void main()
{
	vec4 texel = texture2D( heightmap, vertex_position );
	texture_coords = vertex_position;
	
	float normal1 = texture2D(heightmap, (vertex_position + vec2(-1.0f, 0.0f) / 256.0f)).r;
    float normal2 = texture2D(heightmap, (vertex_position + vec2(1.0f, 0.0f) / 256.0f)).r;
    float normal3 = texture2D(heightmap, (vertex_position + vec2(0.0f, -1.0f) / 256.0f)).r;
    float normal4 = texture2D(heightmap, (vertex_position + vec2(0.0f, 1.0f) / 256.0f)).r;
    vec3 myNormal = normalize(vec3((normal1 - normal2), 0.01f, (normal3 - normal4)));
	worldVertex = matWorld * vec4( vertex_position.x, height*texel.x, vertex_position.y, 1.0 );
	Normal = invTransMatrix * vec4(myNormal, 0.0f);
	layer = texel.x;
	gl_Position = matrix * vec4( vertex_position.x, height*texel.x, vertex_position.y, 1.0 );
} 