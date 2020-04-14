#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../Math/Vector2f.hpp"

struct Transform
{
	Math::Vector2f position;
	Math::Vector2f previous_pos;
};

#endif