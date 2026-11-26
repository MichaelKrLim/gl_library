#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texture_coord;

out vec2 v_texture_coord;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	gl_Position = projection*view*model*vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
	v_texture_coord=a_texture_coord;
}
