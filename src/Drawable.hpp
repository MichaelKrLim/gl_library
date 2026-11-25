#ifndef Drawable_hpp_INCLUDED
#define Drawable_hpp_INCLUDED

#include "Mesh.hpp"
#include "Texture.hpp"

template <is_Mesh Mesh> 
class Drawable
{
	public:

	explicit Drawable(Mesh mesh, Texture texture) noexcept;
	explicit Drawable(Texture texture) noexcept;

	void draw() noexcept;

	private:

	Mesh mesh;
	Texture texture;
};

#include "Drawable.tpp"

#endif // Drawable_hpp_INCLUDED
