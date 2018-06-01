#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject()
{
}

GameObject::GameObject(Mesh* mesh, Shader* shader, Vector3 position)
{
	m_mesh = mesh;
	m_shader = shader;
	m_position = position;
	m_texture = NULL;
	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);
	m_TM = NULL;
	m_MM = NULL;
	m_S = NULL;
	tempTile = NULL;
}

GameObject::GameObject(Mesh* mesh, Shader* shader, Vector3 position, Texture* texture)
{
	m_mesh = mesh;
	m_shader = shader;
	m_position = position;
	m_texture = texture;
	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);
	m_TM = NULL;
	m_MM = NULL;
	m_S = NULL;
	tempTile = NULL;
}

GameObject::GameObject(Mesh* mesh, Shader* shader, Vector3 position, Texture* texture, MeshManager* MM, TextureManager* TM, Shader* S)
{
	m_mesh = mesh;
	m_shader = shader;
	m_position = position;
	m_texture = texture;
	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);
	m_TM = TM;
	m_MM = MM;
	m_S = S;
	tempTile = NULL;
	Check();
}

GameObject::~GameObject() { CleanTempTile(); }

void GameObject::Update(float timestep)
{

}

void GameObject::Check() //Creates a floor tile under tiles that need to stand on something
{
	if (m_mesh->GetFilename() != "Assets/Meshes/floor_tile.obj" && m_mesh->GetFilename() != "Assets/Meshes/floor_tile.obj")
	{
		tempTile = new GameObject(m_MM->GetMesh("Assets/Meshes/floor_tile.obj"), m_S, m_position, m_TM->GetTexture("Assets/Textures/tile_white.png"));
	}
}

void GameObject::changeWhite() //gets rid of tiles for standing on
{
	m_mesh = m_MM->GetMesh("Assets/Meshes/floor_tile.obj");
	m_texture = m_TM->GetTexture("Assets/Textures/tile_white.png");
	SetUniformScale(1.0f);
	m_rotX = m_rotY = m_rotZ = 0.0f;
	m_position = Vector3(int(m_position.x + 0.5), 0, int(m_position.z + 0.5));
	CleanTempTile();
}

void GameObject::CleanTempTile() //pointer cleanup
{
	if (tempTile != NULL)
	{
		delete tempTile;
		tempTile = NULL;
	}
}

void GameObject::UpdateTile(float timestep, Vector3 player)
{
	if (m_texture->GetFilename() == "Assets/Textures/tile_red.png" || m_texture->GetFilename() == "Assets/Textures/tile_reder.png" || m_texture->GetFilename() == "Assets/Textures/tile_redest.png") //Magic for making the enemies face the player
	{
		float RVecX = player.x - m_position.x; 
		float RVecY = player.z - m_position.z;

		float Angle = atan(RVecX / RVecY);

		if (RVecY < 0)
		{
			Angle = Angle + PI;
		}

		m_rotY = Angle;
		
		/*

		ObjVec
		PlayerVec

		objvec - playervec = RVec

		arcTan(RvecX/rvecY) = Angle

		Check Quadrants and apply tarnformatinos

		*/
	}
}

void GameObject::Render(Direct3D* renderer, Camera* cam)
{
	if (m_mesh)
	{
		m_world = Matrix::CreateScale(m_scaleX, m_scaleY, m_scaleZ) * Matrix::CreateFromYawPitchRoll(m_rotY, m_rotX, m_rotZ) * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
	if (tempTile != NULL)
	{
		tempTile->Render(renderer, cam);
	}
}