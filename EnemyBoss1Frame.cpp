#include "GameSettings.h"
#include "Level.h"
#include "EnemyBoss1Frame.h"

CEnemyBoss1Frame::CEnemyBoss1Frame(	eTYPE eType,
									eBEHAVIOUR eBehaviour)
{
	this->m_pEnemyBossSideLasersController = NULL;

	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
	this->m_eAction = eACTION_WAIT;

	this->GenerateRandomShootTime();
}

CEnemyBoss1Frame::~CEnemyBoss1Frame(void)
{
}

HRESULT CEnemyBoss1Frame::Create(CTheApp* pTheApp,
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

	this->InitScores();

	return S_OK;
}

void CEnemyBoss1Frame::CreateSideLasersController(CLevel* pLevel, CEnemyBoss1Laser* pLaserLeft, CEnemyBoss1Laser* pLaserRight)
{
	this->m_pEnemyBossSideLasersController = new CEnemyBossSideLasersController();
	this->m_pEnemyBossSideLasersController->Create(this->m_pTheApp, pLevel, this, pLaserLeft, pLaserRight);
}

void CEnemyBoss1Frame::Init(CTheApp* pTheApp,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect)
{
	this->m_fEnemyWidth = CGameSettings::ENEMY_BOSS_FRAME_WIDTH;
	this->m_fEnemyHeight = CGameSettings::ENEMY_BOSS_FRAME_HEIGHT;

	this->m_iHealth = CGameSettings::ENEMY_BOSS_FRAME_HEALTH;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = CGameSettings::ENEMY_BOSS_FRAME_SPEED;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fShootTime = CGameSettings::ENEMY_BOSS_FRAME_SHOOT_TIME;

	// fire as soon as possible
	this->m_fShootCounter = this->m_fShootTime + this->m_fRandShootTime;

	this->m_bBoss = true;

	IEnemy::Init(pTheApp, pSpriteAfterburn, iVolumeSoundEffect);
}

void CEnemyBoss1Frame::Release()
{
	if (this->m_pEnemyBossSideLasersController)
	{
		delete this->m_pEnemyBossSideLasersController;
		this->m_pEnemyBossSideLasersController = NULL;
	}

	CEnemyBoss::Release();
}

void CEnemyBoss1Frame::UpdateShip(float fFrametime, bool bShootPossible)
{
	this->m_pEnemyBossSideLasersController->Update(fFrametime, bShootPossible);

	if(!this->m_bEnter)
	{
		switch(this->m_eAction)
		{
		case eACTION_WAIT:

			if(bShootPossible)
			{
				// can update shoot counter
				if( this->GetShootCount() )
				{
					if( this->Shoot() )
					{
						this->SetShootCount(false);
						// select next random attack
						this->SetRandAttack();
					}
				}
				else
				{
					// side laser weapons are ready, can start counting for the next random attack
					if (this->m_pEnemyBossSideLasersController)
					{
						if (this->m_pEnemyBossSideLasersController->IsReady())
						{
							this->SetShootCount(true);
						}
					}
					else
					{
						this->SetShootCount(true);
					}
				}
			}

			break;

		case eACTION_SMALL_LASER:

			if (this->m_pEnemyBossSideLasersController)
			{
				if (this->m_pEnemyBossSideLasersController->IsReady())
				{
					this->m_pEnemyBossSideLasersController->Activate();
					this->m_eAction = eACTION_WAIT;
				}
			}
			else
			{
				this->m_eAction = eACTION_WAIT;
			}

			break;

		case eACTION_BIG_LASER_CHARGE:

			this->BigLaserCharge();
			
			break;

		case eACTION_BIG_LASER_FIRE:

			this->BigLaserFire(fFrametime);

			break;
		}
	}

	IEnemy::Update(fFrametime, 0.0f);
}

void CEnemyBoss1Frame::Render()
{
	IEnemy::Render(this->m_pTheApp->GetDevice());
}

void CEnemyBoss1Frame::BigLaserCharge()
{
}

void CEnemyBoss1Frame::BigLaserFire(float fFrametime)
{
}

void CEnemyBoss1Frame::SetRandAttack()
{
	int randAction = 1;
	//int iRandAction = this->m_pTheApp->RandInt(1, 2);

	switch(randAction)
	{
	case 1:
		this->m_eAction = eACTION_SMALL_LASER;
		break;

	case 2:
		this->m_eAction = eACTION_BIG_LASER_CHARGE;
		break;
	}
}

void CEnemyBoss1Frame::MoveEnter(float fFrametime, float fPlayerVelocity)
{
	D3DXVECTOR3 pos = this->GetPosition();
	float fFrameSpeed = fFrametime * (this->m_fSpeed / 1.2f);

	float fMovementBorder = this->m_fScreenHeight - (this->GetHeight() / 1.8f);

	if( pos.y < fMovementBorder )
	{
		this->m_bEnter = false;

		this->m_eMove = IEnemy::eMOVE_STAY;
		this->SetMoveState();
		this->GenerateRandomMoveTime();
	}
	else
	{
		pos.y -= fFrameSpeed;
		this->SetPosition(pos);
	}
}

void CEnemyBoss1Frame::Move(float fFrametime, float fPlayerVelocity)
{
	float fMovementBorder = 0.0f;

	// get enemy's position to temp vector
	D3DXVECTOR3 pos = this->GetPosition();

	// enemy's movement speed
	float fFrameSpeed = fFrametime * this->m_fSpeed;

	// change movement
	if( this->m_fMoveTime <= 0.0f )
	{
		this->SetMoveState();
		this->GenerateRandomMoveTime();
	}

	// move accordingly
	switch(this->m_eMove)
	{
	// stay put
	case IEnemy::eMOVE_STAY:

		break;
	
	// move left
	case IEnemy::eMOVE_LEFT:

		fMovementBorder = -this->m_fScreenWidth + (this->GetWidth() / 2);

		if(pos.x < fMovementBorder)
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}
		else
		{
			pos.x -= fFrameSpeed;
		}

		break;

	// move right
	case IEnemy::eMOVE_RIGHT:	

		fMovementBorder = this->m_fScreenWidth - (this->GetWidth() / 2);

		if(pos.x > fMovementBorder)
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}
		else
		{
			pos.x += fFrameSpeed;
		}

		break;
	}

	this->SetPosition(pos);
}
