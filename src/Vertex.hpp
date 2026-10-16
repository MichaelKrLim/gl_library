#ifndef Vertex_hpp_INCLUDED
#define Vertex_hpp_INCLUDED

struct [[gnu::packed]] vec3 { float x=0.0f,y=0.0f,z=0.0f; };
struct [[gnu::packed]] vec4 { float r=0.0f,g=0.0f,b=0.0f,w=0.0f; };

struct Vertex
{
	vec3 position;
	vec4 colour;
};

#endif // Vertex_hpp_INCLUDED
