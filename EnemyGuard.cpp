#include "EnemyGuard.h"

CEnemyGuard::CEnemyGuard(eTYPE eType, eBEHAVIOUR eBehaviour)
{
	this->m_fMoveTime = 0.0f;
	this->m_fShootTime = 0.0f;
	this->m_fRandShootTime = 0.0f;
	this->m_fShootCounter = 0.0f;
	this->m_fFleeTime = 0.0f;
	this->m_fFleeCounter = 0.0f;
	this->m_fSpeedEnter = 0.0f;

	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;
}

CEnemyGuard::~CEnemyGuard(void)
{
}

void CEnemyGuard::Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect)
{
	switch (this->m_eBehaviour)
	{
	case eBEHAVIOUR::eBEHAVIOUR_LAUNCH:
		this->m_fSpeed = pGameSettings->m_fEnemyGuardLaunchSpeed;
		this->m_fShootTime = pGameSettings->m_fEnemyGuardLaunchShootTime;
		break;
	case eBEHAVIOUR::eBEHAVIOUR_STRIKE:
		this->m_fSpeed = pGameSettings->m_fEnemyGuardStrikeSpeed;
		this->m_fShootTime = pGameSettings->m_fEnemyGuardStrikeShootTime;
		break;
	}

	this->m_bEnterSound = true;
	this->m_bFleeSound = true;

	this->m_fEnemyWidth = pGameSettings->m_fEnemyGuardWidth;
	this->m_fEnemyHeight = pGameSettings->m_fEnemyGuardHeight;

	this->m_iHealth = pGameSettings->m_iEnemyGuardHealth;

	this->m_iHealthMax = this->m_iHealth;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fFleeSpeedIncrease = 0.008f;

	this->InitScores();

	this->GenerateRandomMoveTime();
	this->GenerateRandomShootTime();

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);
}

bool CEnemyGuard::Shoot()
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

void CEnemyGuard::Move(float fFrametime, float fPlayerVelocity)
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

void CEnemyGuard::SetMoveState(void)
{
	D3DXVECTOR3 pos = this->GetPosition();
	float fBottomMoveBorder = this->m_fMovementBorderY + (this->m_fEnemyHeight / 2.0f);

	switch (this->m_eBehaviour)
	{
	case IEnemy::eBEHAVIOUR_LAUNCH:
	{
		int randChoice = this->m_pTheApp->RandInt(1, 9);

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

			if (this->m_eMove == IEnemy::eMOVE_STAY)
			{
				this->SetMoveState();
			}
			else
			{
				// set new movement direction
				this->m_eMove = IEnemy::eMOVE_STAY;
			}
			break;

		case 7:

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

		case 9:

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
