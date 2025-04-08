/**
 * Holds 3d meshes and 2d sprites in memory.
 */

#include "TheApp.h"
#include "TextUtils.h"
#include "ZipManager.h"
#include "Resources.h"

int CResources::MODEL_GAME_PLAYER_FRAME					= 0;
int CResources::MODEL_GAME_PLAYER_MINIGUN				= 1;
int CResources::MODEL_GAME_ENEMY_DRONE_1				= 2;
int CResources::MODEL_GAME_ENEMY_DRONE_2				= 3;
int CResources::MODEL_GAME_ENEMY_DRONE_3				= 4;
int CResources::MODEL_GAME_ENEMY_DRONE_4				= 5;
int CResources::MODEL_GAME_ENEMY_DRONE_5				= 6;
int CResources::MODEL_GAME_ENEMY_SNIPER_1				= 7;
int CResources::MODEL_GAME_ENEMY_SNIPER_2				= 8;
int CResources::MODEL_GAME_ENEMY_SNIPER_3				= 9;
int CResources::MODEL_GAME_ENEMY_SNIPER_4				= 10;
int CResources::MODEL_GAME_ENEMY_SNIPER_5				= 11;
int CResources::MODEL_GAME_ENEMY_ROLLER_1				= 12;
int CResources::MODEL_GAME_ENEMY_ROLLER_2				= 13;
int CResources::MODEL_GAME_ENEMY_ROLLER_3				= 14;
int CResources::MODEL_GAME_ENEMY_ROLLER_4				= 15;
int CResources::MODEL_GAME_ENEMY_ROLLER_5				= 16;
int CResources::MODEL_GAME_ENEMY_VANGUARD_1				= 17;
int CResources::MODEL_GAME_ENEMY_VANGUARD_2				= 18;
int CResources::MODEL_GAME_ENEMY_VANGUARD_3				= 19;
int CResources::MODEL_GAME_ENEMY_VANGUARD_4				= 20;
int CResources::MODEL_GAME_ENEMY_VANGUARD_5				= 21;
int CResources::MODEL_GAME_BOSS_1_FRAME					= 22;
int CResources::MODEL_GAME_BOSS_1_CORE					= 23;
int CResources::MODEL_GAME_BOSS_1_LASER_LEFT			= 24;
int CResources::MODEL_GAME_BOSS_1_LASER_RIGHT			= 25;
int CResources::MODEL_GAME_BOSS_1_SCATTER				= 26;
int CResources::MODEL_GAME_BOSS_1_CANNON				= 27;
int CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN		= 28;
int CResources::MODEL_GAME_BULLET_DRONE					= 29;
int CResources::MODEL_GAME_BULLET_SNIPER				= 30;
int CResources::MODEL_GAME_BULLET_ROLLER				= 31;
int CResources::MODEL_GAME_BULLET_VANGUARD				= 32;
int CResources::MODEL_GAME_BULLET_BOSS_1_LASER			= 33;
int CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER		= 34;
int CResources::MODEL_GAME_ASTEROID_BIG_1				= 35;
int CResources::MODEL_GAME_ASTEROID_BIG_2				= 36;
int CResources::MODEL_GAME_ASTEROID_BIG_3				= 37;
int CResources::MODEL_GAME_ASTEROID_BIG_4				= 38;
int CResources::MODEL_GAME_ASTEROID_BIG_5				= 39;
int CResources::MODEL_GAME_ASTEROID_MEDIUM_1			= 40;
int CResources::MODEL_GAME_ASTEROID_MEDIUM_2			= 41;
int CResources::MODEL_GAME_ASTEROID_MEDIUM_3			= 42;
int CResources::MODEL_GAME_ASTEROID_MEDIUM_4			= 43;
int CResources::MODEL_GAME_ASTEROID_MEDIUM_5			= 44;
int CResources::MODEL_GAME_ASTEROID_SMALL_1				= 45;
int CResources::MODEL_GAME_ASTEROID_SMALL_2				= 46;
int CResources::MODEL_GAME_ASTEROID_SMALL_3				= 47;
int CResources::MODEL_GAME_ASTEROID_SMALL_4				= 48;
int CResources::MODEL_GAME_ASTEROID_SMALL_5				= 49;
int CResources::MODEL_GAME_TEXT_SCORE					= 50;

int CResources::SPRITE_GAME_BULLET_FIRST				= 0;
int CResources::SPRITE_GAME_BULLET_PLAYER_MINIGUN_FRONT	= 0;
int CResources::SPRITE_GAME_BULLET_PLAYER_MINIGUN_LEFT	= 1;
int CResources::SPRITE_GAME_BULLET_PLAYER_MINIGUN_RIGHT	= 2;
int CResources::SPRITE_GAME_BULLET_DRONE				= 3;
int CResources::SPRITE_GAME_BULLET_SNIPER				= 4;
int CResources::SPRITE_GAME_BULLET_ROLLER				= 5;
int CResources::SPRITE_GAME_BULLET_BOSS_1_LASER_DOWN	= 6;
int CResources::SPRITE_GAME_BULLET_BOSS_1_LASER_LEFT	= 7;
int CResources::SPRITE_GAME_BULLET_BOSS_1_LASER_RIGHT	= 8;
int CResources::SPRITE_GAME_BULLET_BOSS_1_SCATTER		= 9;
int CResources::SPRITE_GAME_BULLET_LAST					= 9;
int CResources::SPRITE_HIGHSCORE_BULLET_FIRST			= 10;
int CResources::SPRITE_HIGHSCORE_BULLET_PLAYER_MINIGUN	= 10;
int CResources::SPRITE_HIGHSCORE_BULLET_LAST			= 10;

CResources::CResources()
{
	this->m_pDevice = NULL;
	this->m_bInitialized = false;

	this->m_iMeshSteps = 0;
	this->m_iSpriteSteps = 0;
	this->m_iMeshStepsMax = 0;
	this->m_iSpriteStepsMax = 0;
	
	this->m_bIsLoadWaitCycle = false;
	this->m_bResourcesLoaded = false;
}

CResources::~CResources()
{
	Release();
}

void CResources::Init(CTheApp* pApp, CZipManager* pZipManager)
{
	if (this->m_pApp == NULL)
	{
		this->m_pApp = pApp;
	}

	if (this->m_pDevice == NULL)
	{
		this->m_pDevice = pApp->GetDevice();
	}

	if (this->m_pZipManager == NULL)
	{
		this->m_pZipManager = pZipManager;
	}

	this->m_iMeshSteps = 1;
	this->m_iSpriteSteps = 1;
	this->m_iMeshStepsMax = 0;
	this->m_iSpriteStepsMax = 0;

	this->m_iResourcesLoadStepCounter = 0;

	this->m_bInitialized = true;
	this->m_bResourcesLoaded = false;
}

LPCTSTR CResources::GetUnpackedResourceFilePath(const char* childPath)
{
	std::string resourcePath = this->m_pZipManager->GetResourceFilePath(childPath);
	this->m_tempResourceFilePath = TextUtils::StringToWchar(resourcePath);
	return this->m_tempResourceFilePath.c_str();
}

void CResources::SetMeshFilePath(const char* childPath)
{
	std::string resourcePath = this->m_pZipManager->GetResourceFilePath(childPath);
	CXFileContainer::SetCurrentFilePath(resourcePath);
}

void CResources::SetSpriteFilePath(const char* childPath)
{
	std::string resourcePath = this->m_pZipManager->GetResourceFilePath(childPath);

	CSprite::SetCurrentFilePath(resourcePath);
	CSpriteScrolling::SetCurrentFilePath(resourcePath);
}

void CResources::Release(void)
{
	// mesh
	{
		std::map<int, LPD3DXMESH>::iterator it;

		for (it = m_MapMesh.begin(); it != m_MapMesh.end(); it++)
		{
			LPD3DXMESH mesh = it->second;

			if (mesh)
			{
				mesh->Release();
				mesh = NULL;
			}
		}

		m_MapMesh.clear();
	}

	// material
	{
		std::map<int, std::vector<D3DMATERIAL9*>>::iterator it;

		for (it = m_MapMaterial.begin(); it != m_MapMaterial.end(); it++)
		{
			std::vector<D3DMATERIAL9*> materials = it->second;

			for (DWORD i = 0; i < materials.size(); i++)
			{
				if (i == 0)
				{
					delete materials[i];
				}

				materials[i] = NULL;
			}
		}

		m_MapMaterial.clear();
	}

	// texture
	{
		std::map<int, std::vector<LPDIRECT3DTEXTURE9>>::iterator it;

		for (it = m_MapTexture.begin(); it != m_MapTexture.end(); it++)
		{
			std::vector<LPDIRECT3DTEXTURE9> textures = it->second;

			for (DWORD i = 0; i < textures.size(); i++)
			{
				if (textures[i])
				{
					textures[i]->Release();
					textures[i] = NULL;
				}
			}
		}

		m_MapTexture.clear();
	}

	// sprite
	{
		std::map <int, CSprite>::iterator it;

		for (it = m_MapSprite.begin(); it != m_MapSprite.end(); it++)
		{
			CSprite sprite = it->second;
			sprite.Release();
		}

		m_MapSprite.clear();
	}
}

LPD3DXMESH CResources::GetMesh(int index)
{
	std::map<int, LPD3DXMESH>::const_iterator iterator;
	iterator = this->m_MapMesh.find(index);
	return iterator->second;
}

std::vector<D3DMATERIAL9*> CResources::GetMaterial(int index)
{
	std::map<int, std::vector<D3DMATERIAL9*>>::const_iterator iterator;
	iterator = this->m_MapMaterial.find(index);
	return iterator->second;
}

std::vector<LPDIRECT3DTEXTURE9> CResources::GetTexture(int index)
{
	std::map<int, std::vector<LPDIRECT3DTEXTURE9>>::const_iterator iterator;
	iterator = this->m_MapTexture.find(index);
	return iterator->second;
}

CSprite CResources::GetSprite(int index)
{
	std::map<int, CSprite>::const_iterator iterator;
	iterator = this->m_MapSprite.find(index);
	return iterator->second;
}

HRESULT CResources::LoadGameObject(std::string fileName, int mapKey, int modelType)
{
	CXFileContainer xFile = LoadMeshObject(fileName, mapKey, modelType);

	if (xFile.IsInvalid())
	{
		return S_FALSE;
	}

	return S_OK;
}

HRESULT CResources::LoadGameEnemyObject(std::string fileName, int mapKey, int modelType)
{
	CXFileContainer xFile = LoadMeshObject(fileName, mapKey, modelType);

	if (xFile.IsInvalid())
	{
		return S_FALSE;
	}

	RotateEnemy(xFile.GetMesh());
	SetMeshData(xFile, mapKey, modelType);

	return S_OK;
}

CXFileContainer CResources::LoadMeshObject(std::string fileName, int mapKey, int modelType)
{
	char str[128] = "";

	CXFileContainer xFile;
	HRESULT hres = xFile.Create(this->m_pDevice, fileName);

	if (FAILED(hres))
	{
		std::stringstream ss;
		ss << "ERROR: " << fileName;
		std::cout << ss.str() << std::endl;

		xFile.SetIsInvalid();
	}
	else
	{
		SetMeshData(xFile, mapKey, modelType);
	}

	return xFile;
}

void CResources::RotatePlayer(LPD3DXMESH mesh)
{
	DWORD i;
	BYTE *pVertices = NULL;
	DWORD dwStride = 0;
	D3DXMATRIX mRotation;

	// rotate 180 degrees by y axis
	D3DXMatrixRotationY(&mRotation, D3DX_PI);

	dwStride = mesh->GetNumBytesPerVertex();
	mesh->LockVertexBuffer(0, (void**)&pVertices);

	for (i = 0; i < mesh->GetNumVertices(); i++)
	{
		// rotate vertex position
		D3DXVec3TransformCoord(	(D3DXVECTOR3*)pVertices,
								(D3DXVECTOR3*)pVertices,
								&mRotation);
		// rotate vertex normal
		D3DXVec3TransformCoord(	(D3DXVECTOR3*)(pVertices + 12),
								(D3DXVECTOR3*)(pVertices + 12),
								&mRotation);

		// move pointer to next vertex
		pVertices += dwStride;
	}

	mesh->UnlockVertexBuffer();

	// rotate 90 degrees by x axes
	D3DXMatrixRotationX(&mRotation,D3DX_PI * -0.5f);

	pVertices = NULL;
	dwStride = mesh->GetNumBytesPerVertex();
	mesh->LockVertexBuffer(0, (void**)&pVertices);

	for ( i = 0; i < mesh->GetNumVertices(); i++)
	{
		// rotate vertex position
		D3DXVec3TransformCoord(	(D3DXVECTOR3*)pVertices,
								(D3DXVECTOR3*)pVertices,
								&mRotation);
		// rotate vertex normal
		D3DXVec3TransformCoord(	(D3DXVECTOR3*)(pVertices + 12),
								(D3DXVECTOR3*)(pVertices + 12),
								&mRotation);


		// move pointer to next vertex
		pVertices += dwStride;
	}

	mesh->UnlockVertexBuffer();

	if(pVertices)
	{
		pVertices = NULL;
	}
}

void CResources::RotateEnemy(LPD3DXMESH mesh)
{
	DWORD i;
	BYTE *pVertices = NULL;
	DWORD dwStride = 0;
	D3DXMATRIX mRotation;

	// rotate 90 degrees by x axis
	D3DXMatrixRotationX(&mRotation, -(D3DX_PI / 2));

	dwStride = mesh->GetNumBytesPerVertex();
	mesh->LockVertexBuffer(0, (void**)&pVertices);

	for (i = 0; i < mesh->GetNumVertices(); i++)
	{
		// rotate vertex position
		D3DXVec3TransformCoord(	(D3DXVECTOR3*)pVertices,
								(D3DXVECTOR3*)pVertices,
								&mRotation);
		// rotate vertex normal
		D3DXVec3TransformCoord(	(D3DXVECTOR3*)(pVertices + 12),
								(D3DXVECTOR3*)(pVertices + 12),
								&mRotation);

		// move pointer to next vertex
		pVertices += dwStride;
	}

	mesh->UnlockVertexBuffer();

	if(pVertices)
	{
		pVertices = NULL;
	}
}

void CResources::SetMeshData(CXFileContainer xFile, int mapKey, int modelType)
{
	LPD3DXMESH mesh = xFile.GetMesh();
	mesh = SetPivotPoint(mesh, mapKey);

	typedef std::pair<int, LPD3DXMESH> meshPair;
	typedef std::pair<int, std::vector<D3DMATERIAL9*>> materialPair;
	typedef std::pair<int, std::vector<LPDIRECT3DTEXTURE9>> texturePair;

	this->m_MapMesh.insert(meshPair(mapKey, mesh));

	std::vector<D3DMATERIAL9*> vectorMaterial;
	std::vector<LPDIRECT3DTEXTURE9> vectorTexture;

	D3DMATERIAL9* pMaterial;

	// set materials and textures
	for (DWORD i = 0; i < xFile.GetMaterialCount(); i++)
	{
		pMaterial = &xFile.GetMaterials()[i];
		pMaterial = this->InitMaterial(pMaterial, mapKey, modelType);

		vectorMaterial.push_back(pMaterial);
		vectorTexture.push_back(xFile.GetTextures()[i]);
	}

	m_MapMaterial.insert(materialPair(mapKey, vectorMaterial));
	m_MapTexture.insert(texturePair(mapKey, vectorTexture));
}

D3DMATERIAL9* CResources::InitMaterial(D3DMATERIAL9* material, int mapKey, int modelType)
{
	switch(modelType)
	{
	case MODEL_TYPE_PLAYER:
	case MODEL_TYPE_HIGHSCORE_PLAYER:

		material->Specular.r = 0.35f;
		material->Specular.g = 0.35f;
		material->Specular.b = 0.35f;
		material->Specular.a = 1.0f;
		material->Power = 20.0f;

		break;

	case MODEL_TYPE_ENEMY:
	{
		// enemy depth 1
		float diffuseMultiplier = 1.0f;
		float specularValue = 0.35f;
		float specularPower = 20.0f;

		// enemy depth 2
		if (mapKey == MODEL_GAME_ENEMY_DRONE_2 || mapKey == MODEL_GAME_ENEMY_SNIPER_2 || 
			mapKey == MODEL_GAME_ENEMY_ROLLER_2 || mapKey == MODEL_GAME_ENEMY_VANGUARD_2)
		{
			diffuseMultiplier = 0.5f;
		}
		// enemy depth 3
		else if (mapKey == MODEL_GAME_ENEMY_DRONE_3 || mapKey == MODEL_GAME_ENEMY_SNIPER_3 ||
			mapKey == MODEL_GAME_ENEMY_ROLLER_3 || mapKey == MODEL_GAME_ENEMY_VANGUARD_3)
		{
			diffuseMultiplier = 0.41f;
		}
		// enemy depth 4
		else if (mapKey == MODEL_GAME_ENEMY_DRONE_4 || mapKey == MODEL_GAME_ENEMY_SNIPER_4 ||
			mapKey == MODEL_GAME_ENEMY_ROLLER_4 || mapKey == MODEL_GAME_ENEMY_VANGUARD_4)
		{
			diffuseMultiplier = 0.33f;
		}
		// enemy depth 5
		else if (mapKey == MODEL_GAME_ENEMY_DRONE_5 || mapKey == MODEL_GAME_ENEMY_SNIPER_5 ||
			mapKey == MODEL_GAME_ENEMY_ROLLER_5 || mapKey == MODEL_GAME_ENEMY_VANGUARD_5)
		{
			diffuseMultiplier = 0.25f;
		}

		// enemy depth 2-5
		if (mapKey != MODEL_GAME_ENEMY_DRONE_1 && mapKey != MODEL_GAME_ENEMY_SNIPER_1 &&
			mapKey != MODEL_GAME_ENEMY_ROLLER_1 && mapKey != MODEL_GAME_ENEMY_VANGUARD_1)
		{
			specularValue = 0.0f;
			specularPower = 0.0f;
		}

		float diffuseValue = material->Diffuse.r;
		material->Diffuse.r = diffuseMultiplier * diffuseValue;

		diffuseValue = material->Diffuse.g;
		material->Diffuse.g = diffuseMultiplier * diffuseValue;

		diffuseValue = material->Diffuse.b;
		material->Diffuse.b = diffuseMultiplier * diffuseValue;

		material->Specular.a = 1.0f;
		material->Specular.r = specularValue;
		material->Specular.g = specularValue;
		material->Specular.b = specularValue;
		material->Power = specularPower;
	}
		break;

	case MODEL_TYPE_BOSS:

		material->Specular.r = 0.35f;
		material->Specular.g = 0.35f;
		material->Specular.b = 0.35f;
		material->Specular.a = 1.0f;
		material->Power = 30.0f;

		break;

	case MODEL_TYPE_BULLET_PLAYER:

		material->Diffuse.r = 1.0f;
		material->Diffuse.g = 0.5f;
		material->Diffuse.b = 0.5f;
		material->Diffuse.a = 1.0f;

		material->Emissive.r = 2.5f;
		material->Emissive.g = 0.0f;
		material->Emissive.b = 0.0f;
		material->Emissive.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_BULLET_DRONE:

		material->Diffuse.r = 0.9f;
		material->Diffuse.g = 1.0f;
		material->Diffuse.b = 0.9f;
		material->Diffuse.a = 1.0f;

		material->Emissive.r = 0.0f;
		material->Emissive.g = 2.5f;
		material->Emissive.b = 0.0f;
		material->Emissive.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_BULLET_SNIPER:

		material->Diffuse.r = 0.9f;
		material->Diffuse.g = 0.9f;
		material->Diffuse.b = 1.0f;
		material->Diffuse.a = 1.0f;

		material->Emissive.r = 0.0f;
		material->Emissive.g = 0.0f;
		material->Emissive.b = 2.5f;
		material->Emissive.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_BULLET_ROLLER:

		material->Diffuse.r = 1.0f;
		material->Diffuse.g = 1.0f;
		material->Diffuse.b = 1.0f;
		material->Diffuse.a = 1.0f;

		material->Emissive.r = 2.0f;
		material->Emissive.g = 2.0f;
		material->Emissive.b = 0.0f;
		material->Emissive.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_BULLET_VANGUARD:
		break;

	case MODEL_TYPE_BULLET_BOSS_1_LASER:

		material->Diffuse.r = 0.0f;
		material->Diffuse.g = 0.0f;
		material->Diffuse.b = 2.0f;
		material->Diffuse.a = 1.0f;

		material->Emissive.r = 0.7f;
		material->Emissive.g = 0.7f;
		material->Emissive.b = 1.0f;
		material->Emissive.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_BULLET_BOSS_1_SCATTER:

		material->Diffuse.r = 1.0f;
		material->Diffuse.g = 1.0f;
		material->Diffuse.b = 1.0f;
		material->Diffuse.a = 1.0f;

		material->Emissive.r = 0.0f;
		material->Emissive.g = 2.0f;
		material->Emissive.b = 0.0f;
		material->Emissive.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_ASTEROID:

		material->Diffuse.r = 0.8f;
		material->Diffuse.g = 0.8f;
		material->Diffuse.b = 0.8f;
		material->Diffuse.a = 1.0f;

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;

	case MODEL_TYPE_TEXT:

		material->Specular.r = 0.0f;
		material->Specular.g = 0.0f;
		material->Specular.b = 0.0f;
		material->Specular.a = 0.0f;
		material->Power = 0.0f;

		break;
	}

	return material;
}

LPD3DXMESH CResources::SetPivotPoint(LPD3DXMESH mesh, int mapKey)
{
	if (mapKey == MODEL_GAME_PLAYER_MINIGUN)
	{
		// move minigun pivot point to the edge of box
		// so that it will rotate correctly (from its root, not center)

		float fMinigunLength = 2.0f;

		DWORD i;
		BYTE *pVertices = NULL;
		DWORD dwStride = 0;

		dwStride = mesh->GetNumBytesPerVertex();
		mesh->LockVertexBuffer(0, (void**)&pVertices);

		for (i = 0; i < mesh->GetNumVertices(); i++)
		{
			// get the vertex position
			D3DXVECTOR3* pVertexPosition = (D3DXVECTOR3*)pVertices;

			// move all vertices by half of the pipe length
			pVertexPosition->y += fMinigunLength * 0.5f;

			// move pointer to next vertex
			pVertices += dwStride;
		}

		mesh->UnlockVertexBuffer();

		if(pVertices)
		{
			pVertices = NULL;
		}
	}

	return mesh;
}

void CResources::SetSpriteData(CSprite sprite, int mapKey)
{
	typedef std::pair<int, CSprite> spritePair;
	this->m_MapSprite.insert( spritePair (mapKey, sprite) );
}
