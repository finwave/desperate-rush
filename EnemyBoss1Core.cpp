#include "EnemyBoss1Core.h"

CEnemyBoss1Core::CEnemyBoss1Core(	eTYPE eType,
									eBEHAVIOUR eBehaviour)
{
	this->m_pDevice = NULL;

	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;

	this->m_iHealth = 0;
	this->m_iHealthMax = 0;
}

CEnemyBoss1Core::~CEnemyBoss1Core(void)
{
}

HRESULT CEnemyBoss1Core::Create(CTheApp* pTheApp,
								CGameSettings* pGameSettings,
								LPDIRECT3DDEVICE9 pDevice,
								LPD3DXMESH mesh,
								std::vector<D3DMATERIAL9*> materials,
								std::vector<LPDIRECT3DTEXTURE9> textures,
								int iVolumeSoundEffect)
{
	HRESULT hres;

	this->m_pDevice = pDevice;

	this->m_Materials = materials;
	this->m_Textures = textures;

	this->InitMaterial();

	/** CREATE SHIP **/

	hres = IEnemy::Create(	pTheApp,
							pGameSettings,
							mesh,
							materials,
							textures,
							NULL,
							iVolumeSoundEffect);
	if( FAILED(hres) )
	{
		return hres;
	}

	this->InitPosition();

	this->m_bBoss = true;

	return S_OK;
}

void CEnemyBoss1Core::Init(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect)
{
	this->m_fEnemyWidth = 0.0f;
	this->m_fEnemyHeight = 0.0f;

	this->m_iHealth = pGameSettings->m_iEnemyBoss1FrameHealth;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = 0.0f;
	this->m_fSpeedDefault = this->m_fSpeed;

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);
}

void CEnemyBoss1Core::Release()
{
	CEnemyBoss::Release();
}

void CEnemyBoss1Core::UpdateShip(int iHealth,
								 float fFrametime)
{
	if (iHealth != m_iHealth)
	{
		this->SetMaterial(iHealth);
		this->InitTexture(true);
	}

	IEnemy::Update(fFrametime, 0.0f);
}

void CEnemyBoss1Core::InitPosition()
{
	D3DXVECTOR3 pos;

	pos = this->GetPosition();
	pos.y -= 20.676f;

	this->SetPosition(pos);
}

void CEnemyBoss1Core::InitMaterial()
{
	for (DWORD i = 0; i < this->m_Materials.size(); i++)
	{
		// Set the RGBA for diffuse reflection.
		this->m_Materials[i]->Diffuse.r = 0.0f;
		this->m_Materials[i]->Diffuse.g = 1.0f;
		this->m_Materials[i]->Diffuse.b = 0.0f;
		this->m_Materials[i]->Diffuse.a = 1.0f;
	}
}

void CEnemyBoss1Core::SetMaterial(int iHealth)
{
	float fGreen;
	float fRed;

	if(iHealth < (this->m_iHealthMax / 5 * 4))
	{
		// red increases, together
		// with green creates yellow
		if(iHealth >= (this->m_iHealthMax / 5 * 2))
		{
			fGreen = 1.0f;
			fRed = 2.0f - ((float)iHealth / (this->m_iHealthMax / 5 * 2));
		}
		// green decreases, leaving only red
		else
		{
			fRed = 1.0f;
			fGreen = (float)iHealth / (this->m_iHealthMax / 5 * 2 - 1);
		}
	}
	else
	{
		fGreen = 1.0f;
		fRed = 0.0f;
	}

	for (DWORD i = 0; i < this->m_Materials.size(); i++)
	{
		// Set the RGBA for diffuse reflection.
		this->m_Materials[i]->Diffuse.r = fRed;
		this->m_Materials[i]->Diffuse.g = fGreen;
		this->m_Materials[i]->Diffuse.b = 0.0f;
		this->m_Materials[i]->Diffuse.a = 1.0f;
	}
}

void CEnemyBoss1Core::InitTexture(bool bClear)
{
	if(bClear)
	{
		this->ClearMeshData();
	}

	for (DWORD i = 0; i < this->m_Materials.size(); i++)
	{
		this->AddMeshData(this->m_Materials[i], this->m_Textures[i]);
	}
}

void CEnemyBoss1Core::MoveEnter(float fFrametime, float fPlayerVelocity)
{
}