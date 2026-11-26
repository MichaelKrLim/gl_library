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

Texture::Texture(Texture&& other) noexcept
{
	gl_id=other.gl_id;
	other.gl_id=0;
}

Texture& Texture::operator=(Texture&& rhs) noexcept
{
	glDeleteTextures(1, &gl_id);
	gl_id=rhs.gl_id;
	rhs.gl_id=0;
	return *this;
}

GLint Texture::query_width() const noexcept
{
	bind();
	GLint width;

	GLint base_image_mipmap_level=0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, base_image_mipmap_level, GL_TEXTURE_WIDTH, &width);
	unbind();

	return width;
}

GLint Texture::query_height() const noexcept
{
	bind();
	GLint height;

	GLint base_image_mipmap_level=0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, base_image_mipmap_level, GL_TEXTURE_HEIGHT, &height);
	unbind();

	return height;
}
