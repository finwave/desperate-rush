#include "EnemyBoss1Scatter.h"

CEnemyBoss1Scatter::CEnemyBoss1Scatter(	eTYPE eType,
										eBEHAVIOUR eBehaviour,
										eSIDE eSide)
{
	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
	this->m_eSide = eSide;

	this->m_eAction = eACTION_WAIT;

	this->m_pBullet = NULL;

	this->m_fAngleZ = 0.0f;
	this->m_fRotationIncrease = 0.0f;

	this->m_bMoveDown = true;
	this->m_fOriginalYPos = 0.0f;
	this->m_fCurrentYPos = 0.0;

	this->m_fShootMultiTime = 0.0f;
	this->m_fShootMultiTimer = 0.0f;

	this->m_iShootMultiMax = 0;
	this->m_iShootMulti = 0;
	this->m_iShootMultiCount = 0;

	this->GenerateRandomShootTime();
}

CEnemyBoss1Scatter::~CEnemyBoss1Scatter(void)
{
}

HRESULT CEnemyBoss1Scatter::Create(	CTheApp* pTheApp,
									CGameSettings* pGameSettings,
									IEnemy* pBossFrame,
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

	// set enemy score
	this->InitScores();

	// set initial position
	this->InitPosition(pBossFrame->GetPosition());

	// sound effect volume
	int iVolume = pTheApp->GetConfig().GetVolumeSoundEffect();

	if (iVolume == 0)
	{
		this->m_iVolumeSoundEffect = -10000;
	}
	else
	{
		float fVolume = pGameSettings->m_fVolumeBossScatter * (float)iVolume;
		float fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumeSoundEffect = (int)fExactVolume;
	}

	return S_OK;
}

void CEnemyBoss1Scatter::Init(	CTheApp* pTheApp,
								CGameSettings* pGameSettings,
								CSprite* pSpriteAfterburn,
								int iVolumeSoundEffect)
{
	this->m_bBoss = true;

	this->m_fEnemyWidth = pGameSettings->m_fEnemyBoss1ScatterWidth;
	this->m_fEnemyHeight = pGameSettings->m_fEnemyBoss1ScatterHeight;

	this->m_iHealth = pGameSettings->m_iEnemyBoss1ScatterHealth;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = pGameSettings->m_fEnemyBoss1ScatterSpeed;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fShootTime = pGameSettings->m_fEnemyBoss1ScatterShootTime;
	this->m_iShootMultiMax = 40;

	// firing possible as soon as boss has entered
	this->m_fShootCounter = this->m_fShootTime + this->m_fRandShootTime;

	this->m_fRotationIncrease = 0.14f;

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);
}

void CEnemyBoss1Scatter::Release()
{
	if(this->m_pBullet)
	{
		this->m_pBullet->Release();
		delete this->m_pBullet;
		this->m_pBullet = NULL;
	}

	CEnemyBoss::Release();
}

void CEnemyBoss1Scatter::UpdateShip(IEnemy* pBossFrame,
									bool bShootPossible,
									float fBottomBorder,
									float fFrametime)
{
	// rotate as necessary
	this->RotateScatter(pBossFrame);
	// set initial position
	this->InitPosition(pBossFrame->GetPosition());

	if(!this->m_bEnter)
	{
		// these are done only once
		if(this->m_fOriginalYPos == 0.0f)
		{
			this->m_fOriginalYPos = this->GetPosition().y;
			this->m_fCurrentYPos = m_fOriginalYPos;

			this->SetRandAttack();
		}

		// set movement to same as boss core
		this->SetMovement(pBossFrame->GetMovement());

		switch(this->m_eAction)
		{
		case eACTION_WAIT:

			if(bShootPossible)
			{
				if( this->Shoot() )
				{
					// randomize next attack mode
					this->SetRandAttack();
					this->SetShootCount(false);

					this->m_iShootMulti = this->m_pTheApp->RandInt(
						15, this->m_iShootMultiMax);
				}
			}

			break;

		case eACTION_SHOOT:

			if(bShootPossible)
			{
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
					// reset fired bullets count
					this->m_iShootMultiCount = 0;
					// reset sound effect
					this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
					// go to rest mode and wait for the next attack time
					this->m_eAction = eACTION_WAIT;
					this->SetShootCount(true);
				}
			}
			else
			{
				// reset fired bullets count
				this->m_iShootMultiCount = 0;
				// reset sound effect
				this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
				// go to rest mode and wait for the next attack time
				this->m_eAction = eACTION_WAIT;
				this->SetShootCount(true);
			}

			break;

		case eACTION_RUSH_DOWN:

			this->MovementRush(fBottomBorder, fFrametime);

			break;

		case eACTION_RUSH_UP:

			if(this->MovementRush(fBottomBorder, fFrametime))
			{
				if(bShootPossible)
				{
					// fire next multi-shoot bullet
					if(this->m_fShootMultiTimer <= 0.0f)
					{
						// shoot next bullet
						this->ShootWeapons();
						// reset single shot timer
						this->m_fShootMultiTimer = this->m_fShootMultiTime;
					}
					else
					{
						// update single shot timer
						this->m_fShootMultiTimer -= fFrametime;
					}
				}
			}
			else
			{
				// reset sound effect
				this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
				// go to rest mode and wait for the next attack time
				this->m_eAction = eACTION_WAIT;
				this->SetShootCount(true);
			}

			break;
		}
	}

	IEnemy::Update(fFrametime, 0.0f);
}

void CEnemyBoss1Scatter::Render()
{
	IEnemy::Render(this->m_pTheApp->GetDevice());
}

HRESULT CEnemyBoss1Scatter::InitWeapons(CTheApp* pTheApp,
										LPD3DXMESH mesh,
										std::vector<D3DMATERIAL9*> materials,
										std::vector<LPDIRECT3DTEXTURE9> textures,
										float fScatterWidth,
										float fScatterHeight,
										float fScatterSpeed,
										int iScatterDamage)
{
	HRESULT hres;

	this->m_pBullet = new CWeaponBoss1Scatter();
	if( !this->m_pBullet )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pBullet->Create(pTheApp->GetDevice(),
									mesh,
									materials,
									textures,
									fScatterWidth,
									fScatterHeight,
									fScatterSpeed,
									iScatterDamage,
									CWeapon::eBULLET_TYPE_BOSS_1_SCATTER);
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

HRESULT CEnemyBoss1Scatter::InitWeapons(CTheApp* pTheApp,
										LPD3DXMESH mesh,
										std::vector<MESHDATA>& meshData,
										float fScatterWidth,
										float fScatterHeight,
										float fScatterSpeed,
										int iScatterDamage)
{
	HRESULT hres;

	this->m_pBullet = new CWeaponBoss1Scatter();
	if( !this->m_pBullet )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pBullet->Create(pTheApp->GetDevice(),
									mesh,
									meshData,
									fScatterWidth,
									fScatterHeight,
									fScatterSpeed,
									iScatterDamage,
									CWeapon::eBULLET_TYPE_BOSS_1_SCATTER);
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

void CEnemyBoss1Scatter::ShootWeapons()
{
	CWeapon* weapon = NULL;
	weapon = new CWeaponBoss1Scatter();

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

		weapon->SetOwner(CWeapon::eOWNER_BOSS);
		weapon->SetPosition(this->GetPosition());

		switch (this->m_eAction)
		{
			// normal attack mode
		case eACTION_SHOOT:

			switch (this->m_pTheApp->RandInt(1, 7))
			{
			case 1:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN);
				break;
			case 2:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT_LEFT);
				break;
			case 3:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT);
				break;
			case 4:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_DOWN_RIGHT);
				break;
			case 5:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_DOWN_LEFT);
				break;
			case 6:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT);
				break;
			case 7:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT_RIGHT);
				break;
			}

			break;

			// rush attack mode
		case eACTION_RUSH_UP:

			switch (this->m_pTheApp->RandInt(1, 9))
			{
			case 1:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN);
				break;
			case 2:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT_LEFT);
				break;
			case 3:
				weapon->SetDirection(CWeapon::eDIRECTION_RIGHT);
				break;
			case 4:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_DOWN_LEFT);
				break;
			case 5:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT);
				break;
			case 6:
				weapon->SetDirection(CWeapon::eDIRECTION_LEFT);
				break;
			case 7:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_RIGHT_RIGHT);
				break;
			case 8:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_LEFT);
				break;
			case 9:
				weapon->SetDirection(CWeapon::eDIRECTION_DOWN_DOWN_RIGHT);
				break;
			}

			break;
		}

		weapon->InitPosition();

		this->m_pBullets.Push(weapon);

		// play sound effect

		if (this->m_eSoundFiring == eSOUND_FIRING_NORMAL_1)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_SCATTER_1).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_NORMAL_2)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_SCATTER_3).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_QUIET_1)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_SCATTER_2).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}
		else if (this->m_eSoundFiring == eSOUND_FIRING_QUIET_2)
		{
			this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_SCATTER_4).Play(
				FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
		}

		this->ChangeFiringSound();
	}
}

void CEnemyBoss1Scatter::SetRandAttack()
{
	// randomize next attack

	switch(this->m_pTheApp->RandInt(1,2))
	{
	case 1:

		this->m_eAction = eACTION_SHOOT;
		this->m_fShootMultiTime = 0.11f;
		this->m_fShootMultiTimer = 0.0f;

		break;

	case 2:

		this->m_eAction = eACTION_RUSH_DOWN;
		this->m_fShootMultiTime = 0.06f;
		this->m_fShootMultiTimer = 0.0f;

		break;
	}
}

void CEnemyBoss1Scatter::RotateScatter(IEnemy* pBossFrame)
{
	this->SetRotateY(pBossFrame->GetAngleY());

	switch(this->m_eAction)
	{
	case eACTION_WAIT:
		this->m_fAngleZ += this->m_fRotationIncrease * 0.4f;
		break;

	case eACTION_SHOOT:
		this->m_fAngleZ += this->m_fRotationIncrease;
		break;

	case eACTION_RUSH_DOWN:
		this->m_fAngleZ += this->m_fRotationIncrease * 0.7f;
		break;

	case eACTION_RUSH_UP:
		this->m_fAngleZ += this->m_fRotationIncrease * 1.10f;
		break;
	}

	switch(this->m_eSide)
	{
	case eSIDE_LEFT:
		this->SetRotateZ(this->m_fAngleZ);
		break;

	case eSIDE_RIGHT:
		this->SetRotateZ(-this->m_fAngleZ);
		break;
	}
}

void CEnemyBoss1Scatter::SetMovement(eMOVE eMove)
{
	this->m_eMove = eMove;
}

bool CEnemyBoss1Scatter::MovementRush(	float fBottomBorder,
										float fFrametime)
{
	D3DXVECTOR3 pos = this->GetPosition();

	const float fOriginalYPos = pos.y;

	float fMove = this->m_fSpeed * fFrametime;
	fBottomBorder = -fBottomBorder;

	bool bIsMoving = true;

	// scatter moves down towards bottom border
	if(this->m_bMoveDown)
	{
		// scatter needs to move down on default speed
		if((this->m_fCurrentYPos -  fMove) > fBottomBorder)
		{
			this->m_fCurrentYPos -= fMove;
		}
		// scatter needs to move down less than default speed
		else
		{
			this->m_fCurrentYPos += (-fBottomBorder + this->m_fCurrentYPos);

			this->m_bMoveDown = false;
			this->m_eAction = eACTION_RUSH_UP;
		}
		pos.y = this->m_fCurrentYPos;
		this->SetPosition(pos);
	}
	// scatter moves up to it's original y-axel position
	else
	{
		// scatter needs to move up on default speed
		if((this->m_fCurrentYPos +  fMove) < fOriginalYPos)
		{
			this->m_fCurrentYPos += fMove;
		}
		// scatter needs to move up less than default speed
		else
		{
			this->m_fCurrentYPos += (fOriginalYPos - this->m_fCurrentYPos);

			this->m_bMoveDown = true;
			bIsMoving = false;

		}
		pos.y = this->m_fCurrentYPos;
		this->SetPosition(pos);
	}

	return bIsMoving;
}

void CEnemyBoss1Scatter::InitPosition(D3DXVECTOR3 posFrame)
{
	D3DXVECTOR3 pos = posFrame;

	switch(this->m_eSide)
	{
	case eSIDE_LEFT:

		pos.x -= 25.325f;
		pos.y += 12.272f;
		pos.z -= 30.0f;

		break;

	case eSIDE_RIGHT:

		pos.x += 25.325f;
		pos.y += 12.272f;
		pos.z -= 30.0f;

		break;
	}

	this->SetPosition(pos);
}

void CEnemyBoss1Scatter::MoveEnter(float fFrametime, float fPlayerVelocity)
{
}