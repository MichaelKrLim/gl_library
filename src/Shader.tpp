#include <glad/glad.h>
#include <mio/mmap.hpp>

#include <print>
#include <system_error>
#include <utility>

template <Shader_type shader_variant>
Shader<shader_variant>::Shader(const std::filesystem::path& path) noexcept
	:	gl_id(glCreateShader(std::to_underlying(shader_variant)))
{
	std::error_code error;
	mio::mmap_source shader_source;
	shader_source.map(path.string(), error);
	if(error) { std::println(stderr, "Error in shader path ({}): {}", path, error.message()); }
	auto pointer=shader_source.data();
	GLint size=shader_source.size();
	glShaderSource(gl_id, 1, &pointer, &size);

	int success;
	glCompileShader(gl_id);
	glGetShaderiv(gl_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		GLint buffer_size=0;
		glGetShaderiv(gl_id, GL_INFO_LOG_LENGTH, &buffer_size);
		std::string error_message(buffer_size, ' ');
		glGetShaderInfoLog(gl_id, buffer_size, NULL, error_message.data());
		std::println(stderr, "Error compiling shader at '{}': {}", path, error_message);
	}
}

template <Shader_type shader_variant>
Shader<shader_variant>::~Shader() noexcept
{
	glDeleteShader(gl_id);
}

template <Shader_type shader_variant>
Shader<shader_variant>& Shader<shader_variant>::operator=(Shader&& other) noexcept
{
	if(gl_id!=0)
		glDeleteShader(gl_id);

	gl_id=other.gl_id;
}

template <Shader_type shader_variant>
Shader<shader_variant>::Shader(Shader&& other) noexcept
{
	gl_id=other.gl_id;
}
