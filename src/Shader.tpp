#include <mio/mmap.hpp>

#include <print>
#include <system_error>

template <std::size_t shader_variant>
Shader<shader_variant>::Shader(const std::filesystem::path& path) noexcept
	:	gl_id(glCreateShader(shader_variant))
{
	std::error_code error;
	mio::mmap_source shader_source;
	shader_source.map(path.string(), error);
	if(error) { std::println(stderr, "Error in shader path ({}): {}", path, error.message()); }
	auto pointer=shader_source.data();
	glShaderSource(gl_id, 1, &pointer, NULL);

	int success;
	std::string error_message(512, ' ');
	glCompileShader(gl_id);
	glGetShaderiv(gl_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(gl_id, 512, NULL, error_message.data());
		std::println(stderr, "Error compiling shader at '{}': {}", path, error_message);
	}
}

template <std::size_t shader_variant>
Shader<shader_variant>::~Shader() noexcept
{
	glDeleteShader(gl_id);
}

template <std::size_t shader_variant>
Shader<shader_variant>& Shader<shader_variant>::operator=(Shader&& other) noexcept
{
	if(gl_id!=0)
		glDeleteShader(gl_id);

	gl_id=other.gl_id;
}

template <std::size_t shader_variant>
Shader<shader_variant>::Shader(Shader&& other) noexcept
{
	gl_id=other.gl_id;
}
