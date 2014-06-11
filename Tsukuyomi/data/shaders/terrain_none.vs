#version 400
layout(location = 0) in vec2 vertex_position;

uniform mat4 matrix;
uniform sampler2D heightmap;
uniform float height;

out vec2 texture_coords;
out float layer;
void main()
{
	vec4 texel = texture2D( heightmap, vertex_position );
	texture_coords = vertex_position;
	layer = texel.x;
	gl_Position = matrix * vec4( vertex_position.x, height*texel.x, vertex_position.y, 1.0 );
}