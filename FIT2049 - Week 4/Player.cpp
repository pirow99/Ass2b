#include "Player.h"
#include <iostream>
#include <math.h>

using namespace std;

Player::Player(Mesh * mesh, Shader * shader, InputController * input, Vector3 position, Texture * texture)
{
	m_mesh = mesh;
	m_shader = shader;
	m_input = input;
	m_position = position;
	m_texture = texture;
	m_targetPosition = position;
	direction = 0;

	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);

	m_moveSpeed = 10.0f; //sets players move speed
}

Player::~Player()
{

}

void Player::Update(float timestep, Logic* logic)
{
	Vector3 temp = m_targetPosition;

	switch (direction) //Changes movement controls depending on direction the player is facing
	{
	case 0:
		if (m_input->GetKeyDown(VK_LEFT))
		{
			m_targetPosition += Vector3(-1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyDown(VK_RIGHT))
		{
			m_targetPosition += Vector3(1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyDown(VK_UP))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, 1.0f);
		}
		if (m_input->GetKeyDown(VK_DOWN))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, -1.0f);
		}
		break;
	case 1:
		if (m_input->GetKeyDown(VK_LEFT))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, 1.0f);
		}
		if (m_input->GetKeyDown(VK_RIGHT))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, -1.0f);
		}
		if (m_input->GetKeyDown(VK_UP))
		{
			m_targetPosition += Vector3(1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyDown(VK_DOWN))
		{
			m_targetPosition += Vector3(-1.0f, 0.0f, 0.0f);
		}
		break;
	case 2:
		if (m_input->GetKeyDown(VK_LEFT))
		{
			m_targetPosition += Vector3(1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyDown(VK_RIGHT))
		{
			m_targetPosition += Vector3(-1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyDown(VK_UP))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, -1.0f);
		}
		if (m_input->GetKeyDown(VK_DOWN))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, 1.0f);
		}
		break;
	case 3:
		if (m_input->GetKeyDown(VK_LEFT))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, -1.0f);
		}
		if (m_input->GetKeyDown(VK_RIGHT))
		{
			m_targetPosition += Vector3(0.0f, 0.0f, 1.0f);
		}
		if (m_input->GetKeyDown(VK_UP))
		{
			m_targetPosition += Vector3(-1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyDown(VK_DOWN))
		{
			m_targetPosition += Vector3(1.0f, 0.0f, 0.0f);
		}
		break;
	default:
		break;
	}
	if (!logic->TileCheck()) //Checks if the players is moving towards a valid position
	{
		m_targetPosition = temp; // if not sets the target position to it previous location
	}

	if (Vector3::DistanceSquared(m_position, m_targetPosition) <= 0.001f) //checks if the player has arrvied at the target position
	{
		m_moveSpeed = 0;
	}
	else //smoove movement towards the target position
	{
		m_moveSpeed = 10.0f;
		m_position = Vector3::Lerp(m_position, m_targetPosition, m_moveSpeed * timestep);
	}
}

void Player::SetForward(float Angle) //Determines what direction the player is facing
{
	float direct = fmod(Angle - PI/4, (PI * 2));
	if (direct > 0 && direct < PI / 2)
	{
		direction = 1;
	}
	else if (direct > PI / 2 && direct < PI)
	{
		direction = 2;
	}
	else if (direct > PI && direct < PI * 3 / 2)
	{
		direction = 3;
	}
	else if (direct > PI * 3 / 2)
	{
		direction = 0;
	}
	else if (direct < 0 && direct > -PI / 2)
	{
		direction = 0;
	}
	else if (direct < -PI / 2 && direct > -PI)
	{
		direction = 3;
	}
	else if (direct < -PI && direct > -PI * 3 / 2)
	{
		direction = 2;
	}
	else if (direct < -PI * 3 / 2)
	{
		direction = 1;
	}

}