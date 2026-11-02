#version 330 core

in vec4 v_color;
in vec2 v_texture_coord;

out vec4 FragColor;

uniform sampler2D our_texture;

void main()
{
	FragColor = texture(our_texture, v_texture_coord);
}
