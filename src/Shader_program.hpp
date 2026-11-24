#ifndef Shader_program_hpp_INCLUDED
#define Shader_program_hpp_INCLUDED

#include "Shader.hpp"

#include "glad/glad.h"

struct Uniform_location { unsigned location; };

class Shader_program
{
	public:

	template <Shader_type... shader_variants>
	explicit Shader_program(Shader<shader_variants>... shaders) noexcept;
	~Shader_program() noexcept;

	Shader_program& operator=(const Shader_program&)=delete;
	Shader_program(const Shader_program&)=delete;

	Shader_program& operator=(Shader_program&& rhs) noexcept;
	explicit Shader_program(Shader_program&& other) noexcept;

	void use() noexcept;

	Uniform_location get_uniform_location(std::string name) noexcept;
	void set_uniform(const Uniform_location& uniform, const auto& value) noexcept;

	private:

	unsigned gl_id=0;
};

#include "Shader_program.tpp"

#endif // Shader_program_hpp_INCLUDED
