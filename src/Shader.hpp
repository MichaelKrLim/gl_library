#ifndef Shader_hpp_INCLUDED
#define Shader_hpp_INCLUDED

#include <glad/glad.h>

#include <cstdint>
#include <filesystem>

template <std::size_t shader_variant>
class Shader
{
	public:

	explicit Shader(const std::filesystem::path& path) noexcept;
	~Shader() noexcept;

	Shader& operator=(const Shader&)=delete;
	Shader(const Shader&)=delete;

	Shader& operator=(Shader&& other) noexcept;
	explicit Shader(Shader&& other) noexcept;

	private:

	unsigned gl_id=0;

	friend class Shader_program;
};

#include "Shader.tpp"

#endif // Shader_hpp_INCLUDED
