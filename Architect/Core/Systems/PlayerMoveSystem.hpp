#ifndef PLAYERMOVESYSTEM_HPP
#define PLAYERMOVESYSTEM_HPP

#include "../ECS/System.hpp"
#include "../Coordinator.hpp"
#include "../Math/Vector2.hpp"

class PlayerMoveSystem : public System
{
public:
	void Init(Coordinator* coordinator);
	void Update();

private:
	Coordinator* _coordinator;
};

#endif