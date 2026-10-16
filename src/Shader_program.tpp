#include <print>
#include <string>

template <std::size_t... shader_variants>
Shader_program::Shader_program(Shader<shader_variants>... shaders) noexcept
	:	gl_id(glCreateProgram())
{
	template for(const auto& shader : {shaders...})
		glAttachShader(gl_id, shader.gl_id);

	int success;
	std::string error_message(512, ' ');
	glLinkProgram(gl_id);
	glGetProgramiv(gl_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(gl_id, 512, NULL, error_message.data());
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
