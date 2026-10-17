#include <concepts>
#include <meta>

template<typename Vertex_type, With_ebo uses_ebo, std::unsigned_integral Ebo_index_type>
Vertex_array_object<Vertex_type, uses_ebo, Ebo_index_type>::Vertex_array_object(std::span<const Vertex_type> vertices, std::size_t draw_mode, std::span<const Ebo_index_type> indices) noexcept
		:	next_free_vertex_attribute(0)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), draw_mode);

	template for(constexpr std::meta::info member_info : std::define_static_array(std::meta::nonstatic_data_members_of(^^Vertex_type, std::meta::access_context::unchecked())))
	{
		glVertexAttribPointer(next_free_vertex_attribute, size_of(member_info)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offset_of(member_info).bytes));
		glEnableVertexAttribArray(next_free_vertex_attribute++);
	}

	if constexpr(uses_ebo==With_ebo::yes)
	{
		num_vertices_to_draw=indices.size();

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Ebo_index_type)*indices.size(), indices.data(), draw_mode);
	}
	else
		num_vertices_to_draw=vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	if constexpr(uses_ebo==With_ebo::yes) // we only want to unbind the ebo after the vao
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template<typename Vertex_type, With_ebo uses_ebo, std::unsigned_integral Ebo_index_type>
Vertex_array_object<Vertex_type, uses_ebo, Ebo_index_type>::~Vertex_array_object() noexcept
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

template<typename Vertex_type, With_ebo uses_ebo, std::unsigned_integral Ebo_index_type>
void Vertex_array_object<Vertex_type, uses_ebo, Ebo_index_type>::draw() noexcept
{
	glBindVertexArray(vao);
	if constexpr(uses_ebo==With_ebo::yes)
		glDrawElements(GL_TRIANGLES, num_vertices_to_draw, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, num_vertices_to_draw);
}
