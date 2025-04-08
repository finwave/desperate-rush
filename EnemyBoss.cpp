#include "EnemyBoss.h"

CEnemyBoss::CEnemyBoss()
{
	this->m_pBullets.Clear();

	this->m_fMoveTime = 0.0f;
	this->m_fShootTime = 0.0f;
	this->m_fRandShootTime = 0.0f;
	this->m_fShootCounter = 0.0f;
	this->m_fFleeTime = 0.0f;
	this->m_fFleeCounter = 0.0f;
	this->m_fSpeedEnter = 0.0f;

	this->m_iVolumeSoundEffect = 0;
}

CEnemyBoss::~CEnemyBoss(void)
{
}

void CEnemyBoss::Release()
{
	IEnemy::Release();
}

bool CEnemyBoss::Shoot()
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

void CEnemyBoss::SetMoveState(void)
{
	switch( this->m_eType )
	{
	case IEnemy::eTYPE_BOSS_1_FRAME:

		if( this->m_eMove == IEnemy::eMOVE_STAY )
		{
			switch(this->m_pTheApp->RandInt(1,2))
			{
			case 1:
				this->m_eMove = IEnemy::eMOVE_LEFT;
				break;
			case 2:
				this->m_eMove = IEnemy::eMOVE_RIGHT;
				break;
			}
		}
		else if( this->m_eMove == IEnemy::eMOVE_LEFT )
		{
			this->m_eMove = IEnemy::eMOVE_RIGHT;
		}
		else if( this->m_eMove == IEnemy::eMOVE_RIGHT )
		{
			this->m_eMove = IEnemy::eMOVE_LEFT;
		}

		break;
	}
	/*
	else
	{
		switch(this->m_pTheApp->RandInt(1,5))
		{
		case 1:
			if( this->m_eMove == IEnemy::eMOVE_STAY )
			{
				this->SetMoveState();
			}
			else
			{
				this->m_eMove = IEnemy::eMOVE_STAY;
			}
			break;
		case 2:
			if( this->m_eMove == IEnemy::eMOVE_UP )
			{
				this->SetMoveState();
			}
			else
			{
				this->m_eMove = IEnemy::eMOVE_UP;
			}
			break;
		case 3:
			if( this->m_eMove == IEnemy::eMOVE_DOWN )
			{
				this->SetMoveState();
			}
			else
			{
				this->m_eMove = IEnemy::eMOVE_DOWN;
			}
			break;
		case 4:
			if( this->m_eMove == IEnemy::eMOVE_LEFT )
			{
				this->SetMoveState();
			}
			else
			{
				this->m_eMove = IEnemy::eMOVE_LEFT;
			}
			break;
		case 5:
			if( this->m_eMove == IEnemy::eMOVE_RIGHT )
			{
				this->SetMoveState();
			}
			else
			{
				this->m_eMove = IEnemy::eMOVE_RIGHT;
			}
			break;
		}
	}
	*/
}
