#include "Logic.h"

Logic::Logic(TextureManager * texture, MeshManager * mesh, vector<vector<GameObject*>> &map, Player * player) //Stores pointers to variables
{
	m_texture = texture;
	m_mesh = mesh;
	m_map = map;
	m_player = player;
	gameOver = false; //set the gameover trigger to false
}

Logic::~Logic()
{

}

void Logic::TileChange() //Checks players current position on the map and acts accrodingly
{
	if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_white.png"))
	{
		m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->SetTexture(m_texture->GetTexture("Assets/Textures/tile_disabled.png"));
		m_player->IncrementMoveCount();
		PrePos = m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetPosition();
	}
	else if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_green.png"))
	{
		m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->changeWhite();
		m_player->IncrementMoveCount();
		PrePos = m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetPosition();

		if (m_player->GetXScale() < 1.0f) 
		{
			m_player->SetUniformScale(m_player->GetXScale() + 0.25f); //heal amount
			m_player->SetTexture(m_texture->GetTexture("Assets/Textures/tile_disabled.png"));
			if (m_player->GetXScale() > 1.0f) //sets the players max health
			{
				m_player->SetUniformScale(1.0f);
			}
		}
	}
	else if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_blue.png"))
	{
		m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->SetTexture(m_texture->GetTexture("Assets/Textures/tile_disabled.png"));
		m_player->IncrementMoveCount();
		if (teleLocation.size() > 1) //makes sure there is a tile to teleport to
		{
			for (int i = 0; i < teleLocation.size(); i++) //goes through the list of blue tiles and deletes the tile the player is standing on from list of possible destinations
			{
				if (int(teleLocation[i].x) == int(m_player->GetPosition().x + 0.5) && int(teleLocation[i].y) == int(m_player->GetPosition().y + 0.5))
				{
					teleLocation.erase(teleLocation.begin() + i);
				}
				else { continue; }
				break;
			}
			random_shuffle(teleLocation.begin(), teleLocation.end()); //randomises the list of possible destinations
			m_player->SetPosition(teleLocation[teleLocation.size() - 1]);// moves the player to a random blue tile
			m_player->SetTarget(teleLocation[teleLocation.size() - 1]);
			m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->SetTexture(m_texture->GetTexture("Assets/Textures/tile_disabled.png"));
			m_player->IncrementMoveCount();
			PrePos = m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetPosition();
			teleLocation.pop_back(); // delets the new tile from list of possible destinations
		}
	}
	else if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_red.png"))
	{
		m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->SetUniformScale(m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetXScale() - 0.12f); //deals damage to the enemy
		if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetXScale() < 0.5f) //if the enemy is defeated changes it to a white floor tile
		{
			m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->changeWhite();
			m_player->IncrementKillCount();
		}
		m_player->SetUniformScale(m_player->GetXScale() - 0.08f); //damage that the player takes from the enemy
		m_player->SetTarget(PrePos);
	}
	//same as other red tile with numbers tweaked
	else if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_reder.png"))
	{
		m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->SetUniformScale(m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetXScale() - 0.08f);
		if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetXScale() < 0.5f)
		{
			m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->changeWhite();
			m_player->IncrementKillCount();
			m_player->IncrementKillCount();
		}
		m_player->SetUniformScale(m_player->GetXScale() - 0.08f);
		m_player->SetTarget(PrePos);
	}
	//same as other red tile with numbers tweaked
	else if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_redest.png"))
	{
		m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->SetUniformScale(m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetXScale() - 0.0667f);
		if (m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->GetXScale() < 0.5f)
		{
			m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 0.5)]->changeWhite();
			m_player->IncrementKillCount();
			m_player->IncrementKillCount();
			m_player->IncrementKillCount();
		}
		m_player->SetUniformScale(m_player->GetXScale() - 0.08f);
		m_player->SetTarget(PrePos);
	}
}

bool Logic::TileCheck() //Checks if the tile the player is moving to is a valid position, and also checks if the player has any valid moves
{
	if (m_map[int(m_player->GetTarget().x + 0.5)][int(m_player->GetTarget().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_white.png") || m_map[int(m_player->GetTarget().x + 0.5)][int(m_player->GetTarget().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_green.png") || m_map[int(m_player->GetTarget().x + 0.5)][int(m_player->GetTarget().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_blue.png") || m_map[int(m_player->GetTarget().x + 0.5)][int(m_player->GetTarget().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_red.png") || m_map[int(m_player->GetTarget().x + 0.5)][int(m_player->GetTarget().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_reder.png") || m_map[int(m_player->GetTarget().x + 0.5)][int(m_player->GetTarget().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_redest.png"))
	{
		return true;
	}
	if (m_map[int(m_player->GetPosition().x + 1.5)][int(m_player->GetPosition().z + -0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + 1.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + 1.5)][int(m_player->GetPosition().z + 1.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + -0.5)][int(m_player->GetPosition().z + -0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + -0.5)][int(m_player->GetPosition().z + 0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + -0.5)][int(m_player->GetPosition().z + 1.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + -0.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png") && m_map[int(m_player->GetPosition().x + 0.5)][int(m_player->GetPosition().z + 1.5)]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_disabled.png"))
	{
		gameOver = true;
	}

	return false;
}

bool Logic::WhiteTile(int x, int z) // checks if a give tileis white 
{
	if (m_map[x][z]->GetTexture() == m_texture->GetTexture("Assets/Textures/tile_white.png"))
	{
		return true;
	}
	return false;
}

void Logic::playerFlashing() //makes the player flash if they are one hit from dead
{
	if (m_player->GetXScale() < 0.48f)
	{
		if (m_player->GetPlayerFlash())
		{
			m_player->SetTexture(m_texture->GetTexture("Assets/Textures/tile_red.png"));
			m_player->SetPlayerFlash(!m_player->GetPlayerFlash());
		}
		else
		{
			m_player->SetTexture(m_texture->GetTexture("Assets/Textures/tile_disabled.png"));
			m_player->SetPlayerFlash(!m_player->GetPlayerFlash());
		}
	}
}

void Logic::MakeWall(GameObject * Object) //truns a given game object into a wall
{
	Object->SetMesh(m_mesh->GetMesh("Assets/Meshes/wall_tile.obj"));
	Object->SetTexture(m_texture->GetTexture("Assets/Textures/tile_disabled.png"));
	if (Object->GetPosition().y > -0.5f) //Checks if the object is already a wall
	{
		Object->SetPosition(Object->GetPosition() + Vector3(0, -0.5, 0));
	}
}

void Logic::SetTele(float x, float z) //adds a location to the list of teleport locations
{
	teleLocation.push_back(Vector3(x, 0.0f, z));
}