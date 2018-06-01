
#ifndef FOLLOW_CAMERA_H
#define FOLLOW_CAMERA_H

#include "Camera.h"
#include "GameObject.h"

class FollowCamera : public Camera //new camera class exstening camera, used for having a camera that tracks the player
{
private:
	GameObject* m_target;

public:
	FollowCamera(GameObject* target);

	void Update(float timestep);

	void SetTarget(GameObject* target) { m_target = target; }

};

#endif