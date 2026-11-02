#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texture_coord;

out vec4 v_color;
out vec2 v_texture_coord;

void main()
{
	gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
	v_color=a_color;
	v_texture_coord=a_texture_coord;
}
