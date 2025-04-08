#include "EnemyBoss1Frame.h"

CEnemyBoss1Frame::CEnemyBoss1Frame(	eTYPE eType,
									eBEHAVIOUR eBehaviour)
{
	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
	this->m_eAction = eACTION_WAIT;

	this->GenerateRandomShootTime();
}

CEnemyBoss1Frame::~CEnemyBoss1Frame(void)
{
}

HRESULT CEnemyBoss1Frame::Create(	CTheApp* pTheApp,
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

	this->InitScores();

	return S_OK;
}

void CEnemyBoss1Frame::Init(CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect)
{
	this->m_fEnemyWidth = pGameSettings->m_fEnemyBoss1FrameWidth;
	this->m_fEnemyHeight = pGameSettings->m_fEnemyBoss1FrameHeight;

	this->m_iHealth = pGameSettings->m_iEnemyBoss1FrameHealth;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = pGameSettings->m_fEnemyBoss1FrameSpeed;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fShootTime = pGameSettings->m_fEnemyBoss1FrameShootTime;

	// fire as soon as possible
	this->m_fShootCounter = this->m_fShootTime + this->m_fRandShootTime;

	this->m_bBoss = true;

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);
}

void CEnemyBoss1Frame::Release()
{
	CEnemyBoss::Release();
}

void CEnemyBoss1Frame::UpdateShip(	CEnemyBoss1Laser* pLaserLeft,
									CEnemyBoss1Laser* pLaserRight,
									bool bShootPossible,
									float fFrametime)
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
					if(pLaserLeft->IsActive() && pLaserRight->IsActive())
					{
						// small lasers are waiting, can start counting for the next shooting
						if( (pLaserLeft->GetAction() == CEnemyBoss1Laser::eACTION_WAIT) && 
							(pLaserRight->GetAction() == CEnemyBoss1Laser::eACTION_WAIT))
						{
							this->SetShootCount(true);
						}
					}
					else if(pLaserLeft->IsActive() && 
							pLaserLeft->GetAction() == CEnemyBoss1Laser::eACTION_WAIT)
					{
						this->SetShootCount(true);
					}
					else if(pLaserRight->IsActive() && 
							pLaserRight->GetAction() == CEnemyBoss1Laser::eACTION_WAIT)
					{
						this->SetShootCount(true);
					}
				}
			}

			break;

		case eACTION_SMALL_LASER:

			if(pLaserLeft->IsActive())
			{
				pLaserLeft->SetAction(CEnemyBoss1Laser::eACTION_TURN);
			}
			if(pLaserRight->IsActive())
			{
				pLaserRight->SetAction(CEnemyBoss1Laser::eACTION_TURN);
			}

			this->m_eAction = eACTION_WAIT;

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
	// randomize next attack

	switch(1)
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
