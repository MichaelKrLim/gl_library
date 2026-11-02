#include <glad/glad.h>

#include <filesystem>

class Texture
{
	public:

	explicit Texture(const std::filesystem::path& path) noexcept;

	void bind() noexcept { glBindTexture(GL_TEXTURE_2D, gl_id); }
	void unbind() noexcept { glBindTexture(GL_TEXTURE_2D, 0); }
	template <typename unnamable>
	void set_params(const unnamable& lambda)
	{
		bind();
		lambda();
		unbind();
	}

	private:

	unsigned gl_id;
};
