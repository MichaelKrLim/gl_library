#include <glm/gtc/matrix_transform.hpp>

#include <array>

template <is_Mesh Mesh>
Drawable<Mesh>::Drawable(Mesh mesh, Texture texture) noexcept
	:	mesh(std::move(mesh))
	,	texture(std::move(texture))
{}

template <is_Mesh Mesh>
void Drawable<Mesh>::draw() const noexcept
{
	texture.bind();
	mesh.draw();
}

template <is_Mesh Mesh>
void Drawable<Mesh>::scale(float scale_factor) noexcept
{
	// local space scale
	model = glm::scale(model, glm::vec3(scale_factor, scale_factor, scale_factor));
}

template <is_Mesh Mesh>
glm::vec3 Drawable<Mesh>::get_position() const noexcept
{
	return position;
}

template <is_Mesh Mesh>
void Drawable<Mesh>::set_position(const glm::vec3& new_position) noexcept
{
	glm::vec3 translation = -position+new_position;
	model = glm::translate(glm::mat4(1.0f),translation)*model;
	position = new_position;
}

template<is_Mesh Mesh>
glm::mat4 Drawable<Mesh>::get_model_matrix() noexcept
{
	return model;
}
