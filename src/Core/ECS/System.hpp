#ifndef SYSTEM_HPP
#define SYSTEM_HPP

//https://austinmorlan.com/posts/entity_component_system/

#include "Types.hpp"
#include <set>


class System
{
public:
	std::set<Entity> mEntities;
};

#endif