#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include "Camera.h"
#include "InputController.h"
#include "Player.h"

class FirstPersonCamera : public Camera
{
private:
	InputController* m_input;
	Vector3 m_offset;
	Player* m_player;

	float m_heading;
	float m_pitch;
	float m_rotationSpeed;

public:
	FirstPersonCamera(InputController* input, Player* player);

	void Update(float timestep);
};

#endif