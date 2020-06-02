#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include "../../ECS/System.hpp"
#include "../../Coordinator.hpp"
#include "Camera.hpp"

class CameraController : public System
{
public:
	void Init(Coordinator* coordinator, Camera* camera);
	void Update();

private:
	Coordinator* _coordinator;
	Camera* _worldCamera;
};

#endif