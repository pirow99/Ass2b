#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "GameObject.h"

class PhysicsObject : public GameObject
{
protected:

	Vector3 m_velocity;
	Vector3 m_acceleration;

	float m_frictionAmount;

	bool del;
	char type;

	void ApplyForce(Vector3 force);
	void ApplyFriction(float strength);

public:
	PhysicsObject(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);
	PhysicsObject(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, Vector3 velocity);
	virtual void Update(float timestep);

	Vector3 GetVelocity() { return m_velocity; }

	virtual void OnCollisionEnter(GameObject* object);
	virtual void OnCollisionStay(GameObject* object);
	virtual void OnCollisionExit(GameObject* object);
	char GetType() { return type; };
	void SetType(char t) { type = t; };
	bool GetDel() { return del; }

};

#endif