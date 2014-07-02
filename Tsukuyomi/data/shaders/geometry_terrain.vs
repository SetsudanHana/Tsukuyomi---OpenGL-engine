#version 400
layout(location = 0) in vec2 vertex_position;

uniform mat4 pvw_matrix;
uniform mat4 world;
uniform sampler2D heightmap;
uniform float height;

layout(location = 0) out vec2 texture_coords;
layout(location = 1) out vec3 normals;
layout(location = 2) out vec3 world_pos;
layout(location = 3) out float layer;

void main()
{
	vec4 texel = texture2D( heightmap, vertex_position );
	texture_coords = vertex_position;
	
	float normal1 = texture2D(heightmap, (vertex_position + vec2(-1.0f, 0.0f) / 256.0f)).r;
    	float normal2 = texture2D(heightmap, (vertex_position + vec2(1.0f, 0.0f) / 256.0f)).r;
    	float normal3 = texture2D(heightmap, (vertex_position + vec2(0.0f, -1.0f) / 256.0f)).r;
    	float normal4 = texture2D(heightmap, (vertex_position + vec2(0.0f, 1.0f) / 256.0f)).r;
    	vec3 myNormal = normalize(vec3((normal1 - normal2), 0.01f, (normal3 - normal4)));
	
	vec4 tmp = (world * vec4(myNormal, 0.0));
	
	normals = tmp.xyz;
	tmp = (world * vec4( vertex_position.x, height*texel.x, vertex_position.y, 1.0 ));
	world_pos = tmp.xyz;
	
	layer = texel.x;
	gl_Position = pvw_matrix * vec4( vertex_position.x, height*texel.x, vertex_position.y, 1.0 );
}