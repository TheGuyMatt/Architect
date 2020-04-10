#ifndef ADDINGSYSTEM_HPP
#define ADDINGSYSTEM_HPP

#include "../ECS/System.hpp"

class AddingSystem : public System
{
public:
	void Init();
	void Update(float dt);
};

#endif