#include "../TheApp.h"
#include "../Level.h"
#include "../EnemyBoss1Laser.h"
#include "EnemyBossSideLasersController.h"

CEnemyBossSideLasersController::CEnemyBossSideLasersController(void)
{
	this->m_pTheApp = NULL;
	this->m_pLevel = NULL;
	this->m_pBossFrame = NULL;
	this->m_pLaserLeft = NULL;
	this->m_pLaserRight = NULL;

	this->m_eAction = eACTION::eACTION_READY;
	this->m_eDirection = eDIRECTION::eDIRECTION_FRONT;

	this->m_fPauseTimer = 0.0f;
	this->m_fCurrentAngleZ = 0.0f;
	this->m_fMaxAngleZ = 0.0f;
}

CEnemyBossSideLasersController::~CEnemyBossSideLasersController(void)
{
}

void CEnemyBossSideLasersController::Create(CTheApp* pTheApp,
											CLevel* pLevel,
											IEnemy* pBossFrame,
											CEnemyBoss1Laser* pLaserLeft,
											CEnemyBoss1Laser* pLaserRight)
{
	this->m_pTheApp = pTheApp;
	this->m_pLevel = pLevel;
	this->m_pBossFrame = pBossFrame;
	this->m_pLaserLeft = pLaserLeft;
	this->m_pLaserRight = pLaserRight;

	this->m_fMaxAngleZ = 0.6f;

	InitWeaponRotation();
	SetAction(eACTION::eACTION_READY);
}

void CEnemyBossSideLasersController::Update(float fFrametime, bool bShootPossible)
{
	if (this->m_pLaserLeft && this->m_pLaserLeft->IsActive())
	{
		this->m_pLaserLeft->UpdateShip(fFrametime, bShootPossible);
	}

	if (this->m_pLaserRight && this->m_pLaserRight->IsActive())
	{
		this->m_pLaserRight->UpdateShip(fFrametime, bShootPossible);
	}

	switch (this->m_eAction)
	{
	case eACTION::eACTION_PAUSE:

		this->m_fPauseTimer -= fFrametime;

		if (this->m_fPauseTimer <= 0.0f)
		{
			if (m_pLevel->IsBossBattlePartEnabled(CLevel::BossBattlePart::LASER_STATIONARY))
			{
				SetAction(eACTION_SHOOT_WEAPONS);
			}
			else
			{
				SetAction(eACTION_SELECT_ROTATION);
			}
		}

		break;

	case eACTION::eACTION_SELECT_ROTATION:

		if (SelectRandomRotation())
		{
			SetAction(eACTION_ROTATE_WEAPONS);
		}
		else
		{
			SetAction(eACTION_SHOOT_WEAPONS);
		}

		break;

	case eACTION::eACTION_ROTATE_WEAPONS:

		if (!RotateWeapons(fFrametime))
		{
			SetAction(eACTION_SHOOT_WEAPONS);
		}

		break;

	case eACTION::eACTION_SHOOT_WEAPONS:
	{
		bool bFinishedShooting = true;

		if (this->m_pLaserLeft && this->m_pLaserLeft->IsActive() && this->m_pLaserLeft->IsShooting())
		{
			bFinishedShooting = false;
		}

		if (this->m_pLaserRight && this->m_pLaserRight->IsActive() && this->m_pLaserRight->IsShooting())
		{
			bFinishedShooting = false;
		}

		if (bFinishedShooting)
		{
			SetAction(eACTION::eACTION_READY);
		}
	}
		break;
	}
}

void CEnemyBossSideLasersController::Activate()
{
	SetAction(eACTION::eACTION_PAUSE);
}

void CEnemyBossSideLasersController::SetAction(eACTION eAction)
{
	switch (eAction)
	{
	case eACTION::eACTION_PAUSE:

		this->m_fPauseTimer = this->m_pTheApp->RandFloat(0.0f, 1.25f);

		break;

	case eACTION::eACTION_SHOOT_WEAPONS:
	{
		int shootAmount = this->m_pTheApp->RandInt(10, 35);

		if (this->m_pLaserLeft && this->m_pLaserLeft->IsActive())
		{
			SetShootAction(this->m_pLaserLeft, shootAmount);
		}

		if (this->m_pLaserRight && this->m_pLaserRight->IsActive())
		{
			SetShootAction(this->m_pLaserRight, shootAmount);
		}
	}
		break;
	}

	this->m_eAction = eAction;
}

void CEnemyBossSideLasersController::SetShootAction(CEnemyBoss1Laser* pLaserWeapon, int shootAmount)
{
	pLaserWeapon->SetAction(CEnemyBoss1Laser::eACTION::eACTION_SHOOT_WEAPON);
	pLaserWeapon->SetShootAmountMax(shootAmount);

	switch (this->m_eDirection)
	{
	case eDIRECTION::eDIRECTION_FRONT:
		pLaserWeapon->SetDirection(CEnemyBoss1Laser::eDIRECTION_FRONT);
		break;
	case eDIRECTION::eDIRECTION_DIAGONAL:
		pLaserWeapon->SetDirection(CEnemyBoss1Laser::eDIRECTION_DIAGONAL);
		break;
	}
}

void CEnemyBossSideLasersController::InitWeaponRotation()
{
	if (m_pLevel->IsBossBattlePartEnabled(CLevel::BossBattlePart::LASER_STATIONARY))
	{
		SetFrontRotation();
	}
	else
	{
		SetDiagonalRotation();
	}
}

bool CEnemyBossSideLasersController::SelectRandomRotation()
{
	int iRand = this->m_pTheApp->RandInt(1, 6);

	switch (iRand)
	{
	case 1:
		return (this->m_eDirection == eDIRECTION_DIAGONAL);
	case 2:
		return (this->m_eDirection == eDIRECTION_FRONT);
	case 3:
		return (this->m_eDirection == eDIRECTION_FRONT);
	case 4:
		return (this->m_eDirection == eDIRECTION_DIAGONAL);
	case 5:
		return (this->m_eDirection == eDIRECTION_DIAGONAL);
	case 6:
		return (this->m_eDirection == eDIRECTION_FRONT);
	}

	return false;
}

bool CEnemyBossSideLasersController::RotateWeapons(float fFrametime)
{
	// rotation speed
	float fRotationSpeed = fFrametime + 0.005f;

	switch (this->m_eDirection)
	{
		// lasers are in diagonal position
	case eDIRECTION_DIAGONAL:

		// update rotation angle
		this->m_fCurrentAngleZ -= fRotationSpeed;

		// reached max rotation
		if (this->m_fCurrentAngleZ <= 0.0f)
		{
			SetFrontRotation();
			return false;
		}

		break;

		// lasers are in front position
	case eDIRECTION_FRONT:

		// update rotation angle
		this->m_fCurrentAngleZ += fRotationSpeed;

		// reached max rotation
		if (this->m_fCurrentAngleZ >= this->m_fMaxAngleZ)
		{
			SetDiagonalRotation();
			return false;
		}

		break;
	}

	UpdateRotation();
	return true;
}

void CEnemyBossSideLasersController::SetFrontRotation()
{
	this->m_eDirection = eDIRECTION_FRONT;
	this->m_fCurrentAngleZ = 0.0f;
	UpdateRotation();
}

void CEnemyBossSideLasersController::SetDiagonalRotation()
{
	this->m_eDirection = eDIRECTION_DIAGONAL;
	this->m_fCurrentAngleZ = this->m_fMaxAngleZ;
	UpdateRotation();
}

void CEnemyBossSideLasersController::UpdateRotation()
{
	float fAngleY = this->m_pBossFrame->GetAngleY();

	if (this->m_pLaserLeft && this->m_pLaserLeft->IsActive())
	{
		this->m_pLaserLeft->SetRotateY(fAngleY);
		this->m_pLaserLeft->SetRotateZ(-this->m_fCurrentAngleZ);
	}

	if (this->m_pLaserRight && this->m_pLaserRight->IsActive())
	{
		this->m_pLaserRight->SetRotateY(fAngleY);
		this->m_pLaserRight->SetRotateZ(this->m_fCurrentAngleZ);
	}
}