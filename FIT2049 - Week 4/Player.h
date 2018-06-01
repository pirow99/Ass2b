#ifndef PLAYER_H
#define PLAYER_H

#include "InputController.h"
#include "GameObject.h"
#include "Logic.h"
#include "PhysicsObject.h"
#include <vector>

class Logic; //Predecleration to stop recursion
class GameObject;

class Player : public PhysicsObject
{
private:
	InputController* m_input;
	int killCount; //the players current score from defeating enemies
	int moveCount; //how far the player has moved this game
	bool playerFlash; //used for making the player flash
	float playerHeading;
	float playerMoveSpeed;

public:
	Player(Mesh* mesh, Shader* shader, InputController* input, Vector3 position, Texture* texture);
	~Player();
	void Update(float timestep, Logic* logic);
	void SetForward(float Angle);
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