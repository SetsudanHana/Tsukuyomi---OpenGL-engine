#version 400
layout(location = 1) in vec3 vertex_position;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_normals;

uniform mat4 pvw_matrix;
uniform mat4 world;

layout(location = 0) out vec2 texture_coords;
layout(location = 1) out vec3 normals;
layout(location = 2) out vec3 world_pos;

void main()
{
	vec4 tmp = (world * vec4(vertex_normals, 0.0));
	normals = tmp.xyz;
	tmp = (world * vec4(vertex_position, 1.0));
	world_pos = tmp.xyz;
	texture_coords = vertex_texture;
	gl_Position = pvw_matrix * vec4( vertex_position, 1.0 );
}