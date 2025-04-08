#include "EnemyRoller.h"

CEnemyRoller::CEnemyRoller(eTYPE eType, eBEHAVIOUR eBehaviour)
{
	this->m_fMoveTime = 0.0f;
	this->m_fShootTime = 0.0f;
	this->m_fRandShootTime = 0.0f;
	this->m_fShootCounter = 0.0f;
	this->m_fFleeTime = 0.0f;
	this->m_fFleeCounter = 0.0f;
	this->m_fSpeedEnter = 0.0f;

	this->m_pBullet = NULL;

	this->m_iVolumeShootRoller = 0;

	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
}

CEnemyRoller::~CEnemyRoller(void)
{
	if(this->m_pBullet)
	{
		this->m_pBullet->Release();
		delete this->m_pBullet;
		this->m_pBullet = NULL;
	}
}

void CEnemyRoller::Init(CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect)
{
	switch (this->m_eBehaviour)
	{
	case eBEHAVIOUR::eBEHAVIOUR_LAUNCH:
		this->m_fSpeed = pGameSettings->m_fEnemyRollerLaunchSpeed;
		this->m_fShootTime = pGameSettings->m_fEnemyRollerLaunchShootTime;
		break;
	case eBEHAVIOUR::eBEHAVIOUR_STRIKE:
		this->m_fSpeed = pGameSettings->m_fEnemyRollerStrikeSpeed;
		this->m_fShootTime = pGameSettings->m_fEnemyRollerStrikeShootTime;
		break;
	}

	this->m_bEnterSound = true;
	this->m_bFleeSound = true;

	this->m_fEnemyWidth = pGameSettings->m_fEnemyRollerWidth;
	this->m_fEnemyHeight = pGameSettings->m_fEnemyRollerHeight;

	this->m_iHealth = pGameSettings->m_iEnemyRollerHealth;

	this->m_iHealthMax = this->m_iHealth;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fFleeSpeedIncrease = 0.01f;

	this->m_fShootMultiTime = 0.09f;
	this->m_fShootMultiTimer = 0.0f;

	this->m_iShootMultiMax = pGameSettings->m_iEnemyBoss1ScatterShootMultiMax;
	this->m_iShootMulti = 0;
	this->m_iShootMultiCount = 0;

	this->m_eRollerAction = eROLLER_ACTION_PASSIVE;

	this->InitScores();

	this->GenerateRandomMoveTime();
	this->GenerateRandomShootTime();

	this->ChangeRotationZ();

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);

	// sound effect volume for shooting
	int iVolume = pTheApp->GetConfig().GetVolumeSoundEffect();

	if (iVolume == 0)
	{
		this->m_iVolumeShootRoller = -10000;
	}
	else
	{
		float fVolume = pGameSettings->m_fVolumeEnemyShootRoller * (float)iVolume;
		float fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumeShootRoller = (int)fExactVolume;
	}
}

void CEnemyRoller::Update(float fFrametime, float fPlayerVelocity)
{
	if (this->m_eBehaviour != IEnemy::eBEHAVIOUR_REINFORCEMENT)
	{
		if(	(this->m_bEnter == false) && (this->m_bFleeMovement == false) )
		{
			switch(this->m_eRollerAction)
			{
			case eROLLER_ACTION_PASSIVE:

				if( this->Shoot() )
				{
					this->m_iShootMulti = this->m_pTheApp->RandInt(15, this->m_iShootMultiMax);

					this->SetShootCount(false);
					this->ChangeRotationZ();

					this->m_eRollerAction = eROLLER_ACTION_ATTACK;
				}

				break;

			case eROLLER_ACTION_ATTACK:

				// current multi-shoot session is not finished
				if(this->m_iShootMultiCount < m_iShootMulti)
				{
					// fire next multi-shoot bullet
					if(this->m_fShootMultiTimer <= 0.0f)
					{
						// shoot next bullet
						this->ShootWeapons();
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
					// reset multi-shoot timer
					this->m_fShootMultiTimer = 0.0f;
					// reset fired bullets count
					this->m_iShootMultiCount = 0;
					// reset sound effect
					this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
					// go to rest mode and wait for the next attack time
					this->m_eRollerAction = eROLLER_ACTION_PASSIVE;
					this->SetShootCount(true);
					this->ChangeRotationZ();
				}

				break;
			}
		}
	}

	IEnemy::Update(fFrametime, fPlayerVelocity);
}

bool CEnemyRoller::Shoot()
{
	if(this->m_fShootCounter >= (this->m_fShootTime + this->m_fRandShootTime))
	{
		this->GenerateRandomShootTime();
		this->m_fShootCounter = 0.0f;

		return true;
	}
	else
	{
		return false;
	}
}

void CEnemyRoller::ShootWeapons()
{
	CWeapon* weapon = NULL;
	weapon = new CWeaponEnemyRoller();

	if (weapon)
	{
		weapon->Create(this->m_pTheApp->GetDevice(),
			this->m_pBullet->GetMesh(),
			this->m_pBullet->GetMeshDataArray(),
			this->m_pBullet->GetWidth(),
			this->m_pBullet->GetHeight(),
			this->m_pBullet->GetSpeed(),
			this->m_pBullet->GetDamage(),
			this->m_pBullet->GetBulletType());

		/* COLLISION MODEL */
		weapon->SetCollisionMesh(this->m_pBullet->GetCollisionMesh());

		weapon->SetOwner(CWeapon::eOWNER_ENEMY);
		weapon->SetPosition(this->GetPosition());

		switch (this->m_pTheApp->RandInt(1, 16))
		{
		case 1:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN);
			break;
		case 2:
			weapon->SetDirection(CWeapon::eDIRECTION_UP_RIGHT_RIGHT);
			break;
		case 3:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT);
			break;
		case 4:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT_LEFT);
			break;
		case 5:
			weapon->SetDirection(CWeapon::eDIRECTION_RIGHT);
			break;
		case 6:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN_DOWN_RIGHT);
			break;
		case 7:
			weapon->SetDirection(CWeapon::eDIRECTION_UP_RIGHT);
			break;
		case 8:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN_DOWN_LEFT);
			break;
		case 9:
			weapon->SetDirection(CWeapon::eDIRECTION_LEFT);
			break;
		case 10:
			weapon->SetDirection(CWeapon::eDIRECTION_UP_LEFT_LEFT);
			break;
		case 11:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT);
			break;
		case 12:
			weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT_RIGHT);
			break;
		case 13:
			weapon->SetDirection(CWeapon::eDIRECTION_UP);
			break;
		case 14:
			weapon->SetDirection(CWeapon::eDIRECTION_UP_UP_LEFT);
			break;
		case 15:
			weapon->SetDirection(CWeapon::eDIRECTION_UP_LEFT);
			break;
		case 16:
			weapon->SetDirection(CWeapon::eDIRECTION_UP_UP_RIGHT);
			break;
		}

		weapon->InitPosition();

		this->m_pBullets.Push(weapon);

		// play sound effect

		if (this->m_eSoundFiring == eSOUND_FIRING_NORMAL_1)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_ROLLER_1).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeShootRoller);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_NORMAL_2)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_ROLLER_3).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeShootRoller);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_QUIET_1)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_ROLLER_2).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeShootRoller);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_QUIET_2)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_ROLLER_4).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeShootRoller);
		}

		this->ChangeFiringSound();
	}
}

HRESULT CEnemyRoller::InitWeapons(	CTheApp* pTheApp,
									LPD3DXMESH mesh,
									std::vector<D3DMATERIAL9*> materials,
									std::vector<LPDIRECT3DTEXTURE9> textures,
									float fBulletWidth,
									float fBulletHeight,
									float fBulletSpeed,
									int iBulletDamage)
{
	HRESULT hres;

	this->m_pBullet = new CWeaponEnemyRoller();
	if( !this->m_pBullet )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pBullet->Create(	pTheApp->GetDevice(),
									mesh,
									materials,
									textures,
									fBulletWidth,
									fBulletHeight,
									fBulletSpeed,
									iBulletDamage,
									CWeapon::eBULLET_TYPE_ENEMY_ROLLER);
	if( FAILED(hres) )
	{
		return hres;
	}

	/* COLLISION MODEL */

	hres = this->m_pBullet->CreateCollisionMesh();
	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

HRESULT CEnemyRoller::InitWeapons(	CTheApp* pTheApp,
									LPD3DXMESH mesh,
									std::vector<MESHDATA>& meshData,
									float fBulletWidth,
									float fBulletHeight,
									float fBulletSpeed,
									int iBulletDamage)
{
	HRESULT hres;

	this->m_pBullet = new CWeaponEnemyRoller();
	if( !this->m_pBullet )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pBullet->Create(	pTheApp->GetDevice(),
									mesh,
									meshData,
									fBulletWidth,
									fBulletHeight,
									fBulletSpeed,
									iBulletDamage,
									CWeapon::eBULLET_TYPE_ENEMY_ROLLER);
	if( FAILED(hres) )
	{
		return hres;
	}

	/* COLLISION MODEL */

	hres = this->m_pBullet->CreateCollisionMesh();
	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

void CEnemyRoller::ChangeRotationZ()
{
	switch(this->m_pTheApp->RandInt(1,4))
	{
	case 1:
		this->m_eRotationZ = eROTATION_Z_LEFT;
		break;
	case 2:
		this->m_eRotationZ = eROTATION_Z_RIGHT;
		break;
	case 3:
		this->m_eRotationZ = eROTATION_Z_RIGHT;
		break;
	case 4:
		this->m_eRotationZ = eROTATION_Z_LEFT;
		break;
	}
}

void CEnemyRoller::Move(float fFrametime, float fPlayerVelocity)
{
	// strike enemy's afterburn sound
	if(this->m_bSoundStrikeAfterburn)
	{
		this->m_bSoundStrikeAfterburn = false;

		switch(this->m_eSoundStrikeAfterburn)
		{
		case eSOUND_STRIKE_AFTERBURN_1:

			this->m_pTheApp->GetWave(SOUND_ENEMY_STRIKE_AFTERBURN_1).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);

			break;

		case eSOUND_STRIKE_AFTERBURN_2:

			this->m_pTheApp->GetWave(SOUND_ENEMY_STRIKE_AFTERBURN_2).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);

			break;

		case eSOUND_STRIKE_AFTERBURN_3:

			this->m_pTheApp->GetWave(SOUND_ENEMY_STRIKE_AFTERBURN_3).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);

			break;

		case eSOUND_STRIKE_AFTERBURN_4:

			this->m_pTheApp->GetWave(SOUND_ENEMY_STRIKE_AFTERBURN_4).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);

			break;
		}
	}

	IEnemy::Move(fFrametime, fPlayerVelocity);
}

void CEnemyRoller::SetMoveState(void)
{
	D3DXVECTOR3 pos = this->GetPosition();
	float fBottomMoveBorder = this->m_fMovementBorderY + (this->m_fEnemyHeight / 2.0f);

	switch (this->m_eBehaviour)
	{
	case IEnemy::eBEHAVIOUR_LAUNCH:
	{
		int randChoice = this->m_pTheApp->RandInt(1, 8);

		if (pos.y <= fBottomMoveBorder)
		{
			randChoice = this->m_pTheApp->RandInt(1, 3);
		}

		switch (randChoice)
		{
		case 1:

			if (this->m_eMove == IEnemy::eMOVE_UP)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_UP;
			}
			break;

		case 2:

			if (this->m_eMove == IEnemy::eMOVE_UP_LEFT)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_UP_LEFT;
			}
			break;

		case 3:

			if (this->m_eMove == IEnemy::eMOVE_UP_RIGHT)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_UP_RIGHT;

			}
			break;

		case 4:

			if (this->m_eMove == IEnemy::eMOVE_LEFT)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_LEFT;
			}
			break;

		case 5:

			if (this->m_eMove == IEnemy::eMOVE_RIGHT)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_RIGHT;
			}
			break;

		case 6:

			if (this->m_eMove == IEnemy::eMOVE_DOWN)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_DOWN;
			}
			break;

		case 7:

			if (this->m_eMove == IEnemy::eMOVE_DOWN_RIGHT)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_DOWN_RIGHT;
			}
			break;

		case 8:

			if (this->m_eMove == IEnemy::eMOVE_DOWN_LEFT)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_DOWN_LEFT;
			}
			break;
		}
	}
	break;

	case IEnemy::eBEHAVIOUR_STRIKE:

		this->m_eMove = IEnemy::eMOVE_DOWN;

		break;

	case IEnemy::eBEHAVIOUR_REINFORCEMENT:

		switch(this->m_eReinforcementAction)
		{
		case eREINFORCEMENT_ACTION_SENT:

			// set new movement direction
			this->m_eMove = IEnemy::eMOVE_STAY;

			break;
		}

		break;

	case eBEHAVIOUR_OBSTACLE:

		switch(this->m_eMove)
		{
		case eMOVE_DOWN:

			if(this->GetPosition().y <= (this->m_fScreenHeight + (this->m_fEnemyHeight / 2)))
			{
				switch(this->m_pTheApp->RandInt(1,3))
				{
				case 1:
					this->m_eMove = eMOVE_DOWN_LEFT;
					break;
				case 2:
					this->m_eMove = eMOVE_DOWN;
					break;
				case 3:
					this->m_eMove = eMOVE_DOWN_RIGHT;
					break;
				}
			}
			
			break;

		case eMOVE_DOWN_LEFT:

			switch(this->m_pTheApp->RandInt(1,2))
			{
			case 1:
				this->m_eMove = eMOVE_DOWN;
				break;
			case 2:
				this->m_eMove = eMOVE_DOWN_RIGHT;
				break;
			}
			
			break;

		case eMOVE_DOWN_RIGHT:

			switch(this->m_pTheApp->RandInt(1,2))
			{
			case 1:
				this->m_eMove = eMOVE_DOWN;
				break;
			case 2:
				this->m_eMove = eMOVE_DOWN_LEFT;
				break;
			}
			
			break;
		}

		break;
	}
}
