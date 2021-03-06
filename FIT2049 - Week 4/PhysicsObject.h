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
	int enemey;
	int health;

	void ApplyFriction(float strength);

public:
	PhysicsObject(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);
	PhysicsObject(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, Vector3 velocity);
	PhysicsObject(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, int e);
	virtual void Update(float timestep);

	Vector3 GetVelocity() { return m_velocity; }

	virtual void OnCollisionEnter(GameObject* object);
	virtual void OnCollisionStay(GameObject* object);
	virtual void OnCollisionExit(GameObject* object);
	void SetType(char t) { type = t; };
	bool GetDel() { return del; }
	int GetEnemy() { return enemey; }
	void ApplyForce(Vector3 force);

};

#endif