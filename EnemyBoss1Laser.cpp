#include "EnemyBoss1Laser.h"

CEnemyBoss1Laser::CEnemyBoss1Laser(	eTYPE eType,
									eBEHAVIOUR eBehaviour,
									eSIDE eSide)
{
	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
	this->m_eSide = eSide;
	this->m_eAction = eACTION_WAIT;
	this->m_eDirection = eDIRECTION_FRONT;

	this->m_pLaser = NULL;

	this->m_fShootMultiTime = 0.0f;
	this->m_fShootMultiTimer = 0.0f;

	this->m_iShootMultiMax = 0;
	this->m_iShootMulti = 0;
	this->m_iShootMultiCount = 0;

	this->m_bRotateLaser = true;

	this->m_fAngleZ = 0.0f;
	this->m_fAngleMaxZ = 0.0f;

	this->GenerateRandomShootTime();
}

CEnemyBoss1Laser::~CEnemyBoss1Laser(void)
{
}

HRESULT CEnemyBoss1Laser::Create(	CTheApp* pTheApp,
									CGameSettings* pGameSettings,
									LPD3DXMESH mesh,
									std::vector<D3DMATERIAL9*> materials,
									std::vector<LPDIRECT3DTEXTURE9> textures,
									int iVolumeSoundEffect)
{
	HRESULT hres;

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

	// sound effect volume
	int iVolume = pTheApp->GetConfig().GetVolumeSoundEffect();

	if (iVolume == 0)
	{
		this->m_iVolumeSoundEffect = -10000;
	}
	else
	{
		float fVolume = pGameSettings->m_fVolumeBossLaser * (float)iVolume;
		float fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumeSoundEffect = (int)fExactVolume;
	}

	return S_OK;
}

void CEnemyBoss1Laser::Init(CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect)
{
	this->m_bBoss = true;

	this->m_fEnemyWidth = pGameSettings->m_fEnemyBoss1LaserWidth;
	this->m_fEnemyHeight = pGameSettings->m_fEnemyBoss1LaserHeight;

	this->m_iHealth = pGameSettings->m_iEnemyBoss1LaserHealth;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = 0.0f;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fShootMultiTime = 0.09f;
	this->m_iShootMultiMax = 35;
	this->m_fAngleMaxZ = 0.6f;

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);
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

void CEnemyBoss1Laser::UpdateShip(IEnemy* pBossFrame,
								  bool bShootPossible,
								  bool leftActive,
								  float fFrametime)
{
	if(this->m_bRotateLaser)
	{
		this->RotateLaser(pBossFrame, fFrametime);
	}

	this->InitPosition(pBossFrame->GetPosition());

	if(!this->m_bEnter)
	{
		switch(this->m_eAction)
		{
		case eACTION_TURN:

			if(leftActive)
			{
				if(this->m_eSide == eSIDE_LEFT)
				{
					this->RandomTurn();
				}
			}
			else
			{
				this->RandomTurn();
			}

			this->m_eAction = eACTION_SHOOT;
			this->m_fShootMultiTimer = 0.0f;

			if(this->m_eSide == eSIDE_LEFT)
			{
				this->m_iShootMulti = this->m_pTheApp->RandInt(
					10, this->m_iShootMultiMax);
			}

			break;

		case eACTION_SHOOT:

			if(!m_bRotateLaser)
			{
				if(bShootPossible)
				{
					// current multi-shoot session is not finished
					if(this->m_iShootMultiCount < this->m_iShootMulti)
					{
						// fire next multi-shoot bullet
						if(this->m_fShootMultiTimer <= 0.0f)
						{
							// shoot next bullet
							this->ShootWeapons(pBossFrame->GetPosition());
							// reset single shot timer
							this->m_fShootMultiTimer = this->m_fShootMultiTime;
							// increase the count of fired bullets
							this->m_iShootMultiCount++;
						}
						else
						{
							// update single shot timer
							this->m_fShootMultiTimer -= fFrametime;
						}
					}
					// current multi-shoot session is finished
					else
					{
						// reset fired bullets count
						this->m_iShootMultiCount = 0;
						// reset sound effect
						this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
						// wait for the next attack command
						this->m_eAction = eACTION_WAIT;
					}
				}
				else
				{
					// reset fired bullets count
					this->m_iShootMultiCount = 0;
					// reset sound effect
					this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
					// wait for the next attack command
					this->m_eAction = eACTION_WAIT;
				}
			}

			break;
		}
	}

	IEnemy::Update(fFrametime, 0.0f);
}

void CEnemyBoss1Laser::Render()
{
	IEnemy::Render(this->m_pTheApp->GetDevice());
}

void CEnemyBoss1Laser::RandomTurn()
{
	switch(this->m_pTheApp->RandInt(1,6))
	{
	case 1:

		if(this->m_eDirection == eDIRECTION_DIAGONAL)
		{
			this->m_bRotateLaser = true;
		}

		break;

	case 2:

		if(this->m_eDirection == eDIRECTION_FRONT)
		{
			this->m_bRotateLaser = true;
		}

		break;

	case 3:

		if(this->m_eDirection == eDIRECTION_FRONT)
		{
			this->m_bRotateLaser = true;
		}

		break;

	case 4:

		if(this->m_eDirection == eDIRECTION_DIAGONAL)
		{
			this->m_bRotateLaser = true;
		}

		break;

	case 5:

		if(this->m_eDirection == eDIRECTION_DIAGONAL)
		{
			this->m_bRotateLaser = true;
		}

		break;

	case 6:

		if(this->m_eDirection == eDIRECTION_FRONT)
		{
			this->m_bRotateLaser = true;
		}

		break;
	}
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
		case eDIRECTION_FRONT:

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

		case eDIRECTION_DIAGONAL:

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

		if (this->m_eSoundFiring == eSOUND_FIRING_NORMAL_1)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_LASER_SMALL_1).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_NORMAL_2)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_LASER_SMALL_3).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_QUIET_1)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_LASER_SMALL_2).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_QUIET_2)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_LASER_SMALL_4).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}

		this->ChangeFiringSound();
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

void CEnemyBoss1Laser::RotateLaser(IEnemy* pBossFrame, float fFrametime)
{
	this->SetRotateY(pBossFrame->GetAngleY());

	// rotation speed
	float fRotationSpeed = fFrametime + 0.005f;

	switch(this->m_eDirection)
	{
	// lasers are in closed position
	case eDIRECTION_DIAGONAL:

		// update rotation angle
		this->m_fAngleZ -= fRotationSpeed;

		// reached max rotation
		if(this->m_fAngleZ <= 0.0f)
		{
			this->m_fAngleZ = 0.0f;

			this->m_eDirection = eDIRECTION_FRONT;
			this->m_bRotateLaser = false;
		}

		break;

	// lasers are in open position
	case eDIRECTION_FRONT:

		// update rotation angle
		this->m_fAngleZ += fRotationSpeed;

		// reached max rotation
		if(this->m_fAngleZ >= this->m_fAngleMaxZ)
		{
			this->m_fAngleZ = this->m_fAngleMaxZ;

			this->m_eDirection = eDIRECTION_DIAGONAL;
			this->m_bRotateLaser = false;
		}

		break;
	}

	switch(this->m_eSide)
	{
	// left minigun
	case eSIDE_LEFT:
		this->SetRotateZ(-this->m_fAngleZ);
		break;

	// right minigun
	case eSIDE_RIGHT:
		this->SetRotateZ(this->m_fAngleZ);
		break;
	}
}

void CEnemyBoss1Laser::InitPosition(D3DXVECTOR3 pos)
{
	pos.z -= 7.0f;

	switch(this->m_eSide)
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

	this->SetPosition(pos);
}

void CEnemyBoss1Laser::MoveEnter(float fFrametime, float fPlayerVelocity)
{
}