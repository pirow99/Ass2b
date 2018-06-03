#include "PhysicsObject.h"

using namespace std;

PhysicsObject::PhysicsObject(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) : GameObject(mesh, shader, position, texture)
{
	m_velocity = Vector3::Zero;
	m_acceleration = Vector3::Zero;
	del = false;
	type = 'p';
	health = 100;
}

PhysicsObject::PhysicsObject(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, Vector3 velocity) : GameObject(mesh, shader, position, texture)
{
	m_velocity = velocity;
	m_acceleration = Vector3::Zero;
	del = false;
	type = 'b';
	health = 100;
}

PhysicsObject::PhysicsObject(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, int e) : GameObject(mesh, shader, position, texture)
{
	m_velocity = Vector3::Zero;
	m_acceleration = Vector3::Zero;
	del = false;
	type = 'e';
	enemey = e;
	if (e == 1)
	{
		health = 100;
		m_frictionAmount = 0.08f;
	}
	else if (e == 2)
	{
		health = 150;
		m_frictionAmount = 0.0f;
	}
	else
	{
		health = 200;
		m_frictionAmount = 0.08f;
	}
}

void PhysicsObject::Update(float timestep)
{
	// Apply friction every frame
	ApplyFriction(m_frictionAmount);

	// Acceleration trickles down into velocity
	m_velocity += m_acceleration;

	// Velocity trickles down into position
	m_position += m_velocity;

	// Reset acceleration each frame so it doesn't accumulate
	m_acceleration = Vector3::Zero;

	GameObject::Update(timestep);

	if (m_position.Distance(m_position, Vector3(15,0,15)) > 30)
	{
		del = true;
	}

	if (enemey == 3)
	{

	}
}

void PhysicsObject::OnCollisionEnter(GameObject * object)
{
	if (type == 'b')
	{
		del = true;
	}
	if (type == 'e')
	{
		if (object->GetType() == 'b')
		{
			health = health - 25;
			m_velocity = (Vector3(object->GetPosition().x, 0, object->GetPosition().z) - m_position) * -0.05;
			if (enemey == 2)
			{
				m_velocity = (Vector3(object->GetPosition().x, 0, object->GetPosition().z) - m_position) * -0.03;
			}
		}
		if (health < 1)
		{
			del = true;
		}
	}
}

void PhysicsObject::OnCollisionStay(GameObject * object)
{
	m_velocity = (Vector3(object->GetPosition().x, 0, object->GetPosition().z) - m_position) * -0.05;
}

void PhysicsObject::OnCollisionExit(GameObject * object)
{
}

void PhysicsObject::ApplyForce(Vector3 force)
{
	// You could take mass into account here if you want to get fancy
	m_acceleration += force;
}

void PhysicsObject::ApplyFriction(float strength)
{
	// Force in opposite direction to velocity
	ApplyForce(-m_velocity * strength);
}
