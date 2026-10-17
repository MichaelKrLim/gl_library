#include <print>
#include <string>

template <Shader_type... shader_variants>
Shader_program::Shader_program(Shader<shader_variants>... shaders) noexcept
	:	gl_id(glCreateProgram())
{
	template for(const auto& shader : {shaders...})
		glAttachShader(gl_id, shader.gl_id);

	glLinkProgram(gl_id);
	int success;
	glGetProgramiv(gl_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		GLint buffer_size=0;
		glGetProgramiv(gl_id, GL_INFO_LOG_LENGTH, &buffer_size);
		std::string error_message(buffer_size, ' ');
		glGetProgramInfoLog(gl_id, buffer_size, NULL, error_message.data());
		std::println(stderr, "Error linking shader: {}", error_message);
	}
}

Shader_program::~Shader_program() noexcept
{
	glDeleteProgram(gl_id);
}

Shader_program& Shader_program::operator=(Shader_program&& rhs) noexcept
{
	if(gl_id!=0)
		glDeleteProgram(gl_id);

	gl_id=rhs.gl_id;
	return *this;
}

Shader_program::Shader_program(Shader_program&& other) noexcept
{
	gl_id=other.gl_id;
}

void Shader_program::use() noexcept
{
	glUseProgram(gl_id);
}
