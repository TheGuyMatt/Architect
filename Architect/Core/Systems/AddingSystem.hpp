#ifndef ADDINGSYSTEM_HPP
#define ADDINGSYSTEM_HPP

#include "../ECS/System.hpp"
#include "../ECS/Coordinator.hpp"

class AddingSystem : public System
{
public:
	void Init(Coordinator* coord);
	void Update(float dt);

private:
	Coordinator* coordinator;
};

#endif