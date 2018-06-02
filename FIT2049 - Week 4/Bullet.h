#ifndef BULLET_H
#define BULLET_H

#include "PhysicsObject.h"
#include <vector>

class GameObject;

class Bullet : public PhysicsObject
{
private:

public:
	Bullet(Mesh* mesh, Shader* shader, Vector3 position, Texture* texture);
	~Bullet();

	void OnCollisionEnter(GameObject* object);
	void OnCollisionStay(GameObject* object);
	void OnCollisionExit(GameObject* object);

};

#endif