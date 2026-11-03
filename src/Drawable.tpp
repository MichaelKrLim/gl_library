template <is_Mesh Mesh>
Drawable<Mesh>::Drawable(Mesh mesh, Texture texture) noexcept
	:	mesh(std::move(mesh))
	,	texture(std::move(texture))
{}

template <is_Mesh Mesh>
void Drawable<Mesh>::draw() noexcept
{
	texture.bind();
	mesh.draw();
}
