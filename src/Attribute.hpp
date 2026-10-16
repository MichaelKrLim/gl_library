#ifndef Attribute_hpp_INCLUDED
#define Attribute_hpp_INCLUDED

#include <cstdint>
#include <span>

template<typename Attribute>
struct Attribute_span
{
	std::span<const Attribute> attributes;
	std::uint8_t components_per_attribute;
};

#endif // Attribute_hpp_INCLUDED
