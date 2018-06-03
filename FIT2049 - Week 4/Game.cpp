/*	FIT2049 - Example Code
*	Game.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*/

#include "Game.h"
#include <sstream>

using namespace std;

const int mapSize = 20; //const that is used for determing size of the map

Game::Game() //constructor that sets all pointers to null
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_meshManager = NULL;
	m_textureManager = NULL;
	m_unlitTexturedShader = NULL;
	m_unlitVertexColouredShader = NULL;
	m_playerCam = NULL;
	m_skyCam = NULL;
	m_collisionManager = NULL;
}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input) //initialise everything
{
	m_renderer = renderer;	
	m_input = input;
	m_meshManager = new MeshManager();
	m_textureManager = new TextureManager();
	m_skyCam = new Camera(); // creates a new camera that is used for a birds eye view
	m_skyCam->SetPosition(Vector3((float)mapSize / 2, 30.0f, (float)mapSize / 2));
	m_skyCam->SetLookAt(Vector3((float)mapSize / 2, 0.0f, ((float)mapSize / 2) + 0.01f)); //perfectly aligned camera caused world to not render so + 0.01f
	srand(time(NULL)); //seed random



	if (!InitShaders())
		return false;

	if (!LoadMeshes())
		return false;

	if (!LoadTextures())
		return false;


	InitGameWorld();
	LoadFonts();
	InitUI();
	RefreshUI();

	return true;
}

bool Game::InitShaders()
{
	m_unlitVertexColouredShader = new Shader();
	if (!m_unlitVertexColouredShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/VertexColourPixelShader.ps"))
		return false;
	
	m_unlitTexturedShader = new TexturedShader();
	if (!m_unlitTexturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
		return false;

	return true;
}

void Game::InitUI()
{
	m_spriteBatch = new SpriteBatch(m_renderer->GetDeviceContext());

	m_healthSprite = m_textureManager->GetTexture("Assets/Textures/sprite_healthBar.png");
}

bool Game::LoadMeshes()
{
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/floor_tile.obj")) return false;
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/player_capsule.obj")) return false;
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/wall_tile.obj")) return false;
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/enemy.obj")) return false;
	
	return true;
}

bool Game::LoadTextures()
{
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_white.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_reder.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_redest.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_green.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_blue.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_disabled.png")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/checkerboard.jpg")) return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/sprite_healthBar.png")) return false;

	return true;
}

void Game::LoadFonts()
{
	m_arialFont12 = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-12pt.spritefont");
	m_arialFont18 = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-18pt.spritefont");
}

void Game::RefreshUI()
{
	if (player)
	{
		std::wstringstream ss;

		ss << "Distance Travelled: " << player->GetMoveCount();

		m_distanceTravelledText = ss.str();

		std::wstringstream ss2;

		ss2 << "Score: " << player->GetKillCount();

		m_scoreText = ss2.str();
	
	}
}

void Game::InitGameWorld()
{
	player = new Player(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"), m_unlitTexturedShader, m_input, Vector3(1.0f, 0.0f, 1.0f), m_textureManager->GetTexture("Assets/Textures/tile_disabled.png")); //Create player object

	collisionObjects = new vector<PhysicsObject*>;

	staticObjects = new vector<GameObject*>;

	collisionObjects->push_back(player);

	for (int i = 0; i < mapSize; i++)	//Create a map of gameobjects 
	{
		vector<GameObject*> temp;
		for (int j = 0; j < mapSize; j++)
		{
			if (j == 0 || i == 0 || i == mapSize - 1 || j == mapSize - 1) //checks to see if gameobject is on the edge of the map and if so makes it a wall
			{
				temp.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"), m_unlitTexturedShader, Vector3((float)i, -0.5f, (float)j), m_textureManager->GetTexture("Assets/Textures/tile_disabled.png")));
				staticObjects->push_back(temp.back());
			}
			else
			{
				temp.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"), m_unlitTexturedShader, Vector3((float)i, 0.0f, (float)j), m_textureManager->GetTexture("Assets/Textures/tile_white.png"), m_meshManager, m_textureManager, m_unlitTexturedShader));
			}
		}
		m_map.push_back(temp);
	}

	logic = new Logic(m_textureManager, m_meshManager, m_map, player, staticObjects); //logic class is created, used to make the game class less messy. Created as a class instead of a library of functions so that I dont have to pass m_textureManager, m_meshManager, m_map, player to every function

	for (int i = 0; i < mapSize * 3 / 4; i++) //creates a random amount of walls in the map at random positions
	{
		int x = (rand() % (mapSize - 5)) + 3;
		int y = (rand() % (mapSize - 5)) + 3;

		switch (rand() % 8)
		{
		case 0:
			logic->MakeWall(m_map[x + 1][y]);
			logic->MakeWall(m_map[x - 1][y]);
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x][y + 1]);
			logic->MakeWall(m_map[x][y - 1]);
			break;
		case 1:
			logic->MakeWall(m_map[x + 1][y + 1]);
			logic->MakeWall(m_map[x + 1][y]);
			logic->MakeWall(m_map[x + 1][y - 1]);
			logic->MakeWall(m_map[x][y + 1]);
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x][y - 1]);
			logic->MakeWall(m_map[x - 1][y + 1]);
			logic->MakeWall(m_map[x - 1][y]);
			logic->MakeWall(m_map[x - 1][y - 1]);
			break;
		case 2:
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x + 1][y + 1]);
			logic->MakeWall(m_map[x][y + 1]);
			logic->MakeWall(m_map[x + 1][y]);
			break;
		case 3:
			logic->MakeWall(m_map[x][y]);
			break;
		case 4:
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x][y + 1]);
			break;
		case 5:
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x + 1][y]);
			break;
		case 6:
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x + 1][y]);
			logic->MakeWall(m_map[x + 2][y]);
			break;
		case 7:
			logic->MakeWall(m_map[x][y]);
			logic->MakeWall(m_map[x][y + 1]);
			logic->MakeWall(m_map[x][y + 2]);
			break;
		default:
			break;
		}
	}

	for (int i = 1; i < mapSize; i++) //adds blue and green tiles to the map
	{
		for (int j = 1; j < mapSize; j++)
		{
			if (logic->WhiteTile(i, j) && rand() % 20 == 0)
			{
				m_map[i][j]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_green.png"));
				m_map[i][j]->SetMesh(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"));
				m_map[i][j]->Check();
				m_map[i][j]->SetZRotation(PI / 2);
				m_map[i][j]->SetUniformScale(0.9);
				m_map[i][j]->SetPosition(Vector3(m_map[i][j]->GetPosition().x + 0.45, m_map[i][j]->GetPosition().y + 0.2, m_map[i][j]->GetPosition().z));
			}
			else if (logic->WhiteTile(i, j) && rand() % 25 == 0)
			{
				m_map[i][j]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_blue.png"));
				logic->SetTele(i, j);
			}
		}
	}

	for (int i = 0; i < 5;) //creates the enemy tiles
	{
		bool temp = true;
		int tempX;
		int tempY;
		while (temp)
		{
			tempX = (rand() % (mapSize - 2)) + 1;
			tempY = (rand() % (mapSize - 2)) + 1;
			if (logic->WhiteTile(tempX, tempY) && !(tempX == 1 && tempY == 1))
			{
				if (i < 3) //makes 3 of the easy enemies and one of the other two
				{
					m_map[tempX][tempY]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_red.png"));
					m_map[tempX][tempY]->SetMesh(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"));
					m_map[tempX][tempY]->Check();
					i++;
					temp = false;
				}
				else if (i < 4)
				{
					m_map[tempX][tempY]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_reder.png"));
					m_map[tempX][tempY]->SetMesh(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"));
					m_map[tempX][tempY]->Check();
					i++;
					temp = false;
				}
				else if (i < 5)
				{
					m_map[tempX][tempY]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_redest.png"));
					m_map[tempX][tempY]->SetMesh(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"));
					m_map[tempX][tempY]->Check();
					i++;
					temp = false;
				}
			}
		}
	}

	//m_playerCam = new FollowCamera(player); //creates the camera that follows the player
	m_playerCam = new FirstPersonCamera(m_input, player);
	m_currentCam = m_playerCam; // sets that camera as the camera to render from
	m_collisionManager = new CollisionManager(staticObjects, collisionObjects);

}

void Game::Update(float timestep)
{
	m_input->BeginUpdate();
	
	if (m_input->GetKeyDown('Q'))
	{
		Vector3 worldForward = Vector3(0, 0, 1);

		Matrix heading = Matrix::CreateRotationY(player->GetHeading());

		Vector3 localForward = Vector3::TransformNormal(worldForward, heading);

		PhysicsObject* temp = new PhysicsObject(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"), m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/tile_red.png"), Vector3(player->GetPosition().x, 0.5f, player->GetPosition().y) + localForward * 2, localForward * 0.1);

		collisionObjects->push_back(temp);
	}

	for (int i = 0; i < staticObjects->size(); i++)
	{
		(*staticObjects)[i]->Update(timestep);
	}

	if (m_input->GetKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (player->GetXScale() < 0.4f) //checks to see if the player has enough health
	{
		logic->SetGameOver(true);
	}
	if (logic->GetGameOver()) //Ends the game if gameover is triggered
	{
		cout << "Score: " << player->GetKillCount() << endl;
		cout << "Distance Covered: " << player->GetMoveCount() << endl;
		MessageBox(NULL, "You Lose! See Console for stats.", "Game Over", MB_OK);
		PostQuitMessage(0);
	}
	if (player->GetKillCount() >= 8) //checks to see if the player has won the game
	{
		cout << "Score: " << player->GetKillCount() << endl;
		cout << "Distance Covered: " << player->GetMoveCount() << endl;
		MessageBox(NULL, "You Win! See Console for stats.", "Winner", MB_OK);
		PostQuitMessage(0);
	}
	logic->TileChange(); //checks the tile that the player is currently on and acts accordingly
	logic->playerFlashing(); //makes the player flash when they are one hit away from dead
	player->Update(timestep, logic); //updates the player

	for (int i = 0; i < m_map.size(); i++) //updates the map
	{
		for (int j = 0; j < m_map.size(); j ++)
		{
			m_map[i][j]->UpdateTile(timestep, player->GetPosition());
		}
	}

	RefreshUI();

	if (m_input->GetKeyHold('M')) //if M is being held changes the camera to the over head view
	{
		m_currentCam = m_skyCam;
	}
	else
	{
		m_currentCam = m_playerCam;
	}
	m_currentCam->Update(timestep); //Updates the camera currently being used

	m_collisionManager->CheckCollisions();

	for (int i = 0; i < collisionObjects->size(); i++)
	{
		if ((*collisionObjects)[i]->GetDel() == true)
		{
			delete (*collisionObjects)[i];
			collisionObjects->erase(collisionObjects->begin() + i);
		}
	}

	m_input->EndUpdate();
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);
	
//	player->Render(m_renderer, m_currentCam); //renders the player mesh
	
	for (int i = 0; i < m_map.size(); i++) //renders the map
	{
		for (int j = 0; j < m_map.size(); j++)
		{
			m_map[i][j]->Render(m_renderer, m_currentCam);
		}
	}

	for (int i = 0; i < collisionObjects->size(); i++)
	{
		if ((*collisionObjects)[i]->GetType == 'b' || 'e')
		{
			(*collisionObjects)[i]->Render(m_renderer, m_currentCam);
		}
	}

	DrawUI();

	m_renderer->EndScene();		
}

void Game::DrawUI()
{
	m_renderer->SetCurrentShader(NULL);

	CommonStates states(m_renderer->GetDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	m_arialFont18->DrawString(m_spriteBatch, m_distanceTravelledText.c_str(), Vector2(500, 10), Color(1.0f, 1.0f, 1.0f), 0, Vector2(0,0));

	m_arialFont18->DrawString(m_spriteBatch, m_scoreText.c_str(), Vector2(500, 30), Color(1.0f, 1.0f, 1.0f), 0, Vector2(0, 0));

	for (int i = 0; player->GetXScale() - i * 0.08 > 0.4; i++)
	{
		m_spriteBatch->Draw(m_healthSprite->GetShaderResourceView(), Vector2(0 + 32 * i, 700), Color(1.0f, 0.0f, 0.0f));
	}
	
	m_spriteBatch->End();
}

void Game::Shutdown()
{
	for (int i = 0; i < mapSize; i++) //Deletes the map
	{
		for (int j = 0; j < mapSize; j++)
		{
			delete m_map[i][j];
		}
	}

	m_map.empty();
	//deltes all other pointers
	delete m_playerCam;
	delete m_skyCam;
	m_playerCam = NULL;
	m_skyCam = NULL;
	m_currentCam = NULL;
	delete logic;
	logic = NULL;
	delete player;
	player = NULL;


	if (m_unlitVertexColouredShader)
	{
		m_unlitVertexColouredShader->Release();
		delete m_unlitVertexColouredShader;
		m_unlitVertexColouredShader = NULL;
	}

	if (m_meshManager)
	{
		m_meshManager->Release();
		delete m_meshManager;
		m_meshManager = NULL;
	}

	if (m_textureManager)
	{
		m_textureManager->Release();
		delete m_textureManager;
		m_textureManager = NULL;
	}
}
