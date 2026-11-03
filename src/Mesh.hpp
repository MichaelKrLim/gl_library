#ifndef Vertex_array_object_hpp_INCLUDED
#define Vertex_array_object_hpp_INCLUDED

#include <glad/glad.h>

#include <span>

enum class With_ebo
{
	yes, no, size
};

// please use [[gnu::packed]] if possible, thanks!
template<typename Vertex_type, With_ebo uses_ebo, std::unsigned_integral Ebo_index_type>
class Mesh
{
	public:

	// the order in which you layout your attributes in memory determine the vertex attribute id passed to GLSL
	explicit Mesh(std::span<const Vertex_type> vertex_data, std::size_t draw_mode=GL_STATIC_DRAW, std::span<const Ebo_index_type> indices={}) noexcept;
	~Mesh() noexcept;

	void draw() noexcept;

	private:

	std::size_t next_free_vertex_attribute=0;
	unsigned vao=0, vbo=0, ebo=0;
	std::size_t num_vertices_to_draw=0;
};

template<typename... Ts>
void detail_is_Mesh(Mesh<Ts...>) {}

template <typename T>
concept is_Mesh = requires { detail_is_Mesh(std::declval<T>()); };

#include "Mesh.tpp"

#endif // Vertex_array_object_hpp_INCLUDED
