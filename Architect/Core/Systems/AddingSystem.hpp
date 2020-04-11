#ifndef ADDINGSYSTEM_HPP
#define ADDINGSYSTEM_HPP

#include "../ECS/System.hpp"
#include "../ECS/Coordinator.hpp"

class AddingSystem : public System
{
public:
	void Init(Coordinator* coordinator);
	void Update(float dt);

private:
	Coordinator* _coordinator;
};

#endif