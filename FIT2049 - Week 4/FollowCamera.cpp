#include "FollowCamera.h"

FollowCamera::FollowCamera(GameObject * target) //Constructor for new camera that is passed a gameobject to track
{
	m_target = target;
	SetLookAt(m_target->GetPosition());
}

void FollowCamera::Update(float timestep) //new update function that changes the positions of the camera relative to the tartget
{
	Camera::Update(timestep);
	SetPosition(m_target->GetPosition() += Vector3(0.0f, 5.0f, -8.0f));
	SetLookAt(m_target->GetPosition());
}
