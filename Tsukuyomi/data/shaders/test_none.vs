#version 400
layout(location = 1) in vec3 vertex_position;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_normals;

uniform mat4 matrix;

out vec2 texture_coords;

void main()
{
	texture_coords = vertex_texture;
	gl_Position = matrix * vec4( vertex_position, 1.0 );
}