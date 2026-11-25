#include <array>

template <is_Mesh Mesh>
Drawable<Mesh>::Drawable(Mesh mesh, Texture texture) noexcept
	:	mesh(std::move(mesh))
	,	texture(std::move(texture))
{}

template <is_Mesh Mesh>
Drawable<Mesh>::Drawable(Texture texture) noexcept
	: texture(std::move(texture))
{
	struct Vertex { glm::vec2 position; };

	std::array<Vertex, 6> vertices {
		// triangle one
		Vertex{ glm::vec2{-0.5f,  0.5f} },
		Vertex{ glm::vec2{-0.5f, -0.5f} },
		Vertex{ glm::vec2{ 0.5f,  0.5f} },
		// triangle two
		Vertex{ glm::vec2{-0.5f, -0.5f} },
		Vertex{ glm::vec2{ 0.5f, -0.5f} },
		Vertex{ glm::vec2{ 0.5f,  0.5f} }
	};

	mesh=Mesh(vertices);
}

template <is_Mesh Mesh>
void Drawable<Mesh>::draw() noexcept
{
	texture.bind();
	mesh.draw();
}
