#ifndef PLAYERMOVE_HPP
#define PLAYERMOVE_HPP

#include "../../ECS/System.hpp"
#include "../../Coordinator.hpp"
#include "../../Math/Vector2.hpp"

class PlayerMove : public System
{
public:
	void Init(Coordinator* coordinator);
	void Update();

private:
	Coordinator* _coordinator;
};

#endif