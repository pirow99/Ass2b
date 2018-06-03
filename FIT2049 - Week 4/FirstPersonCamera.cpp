#include "FirstPersonCamera.h"
#include "MathsHelper.h"
#include <Iostream>

FirstPersonCamera::FirstPersonCamera(InputController* input, Player* player)
{
	m_input = input;
	m_player = player;
	SetPosition(player->GetPosition());
	m_rotationSpeed = 3.0f;
	m_heading = 0.0f;
	m_pitch = 0.0f;
}

void FirstPersonCamera::Update(float timestep)
{
	m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;
	m_pitch += m_input->GetMouseDeltaY() * m_rotationSpeed * timestep;
	m_player->SetForward(m_heading);

	m_pitch = MathsHelper::Clamp(m_pitch, ToRadians(-80.0f), ToRadians(80.0f));

	Matrix heading = Matrix::CreateRotationY(m_heading);
	Matrix pitch = Matrix::CreateRotationX(m_pitch);

	Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

	Vector3 currentPos = GetPosition();

	Matrix lookAtRotation = pitch * heading;

	Vector3 lookAt = Vector3::TransformNormal(Vector3(0, 0, 1), lookAtRotation);

	lookAt += currentPos;

	SetLookAt(lookAt);
	SetPosition(m_player->GetPosition() + Vector3(0, 0.7, 0));

	Camera::Update(timestep);
}

