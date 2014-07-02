#version 400
layout(location = 1) in vec3 vertex_position;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_normals;

uniform mat4 matrix;
uniform mat4 matWorld;
uniform mat4 invTransMatrix;

layout(location = 20) out vec4 worldVertex;
layout(location = 30) out vec2 texture_coords;
layout(location = 40) out vec4 Normal;

void main () {
  texture_coords = vertex_texture;
  worldVertex = matWorld * vec4(vertex_position, 1.0);
  Normal = invTransMatrix * vec4(vertex_normals, 0.0f);
  gl_Position = matrix * vec4(vertex_position, 1.0);
}