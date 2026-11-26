#ifndef Texture_hpp_INCLUDED
#define Texture_hpp_INCLUDED

#include <glad/glad.h>

#include <filesystem>

class Texture
{
	public:

	explicit Texture(const std::filesystem::path& path) noexcept;

	Texture& operator=(const Texture&)=delete;
	Texture(const Texture&)=delete;

	Texture& operator=(Texture&& rhs) noexcept;
	Texture(Texture&& other) noexcept;

	void bind() const noexcept { glBindTexture(GL_TEXTURE_2D, gl_id); }
	void unbind() const noexcept { glBindTexture(GL_TEXTURE_2D, 0); }
	template <std::invocable T>
	void set_params(const T& lambda) noexcept
	{
		bind();
		lambda();
		unbind();
	}
	GLint query_width() const noexcept;
	GLint query_height() const noexcept;

	private:

	unsigned gl_id;
};

#endif // Texture_hpp_INCLUDED
