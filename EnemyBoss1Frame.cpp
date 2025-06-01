#include "GameSettings.h"
#include "EnemyBoss1Frame.h"

CEnemyBoss1Frame::CEnemyBoss1Frame(	eTYPE eType,
									eBEHAVIOUR eBehaviour)
{
	this->m_pLaserLeft = NULL;
	this->m_pLaserRight = NULL;

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

void CEnemyBoss1Frame::SetLaserObjects(CEnemyBoss1Laser* pLaserLeft, CEnemyBoss1Laser* pLaserRight)
{
	this->m_pLaserLeft = pLaserLeft;
	this->m_pLaserRight = pLaserRight;
}

void CEnemyBoss1Frame::Release()
{
	CEnemyBoss::Release();
}

void CEnemyBoss1Frame::UpdateShip(bool bShootPossible, float fFrametime)
{
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
						// randomize next attack mode
						this->SetRandAttack();
					}
				}
				else
				{
					// small lasers are waiting, can start counting for the next shooting
					if (IsSmallLaserReady())
					{
						this->SetShootCount(true);
					}
				}
			}

			break;

		case eACTION_SMALL_LASER:

			if (IsSmallLaserReady())
			{
				if (this->m_pLaserLeft->IsActive())
				{
					this->m_pLaserLeft->SetAction(CEnemyBoss1Laser::eACTION_TURN);
				}
				if (this->m_pLaserRight->IsActive())
				{
					this->m_pLaserRight->SetAction(CEnemyBoss1Laser::eACTION_TURN);
				}

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
		if (this->m_pLaserLeft || this->m_pLaserRight)
		{
			this->m_eAction = eACTION_SMALL_LASER;
		}
		break;

	case 2:
		this->m_eAction = eACTION_BIG_LASER_CHARGE;
		break;
	}
}

bool CEnemyBoss1Frame::IsSmallLaserReady()
{
	if (!this->m_pLaserLeft || !this->m_pLaserRight)
	{
		return false;
	}

	if (this->m_pLaserLeft->IsActive() && this->m_pLaserRight->IsActive() &&
		this->m_pLaserLeft->GetAction() == CEnemyBoss1Laser::eACTION_WAIT &&
		this->m_pLaserRight->GetAction() == CEnemyBoss1Laser::eACTION_WAIT)
	{
		return true;
	}
	else if (this->m_pLaserLeft->IsActive() &&
		this->m_pLaserLeft->GetAction() == CEnemyBoss1Laser::eACTION_WAIT)
	{
		return true;
	}
	else if (this->m_pLaserRight->IsActive() &&
		this->m_pLaserRight->GetAction() == CEnemyBoss1Laser::eACTION_WAIT)
	{
		return true;
	}

	return false;
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
