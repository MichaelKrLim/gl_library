#ifndef Shader_program_hpp_INCLUDED
#define Shader_program_hpp_INCLUDED

#include "Shader.hpp"

#include "glad/glad.h"

class Shader_program
{
	public:

	template <std::size_t... shader_variants>
	explicit Shader_program(Shader<shader_variants>... shaders) noexcept;
	~Shader_program() noexcept;

	Shader_program& operator=(const Shader_program&)=delete;
	Shader_program(const Shader_program&)=delete;

	Shader_program& operator=(Shader_program&& rhs) noexcept;
	explicit Shader_program(Shader_program&& other) noexcept;

	void use() noexcept;

	private:

	unsigned gl_id=0;
};

#include "Shader_program.tpp"

#endif // Shader_program_hpp_INCLUDED
