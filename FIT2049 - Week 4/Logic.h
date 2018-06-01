#ifndef LOGIC_H
#define LOGIC_H

#include "MeshManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Player; //predecleration of the player class to stop recursion

class Logic
{
private:
	TextureManager* m_texture;
	MeshManager* m_mesh;
	Player* m_player;
	vector<vector<GameObject*>> m_map;
	vector<Vector3> teleLocation; //vector of locations that the player can teleport to
	Vector3 PrePos; // the last valid position the player was on
	bool gameOver; //is the game still going

public:
	Logic(TextureManager* texture, MeshManager* mesh, vector< vector<GameObject*> > &map, Player* player);
	~Logic();
	void TileChange();
	bool TileCheck();
	void MakeWall(GameObject * Object);
	void SetTele(float x, float z);
	bool WhiteTile(int x, int z);
	bool GetGameOver() { return gameOver; }
	void SetGameOver(bool go) { gameOver = go; }
	void playerFlashing();
};

#endif