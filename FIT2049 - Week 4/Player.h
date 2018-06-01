#ifndef PLAYER_H
#define PLAYER_H

#include "InputController.h"
#include "GameObject.h"
#include "Logic.h"
#include <vector>

class Logic; //Predecleration to stop recursion
class GameObject;

class Player : public GameObject
{
private:
	InputController* m_input;
	float m_moveSpeed; // the players velocity
	int killCount; //the players current score from defeating enemies
	int moveCount; //how far the player has moved this game
	bool playerFlash; //used for making the player flash
	Vector3 m_targetPosition; //position the player is moving towards
	int direction;


public:
	Player(Mesh* mesh, Shader* shader, InputController* input, Vector3 position, Texture* texture);
	~Player();
	void Update(float timestep, Logic* logic);
	void SetForward(float Angle);
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMoveSpeed(float ms) { m_moveSpeed = ms; }
	Vector3 GetTarget() { return m_targetPosition; }
	void SetTarget(Vector3 t) { m_targetPosition = t; }
	int GetKillCount() { return killCount; }
	void SetKillCont(int kc) { killCount = kc; }
	void IncrementKillCount() { killCount++; }
	int GetMoveCount() { return moveCount; }
	void SetMoveCont(int kc) { moveCount = kc; }
	void IncrementMoveCount() { moveCount++; }
	int GetPlayerFlash() { return playerFlash; }
	void SetPlayerFlash(bool pf) { playerFlash = pf; }
	
};

#endif