#ifndef Drawable_hpp_INCLUDED
#define Drawable_hpp_INCLUDED

#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Texture.hpp"


// uses the model-view-projection. Local space -> World space -> View space -> Clip space
template <is_Mesh Mesh> 
class Drawable
{
	public:

	explicit Drawable(Mesh mesh, Texture texture) noexcept;

	void draw() const noexcept;
	void scale(float scale_factor) noexcept;
	glm::vec3 get_position() const noexcept;
	void set_position(const glm::vec3& new_position) noexcept;
	glm::mat4 get_model_matrix() noexcept;

	private:

	Mesh mesh;
	Texture texture;
	glm::vec3 position{0.0f};
	glm::mat4 model{1.0f}; // Local -> World
};

#include "Drawable.tpp"

#endif // Drawable_hpp_INCLUDED
