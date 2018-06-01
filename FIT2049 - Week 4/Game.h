/*	FIT2049 - Example Code
*	Game.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class is the heart of our game and is also where our game logic will reside
*	It contains the overall Update and Render method for the whole game
*	You should eventually split some game logic into other objects which Game will manage
*	Watch the size of this class - it can grow out of control very fast!
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "Camera.h"
#include "InputController.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "FollowCamera.h"
#include "Logic.h"
#include <vector>
#include "TexturedShader.h"
#include <time.h>
#include "FirstPersonCamera.h"

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "DirectXTK/CommonStates.h"

class Game
{
private:
	Camera* m_currentCam;
	Direct3D* m_renderer;
	InputController* m_input;
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	FirstPersonCamera* m_playerCam;
	Camera* m_skyCam;
	Logic* logic;
	Player* player;

	SpriteBatch* m_spriteBatch;
	SpriteFont* m_arialFont12;
	SpriteFont* m_arialFont18;

	Texture* m_healthSprite;

	Shader* m_unlitVertexColouredShader;
	Shader* m_unlitTexturedShader;
	std::vector< std::vector<GameObject*> > m_map;

	std::wstring m_distanceTravelledText;
	std::wstring m_scoreText;

	bool InitShaders();
	bool LoadMeshes();
	bool LoadTextures();
	void LoadFonts();
	void InitGameWorld();

	void InitUI();
	void DrawUI();
	void RefreshUI();

public:
	Game();	
	~Game();

	bool Initialise(Direct3D* renderer, InputController* input); //The initialise method will load all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();					//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn
	void Shutdown(); //Cleanup everything we initialised
};

#endif