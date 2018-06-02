#include "Bullet.h"

Bullet::Bullet(Mesh * mesh, Shader * shader, Vector3 position, Texture * texture) : PhysicsObject(mesh, shader, texture, position)
{
	m_frictionAmount = 0;
}

Bullet::~Bullet()
{
}

void Bullet::OnCollisionEnter(GameObject * object)
{

}

void Bullet::OnCollisionStay(GameObject * object)
{
}

void Bullet::OnCollisionExit(GameObject * object)
{
}
