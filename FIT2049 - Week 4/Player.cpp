#include "Player.h"
#include <iostream>
#include <math.h>

using namespace std;

Player::Player(Mesh * mesh, Shader * shader, InputController * input, Vector3 position, Texture * texture) : PhysicsObject(mesh, shader, texture, position)
{
	m_input = input;
	playerHeading = 0;
	playerMoveSpeed = 0.001f;

	m_frictionAmount = 0.08f;

	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);
}

Player::~Player()
{

}

void Player::Update(float timestep, Logic* logic)
{
	Vector3 worldForward = Vector3(0, 0, 1);

	Matrix heading = Matrix::CreateRotationY(playerHeading);

	Vector3 localForward = Vector3::TransformNormal(worldForward, heading);

	if (m_input->GetKeyHold('W'))
	{
		ApplyForce(localForward * playerMoveSpeed);
	}

	if (m_input->GetKeyHold('D'))
	{
		heading = Matrix::CreateRotationY(PI / 2);
		localForward = Vector3::TransformNormal(localForward, heading);
		ApplyForce(localForward * playerMoveSpeed);
	}

	if (m_input->GetKeyHold('A'))
	{
		heading = Matrix::CreateRotationY(-PI / 2);
		localForward = Vector3::TransformNormal(localForward, heading);
		ApplyForce(localForward * playerMoveSpeed);
	}

	if (m_input->GetKeyHold('S'))
	{
		ApplyForce(localForward * -playerMoveSpeed);
	}

	PhysicsObject::Update(timestep);
}

void Player::SetForward(float Angle) //Determines what direction the player is facing
{
	playerHeading = Angle;
}

void Player::OnCollisionEnter(GameObject* object)
{
	m_velocity = (Vector3(object->GetPosition().x, 0, object->GetPosition().z) - m_position) * -0.05;
}

void Player::OnCollisionStay(GameObject* object)
{
	m_velocity = (Vector3(object->GetPosition().x, 0, object->GetPosition().z) - m_position) * -0.05;
}

void Player::OnCollisionExit(GameObject* object)
{
}