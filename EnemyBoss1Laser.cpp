#include "Level.h"
#include "GameSettings.h"
#include "WeaponBoss1Laser.h"
#include "EnemyBoss1Laser.h"

CEnemyBoss1Laser::CEnemyBoss1Laser(	eTYPE eType,
									eBEHAVIOUR eBehaviour,
									eSIDE eSide)
{
	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
	this->m_eSide = eSide;

	this->m_eAction = eACTION_READY;
	this->m_eDirection = eDIRECTION::eDIRECTION_FRONT;

	this->m_pLevel = NULL;
	this->m_pLaser = NULL;
	this->m_pBossFrame = NULL;

	this->m_fShootBulletTimer = 0.0f;
	this->m_iShootAmountCounter = 0;
	this->m_iShootAmountMax = 0;

	GenerateRandomShootTime();
}

CEnemyBoss1Laser::~CEnemyBoss1Laser(void)
{
}

HRESULT CEnemyBoss1Laser::Create(	CLevel* pLevel,
									CTheApp* pTheApp,
									IEnemy* pBossFrame,
									LPD3DXMESH mesh,
									std::vector<D3DMATERIAL9*> materials,
									std::vector<LPDIRECT3DTEXTURE9> textures,
									int iVolumeSoundEffect)
{
	HRESULT hres;

	/** CREATE SHIP **/

	hres = IEnemy::Create(	pTheApp,
							mesh,
							materials,
							textures,
							NULL,
							iVolumeSoundEffect);
	if( FAILED(hres) )
	{
		return hres;
	}

	this->m_pLevel = pLevel;
	this->m_pBossFrame = pBossFrame;

	// sound effect volume
	int iVolume = pTheApp->GetConfig().GetVolumeSoundEffect();

	if (iVolume == 0)
	{
		this->m_iVolumeSoundEffect = -10000;
	}
	else
	{
		float fVolume = CGameSettings::VOLUME_BOSS_LASER * (float)iVolume;
		float fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumeSoundEffect = (int)fExactVolume;
	}

	return S_OK;
}

void CEnemyBoss1Laser::Init(CTheApp* pTheApp,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect)
{
	this->m_bBoss = true;

	this->m_fEnemyWidth = CGameSettings::ENEMY_BOSS_LASER_WIDTH;
	this->m_fEnemyHeight = CGameSettings::ENEMY_BOSS_LASER_HEIGHT;

	this->m_iHealth = CGameSettings::ENEMY_BOSS_LASER_HEALTH;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = 0.0f;
	this->m_fSpeedDefault = this->m_fSpeed;

	IEnemy::Init(pTheApp, pSpriteAfterburn, iVolumeSoundEffect);
}

void CEnemyBoss1Laser::Release()
{
	if(this->m_pLaser)
	{
		this->m_pLaser->Release();
		delete this->m_pLaser;
		this->m_pLaser = NULL;
	}

	CEnemyBoss::Release();
}

void CEnemyBoss1Laser::UpdateShip(float fFrametime, bool bShootPossible)
{
	UpdatePosition();

	if (!this->m_bEnter)
	{
		switch (this->m_eAction)
		{
		case eACTION_SHOOT_WEAPON:

			if (bShootPossible)
			{
				// current multi-shoot session is not finished
				if (this->m_iShootAmountCounter < this->m_iShootAmountMax)
				{
					// fire next multi-shoot bullet
					if (this->m_fShootBulletTimer <= 0.0f)
					{
						// shoot next bullet
						ShootWeapons(m_pBossFrame->GetPosition());
						// reset single shot timer
						this->m_fShootBulletTimer = this->m_pTheApp->RandFloat(0.075f, 0.15f);
						// increase the count of fired bullets
						this->m_iShootAmountCounter++;
					}
					else
					{
						// update single shot timer
						this->m_fShootBulletTimer -= fFrametime;
					}
				}
				// current multi-shoot session is finished
				else
				{
					// wait for the next attack command
					SetAction(eACTION_READY);
				}
			}
			else
			{
				// wait for the next attack command
				SetAction(eACTION_READY);
			}

			break;
		}
	}

	IEnemy::Update(fFrametime, 0.0f);
}

void CEnemyBoss1Laser::UpdatePosition()
{
	D3DXVECTOR3 pos = m_pBossFrame->GetPosition();

	pos.z -= 7.0f;

	switch (this->m_eSide)
	{
	// left laser
	case eSIDE_LEFT:

		pos.x -= 35.0f;
		pos.y += 27.0f;

		break;

	// right laser
	case eSIDE_RIGHT:

		pos.x += 35.0f;
		pos.y += 27.0f;

		break;
	}

	SetPosition(pos);
}

void CEnemyBoss1Laser::Render()
{
	IEnemy::Render(this->m_pTheApp->GetDevice());
}

void CEnemyBoss1Laser::SetAction(eACTION eAction)
{
	switch (eAction)
	{
	case eACTION_SHOOT_WEAPON:

		this->m_fShootBulletTimer = 0.0f;
		this->m_iShootAmountCounter = 0;
		this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;

		break;
	}

	this->m_eAction = eAction;
}

void CEnemyBoss1Laser::ShootWeapons(D3DXVECTOR3 framePos)
{
	CWeapon* weapon = NULL;
	weapon = new CWeaponBoss1Laser();

	if (weapon)
	{
		weapon->Create(this->m_pTheApp->GetDevice(),
			this->m_pLaser->GetMesh(),
			this->m_pLaser->GetMeshDataArray(),
			this->m_pLaser->GetWidth(),
			this->m_pLaser->GetHeight(),
			this->m_pLaser->GetSpeed(),
			this->m_pLaser->GetDamage(),
			this->m_pLaser->GetBulletType());

		/* COLLISION MODEL */
		weapon->SetCollisionMesh(this->m_pLaser->GetCollisionMesh());

		switch (this->m_eDirection)
		{
		case eDIRECTION::eDIRECTION_FRONT:

			switch (this->m_eSide)
			{
			case eSIDE_LEFT:

				weapon->SetSide(CWeaponBoss1Laser::eSIDE_LEFT);

				break;

			case eSIDE_RIGHT:

				weapon->SetSide(CWeaponBoss1Laser::eSIDE_RIGHT);

				break;
			}

			weapon->SetDirection(CWeapon::eDIRECTION_DOWN);

			break;

		case eDIRECTION::eDIRECTION_DIAGONAL:

			switch (this->m_eSide)
			{
			case eSIDE_LEFT:

				weapon->SetSide(CWeaponBoss1Laser::eSIDE_LEFT);
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT);

				break;

			case eSIDE_RIGHT:

				weapon->SetSide(CWeaponBoss1Laser::eSIDE_RIGHT);
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT);

				break;
			}
		}

		switch (this->m_pTheApp->RandInt(1, 4))
		{
		case 1:
			weapon->SetBulletPlace(CWeaponBoss1Laser::eBULLET_PLACE_3);
			break;
		case 2:
			weapon->SetBulletPlace(CWeaponBoss1Laser::eBULLET_PLACE_1);
			break;
		case 3:
			weapon->SetBulletPlace(CWeaponBoss1Laser::eBULLET_PLACE_4);
			break;
		case 4:
			weapon->SetBulletPlace(CWeaponBoss1Laser::eBULLET_PLACE_2);
			break;
		}

		weapon->InitRotation();
		weapon->SetPosition(framePos);
		weapon->InitPosition();

		weapon->SetOwner(CWeapon::eOWNER_BOSS);

		this->m_pBullets.Push(weapon);

		// play sound effect

		DWORD dwSoundIndex = SOUND_SHOOT_BOSS_1_LASER_SMALL_1;

		switch (this->m_eSoundFiring)
		{
		case eSOUND_FIRING_NORMAL_2:
			dwSoundIndex = SOUND_SHOOT_BOSS_1_LASER_SMALL_3;
			break;
		case eSOUND_FIRING_QUIET_1:
			dwSoundIndex = SOUND_SHOOT_BOSS_1_LASER_SMALL_2;
			break;
		case eSOUND_FIRING_QUIET_2:
			dwSoundIndex = SOUND_SHOOT_BOSS_1_LASER_SMALL_4;
			break;
		}

		this->m_pTheApp->GetWave(dwSoundIndex).Play(
			FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);

		ChangeFiringSound();
	}
}

HRESULT CEnemyBoss1Laser::InitWeapons(	CTheApp* pTheApp,
										LPD3DXMESH mesh,
										std::vector<D3DMATERIAL9*> materials,
										std::vector<LPDIRECT3DTEXTURE9> textures,
										float fLaserWidth,
										float fLaserHeight,
										float fLaserSpeed,
										int iLaserDamage)
{
	HRESULT hres;

	this->m_pLaser = new CWeaponBoss1Laser();

	if( !this->m_pLaser )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pLaser->Create(	pTheApp->GetDevice(),
									mesh,
									materials,
									textures,
									fLaserWidth,
									fLaserHeight,
									fLaserSpeed,
									iLaserDamage,
									CWeapon::eBULLET_TYPE_BOSS_1_LASER);
	if( FAILED(hres) )
	{
		return hres;
	}

	hres = this->m_pLaser->CreateCollisionMesh();

	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

HRESULT CEnemyBoss1Laser::InitWeapons(	CTheApp* pTheApp,
										LPD3DXMESH mesh,
										std::vector<MESHDATA>& meshData,
										float fLaserWidth,
										float fLaserHeight,
										float fLaserSpeed,
										int iLaserDamage)
{
	HRESULT hres;

	this->m_pLaser = new CWeaponBoss1Laser();

	if( !this->m_pLaser )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pLaser->Create(	pTheApp->GetDevice(),
									mesh,
									meshData,
									fLaserWidth,
									fLaserHeight,
									fLaserSpeed,
									iLaserDamage,
									CWeapon::eBULLET_TYPE_BOSS_1_LASER);
	if( FAILED(hres) )
	{
		return hres;
	}

	hres = this->m_pLaser->CreateCollisionMesh();

	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

void CEnemyBoss1Laser::MoveEnter(float fFrametime, float fPlayerVelocity)
{
}