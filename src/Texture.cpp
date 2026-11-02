#include "Texture.hpp"

#include "stb_image.h"

#include <print>

Texture::Texture(const std::filesystem::path& path) noexcept
{
	glGenTextures(1, &gl_id);
	bind();

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
		std::println(stderr, "Failed to load texture");
		return;
	}

	unbind();
}
