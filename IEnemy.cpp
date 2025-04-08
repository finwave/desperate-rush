#include "LerpUtils.h"
#include "IEnemy.h"

IEnemy::IEnemy(void)
{
	this->m_pTheApp = NULL;

	this->m_pBullets.Clear();

	this->m_eMove = eMOVE_STAY;
	this->m_eMoveOld = eMOVE_STAY;
	this->m_eRotationX = eROTATION_X_NONE;
	this->m_eRotationZ = eROTATION_Z_NONE;
	this->m_eSoundHit = eSOUND_HIT_NORMAL;
	this->m_eMoveDamageLevel = eMOVE_DAMAGE_LEVEL_0;
	this->m_eReinforcementAction = eREINFORCEMENT_ACTION_NONE;

	this->m_bEnter = false;
	this->m_bFleeReady = false;
	this->m_bFleeMovement = false;
	this->m_bSpeedSlowDown = false;

	this->m_bBoss = false;
	this->m_bShootCount = true;

	this->m_iVolumeSoundEffect = 0;

	this->m_fScreenWidth = 0.0f;
	this->m_fScreenHeight = 0.0f;
	this->m_fScreenPixelWidth = 1024.0f;
	this->m_fScreenPixelHeight = 768.0f;

	this->m_fShipEnterMoveDuration = 0.0f;
	this->m_fShipEnterMoveTimer = 0.0f;
	this->m_fShipEnterStartPosY = 0.0f;
	this->m_fShipEnterEndPosY = 0.0f;
	this->m_fMovementBorderY = 0.0f;

	this->m_fSpeed = 0.0f;
	this->m_fSpeedDefault = 0.0f;
	this->m_fSpeedDivider = 1.0f;
	this->m_fSpeedChangeMultiplier = 0.0f;

	this->m_bSpeedChange = false;

	this->m_fEnemyWidth = 0.0f;
	this->m_fEnemyHeight = 0.0f;
	
	this->m_iHealth = 0;
	this->m_iHealthMax = 0;

	this->m_iScoreHit = 0;
	this->m_iScoreDestroyed = 0;

	this->m_bBonus = false;
	this->m_bAfterburn = false;
	this->m_bCannonDamage = true;

	this->m_bSoundStrikeAfterburn = false;

	this->m_bBlastShakeUp = false;
	this->m_bBlastShakeDown = false;
	this->m_bBlastShakeLeft = false;
	this->m_bBlastShakeRight = false;
	this->m_bBlastShakeUpLeft = false;
	this->m_bBlastShakeUpRight = false;
	this->m_bBlastShakeDownLeft = false;
	this->m_bBlastShakeDownRight = false;

	this->m_bTimedExplosion = false;

	this->m_bRotateYLeft = false;
	this->m_bRotateYRight = false;
	this->m_bRotateYStraight = false;
	this->m_bCheckStraighteningY = false;
	this->m_bIsStraightY = true;

	this->m_fTimedExplosionCounter = 0.0f;
	this->m_fTimedExplosionTimer = 0.0f;

	this->m_fMaxRotation = 0.0f;
	this->m_fRotationSpeed = 0.0f;

	this->m_fAngleX = 0.0f;
	this->m_fAngleY = 0.0f;
	this->m_fAngleZ = 0.0f;

	this->m_fDamageMoveCycleTime = 0.0f;
	this->m_fDamageMoveTime = 0.0f;
	this->m_fDamageMoveCycleCounter = 0.0f;

	this->m_fCannonDamageMoveCounter = 0.0f;
	this->m_fBlastDamageMoveCounter = 0.0f;

	this->m_iDamageMoves = 0;
	this->m_iPauseAfterburn = 0;
}

IEnemy::~IEnemy(void)
{
}

HRESULT IEnemy::Create(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						LPD3DXMESH mesh,
						std::vector<D3DMATERIAL9*> materials,
						std::vector<LPDIRECT3DTEXTURE9> textures,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect)
{
	// get default matrix
	this->m_mDefault = this->GetLocalMatrix();

	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}

	Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);

	return S_OK;
}

HRESULT IEnemy::Create(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						LPD3DXMESH mesh,
						std::vector<MESHDATA>& meshData,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect)
{
	// get default matrix
	this->m_mDefault = this->GetLocalMatrix();

	C3DObject::Create(mesh);

	this->m_arrMeshData = meshData;

	Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);

	return S_OK;
}

void IEnemy::Init(CTheApp* pTheApp,
					CGameSettings* pGameSettings,
					CSprite* pSpriteAfterburn,
					int iVolumeSoundEffect)
{
	this->m_pTheApp = pTheApp;
	this->m_pGameSettings = pGameSettings;

	this->m_fScreenWidth = pTheApp->GetScreenWidth();
	this->m_fScreenHeight = pTheApp->GetScreenHeight();

	this->m_pSpriteAfterburn = pSpriteAfterburn;
	this->m_iVolumeSoundEffect = iVolumeSoundEffect;

	this->m_fFleeSpeedMultiplier = this->m_fFleeSpeedIncrease;

	if (this->m_eType == eTYPE_BOSS_1_CANNON)
	{
		return;
	}

	switch(this->m_pTheApp->RandInt(1,2))
	{
	case 1:
		this->m_eMoveDamageSide = eMOVE_DAMAGE_SIDE_LEFT;
		break;

	case 2:
		this->m_eMoveDamageSide = eMOVE_DAMAGE_SIDE_RIGHT;
		break;
	}

	this->SetMovementBorders();
	this->InitFiringSound();

	switch(this->m_eBehaviour)
	{
	case eBEHAVIOUR_LAUNCH:

		this->m_bEnter = true;
		this->m_bAfterburn = true;
		this->m_bSetShipEnterDuration = true;

		this->m_fShootCounter = this->m_fShootTime;

		this->GenerateRandomEnterSpeed();
		this->GenerateRandomFleeTime();
		this->GenerateRandomMoveTime();

		this->SetMoveState();

		break;

	case eBEHAVIOUR_STRIKE:
			
		this->m_bAfterburn = true;
		this->m_bSoundStrikeAfterburn = true;
		this->m_eMove = eMOVE_DOWN;
			
		break;

	case eBEHAVIOUR_BOSS:

		this->m_bEnter = true;
		break;
	}

	// set speed change multiplier
	switch(this->m_eType)
	{
	case eTYPE_DRONE:
		this->m_fSpeedChangeMultiplier = 1.0045f;
		break;

	case eTYPE_SNIPER:
		this->m_fSpeedChangeMultiplier = 1.0045f;
		break;

	case eTYPE_ROLLER:
		this->m_fSpeedChangeMultiplier = 1.0045f;
		break;

	case eTYPE_GUARD:
		this->m_fSpeedChangeMultiplier = 1.0045f;
		break;
	}
}

void IEnemy::Release()
{
	this->m_pBullets.Clear();
	this->m_pCollisionEnemies.Clear();
	this->m_pTheApp = NULL;

	C3DObject::Release();
}

void IEnemy::Update(float fFrametime, float fPlayerVelocity)
{
	if (this->m_eType == eTYPE_BOSS_1_CANNON)
	{
		if (!this->m_bEnter)
		{
			// update shoot counter
			if (this->m_bShootCount)
			{
				this->m_fShootCounter += fFrametime;
			}
		}
	}
	else
	{
		// enter movement
		if (this->m_bEnter)
		{
			this->MoveEnter(fFrametime, fPlayerVelocity);

			if (this->m_eType == eTYPE_ROLLER)
			{
				/* ROTATION */
				this->CheckMovement();
				this->Rotate(fFrametime);
			}
		}
		else
		{
			// rotation
			if ((this->m_eType != eTYPE_BOSS_1_CORE) &&
				(this->m_eType != eTYPE_BOSS_1_LASER_LEFT) &&
				(this->m_eType != eTYPE_BOSS_1_LASER_RIGHT) &&
				(this->m_eType != eTYPE_BOSS_1_SCATTER_LEFT) &&
				(this->m_eType != eTYPE_BOSS_1_SCATTER_RIGHT))
			{
				/* ROTATION */
				this->CheckMovement();
				this->Rotate(fFrametime);
			}

			// damage movement
			this->DamageMovement(fFrametime);

			// timed explosion
			if (this->m_bTimedExplosion)
			{
				if ((this->m_eBehaviour == eBEHAVIOUR_LAUNCH) ||
					(this->m_eBehaviour == eBEHAVIOUR_OBSTACLE))
				{
					if (this->m_bFleeMovement)
					{
						this->MoveFlee(fFrametime, fPlayerVelocity);
					}
					else
					{
						this->Move(fFrametime, fPlayerVelocity);
					}
				}
				else if (this->m_eBehaviour == eBEHAVIOUR_STRIKE)
				{
					this->Move(fFrametime, fPlayerVelocity);
				}

				if (this->m_fTimedExplosionCounter >= this->m_fTimedExplosionTimer)
				{
					this->m_iHealth = 0;
				}
				else
				{
					this->m_fTimedExplosionCounter += fFrametime;
				}
			}
			// enemy is fleeing
			else if (this->m_bFleeMovement)
			{
				this->MoveFlee(fFrametime, fPlayerVelocity);
			}
			else
			{
				// sent fleet ship
				if ((this->m_eBehaviour == eBEHAVIOUR_REINFORCEMENT) &&
					(this->m_eReinforcementAction == eREINFORCEMENT_ACTION_SENT))
				{
					if (this->m_bSpeedChange)
					{
						this->MoveReinforcementSpeedChange(fFrametime, fPlayerVelocity);
					}
					else
					{
						this->MoveReinforcement(fFrametime, fPlayerVelocity);
					}

					if (this->m_fMoveTime <= 0.0f)
					{
						if ((this->m_eMove == eMOVE_STAY) &&
							this->m_bSpeedSlowDown)
						{
							this->m_bSpeedSlowDown = false;
						}
					}
				}
				// launch/strike enemies
				else
				{
					this->Move(fFrametime, fPlayerVelocity);
				}

				// update move timer
				this->m_fMoveTime -= fFrametime;

				// update shoot counter
				if (this->m_eBehaviour == eBEHAVIOUR_LAUNCH ||
					this->m_eBehaviour == eBEHAVIOUR_OBSTACLE ||
					this->m_eBehaviour == eBEHAVIOUR_BOSS)
				{
					if (this->m_bShootCount)
					{
						this->m_fShootCounter += fFrametime;
					}
				}
				// update flee counter
				if (this->m_eBehaviour == eBEHAVIOUR_LAUNCH)
				{
					this->m_fFleeCounter += fFrametime;

					if (this->m_fFleeCounter >= this->m_fFleeTime)
					{
						this->m_bFleeReady = true;
					}
				}
			}
		}
	}

	C3DObject::Update(fFrametime);
}

void IEnemy::UpdateShake(float fFrametime)
{
	C3DObject::Update(fFrametime);
}

void IEnemy::UpdateBossCannonShake(float fFrametime)
{
	if(this->m_fCannonDamageMoveCounter >= this->m_fDamageMoveTime)
	{
		// current position
		D3DXVECTOR3 pos = this->GetPosition();

		// enemy's movement speed
		float fFrameSpeed = fFrametime * this->m_fSpeed;

		// random shake direction
		if(	!this->m_bBlastShakeLeft && !this->m_bBlastShakeRight )
		{
			switch(this->m_pTheApp->RandInt(1,2))
			{
			// shake right
			case 1:
				pos.x += fFrameSpeed * 1.50f;
				this->m_bBlastShakeRight = true;
				break;

			// shake left
			case 2:
				pos.x -= fFrameSpeed * 1.50f;
				this->m_bBlastShakeLeft = true;
				break;
			}
		}
		// shakes to other direction
		else
		{
			if(this->m_bBlastShakeLeft)
			{
				pos.x += fFrameSpeed * 1.50f;
				this->m_bBlastShakeLeft = false;
			}
			else if(this->m_bBlastShakeRight)
			{
				pos.x -= fFrameSpeed * 1.50f;
				this->m_bBlastShakeRight = false;
			}
		}

		this->SetPosition(pos);

		// start counting for the next damage move
		this->m_fCannonDamageMoveCounter = 0.0f;
	}
	else
	{
		this->m_fCannonDamageMoveCounter += fFrametime;
	}
}

void IEnemy::UpdateBossBlastShake(float fFrametime)
{
	if(this->m_fBlastDamageMoveCounter >= this->m_fDamageMoveTime)
	{
		// current position
		D3DXVECTOR3 pos = this->GetPosition();

		// enemy's movement speed
		float fFrameSpeed = fFrametime * this->m_fSpeed;

		// random shake direction
		if(	!this->m_bBlastShakeLeft && !this->m_bBlastShakeRight )
		{
			switch(this->m_pTheApp->RandInt(1,2))
			{
			// shake right
			case 1:
				pos.x += fFrameSpeed * 1.20f;
				this->m_bBlastShakeRight = true;
				break;

			// shake left
			case 2:
				pos.x -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeLeft = true;
				break;
			}
		}
		// shakes to other direction
		else
		{
			if(this->m_bBlastShakeLeft)
			{
				pos.x += fFrameSpeed * 1.20f;
				this->m_bBlastShakeLeft = false;
			}
			else if(this->m_bBlastShakeRight)
			{
				pos.x -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeRight = false;
			}
		}

		this->SetPosition(pos);

		// start counting for the next damage move
		this->m_fBlastDamageMoveCounter = 0.0f;
	}
	else
	{
		this->m_fBlastDamageMoveCounter += fFrametime;
	}
}

void IEnemy::UpdateEnemyCannonShake(float fFrametime)
{
	if(this->m_fCannonDamageMoveCounter >= this->m_fDamageMoveTime)
	{
		// current position
		D3DXVECTOR3 pos = this->GetPosition();

		// enemy's movement speed
		float fFrameSpeed = fFrametime * this->m_fSpeed;

		// random shake direction
		if(	!this->m_bBlastShakeUp && !this->m_bBlastShakeDown && 
			!this->m_bBlastShakeLeft && !this->m_bBlastShakeRight && 
			!this->m_bBlastShakeUpLeft && !this->m_bBlastShakeUpRight && 
			!this->m_bBlastShakeDownLeft && !this->m_bBlastShakeDownRight)
		{
			switch(this->m_pTheApp->RandInt(1,8))
			{
			// shake up-left
			case 1:
				pos.x -= fFrameSpeed * 2.0f;
				pos.y += fFrameSpeed * 2.0f;
				this->m_bBlastShakeUpLeft = true;
				break;

			// shake right
			case 2:
				pos.x += fFrameSpeed * 2.0f;
				this->m_bBlastShakeRight = true;
				break;

			// shake down-right
			case 3:
				pos.x += fFrameSpeed * 2.0f;
				pos.y -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeDownRight = true;
				break;

			// shake up
			case 4:
				pos.y += fFrameSpeed * 2.0f;
				this->m_bBlastShakeUp = true;
				break;

			// shake left
			case 5:
				pos.x -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeLeft = true;
				break;

			// shake up-right
			case 6:
				pos.x += fFrameSpeed * 2.0f;
				pos.y += fFrameSpeed * 2.0f;
				this->m_bBlastShakeUpRight = true;
				break;

			// shake down
			case 7:
				pos.y -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeDown = true;
				break;

			// shake down-left
			case 8:
				pos.x -= fFrameSpeed * 2.0f;
				pos.y -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeDownLeft = true;
				break;
			}
		}
		// shakes to other direction
		else
		{
			if(this->m_bBlastShakeUp)
			{
				pos.y -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeUp = false;
			}
			else if(this->m_bBlastShakeDown)
			{
				pos.y += fFrameSpeed * 2.0f;
				this->m_bBlastShakeDown = false;
			}
			else if(this->m_bBlastShakeLeft)
			{
				pos.x += fFrameSpeed * 2.0f;
				this->m_bBlastShakeLeft = false;
			}
			else if(this->m_bBlastShakeRight)
			{
				pos.x -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeRight = false;
			}
			else if(this->m_bBlastShakeUpLeft)
			{
				pos.x += fFrameSpeed * 2.0f;
				pos.y -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeUpLeft = false;
			}
			else if(this->m_bBlastShakeUpRight)
			{
				pos.x -= fFrameSpeed * 2.0f;
				pos.y -= fFrameSpeed * 2.0f;
				this->m_bBlastShakeUpRight = false;
			}
			else if(this->m_bBlastShakeDownLeft)
			{
				pos.x += fFrameSpeed * 2.0f;
				pos.y += fFrameSpeed * 2.0f;
				this->m_bBlastShakeDownLeft = false;
			}
			else if(this->m_bBlastShakeDownRight)
			{
				pos.x -= fFrameSpeed * 2.0f;
				pos.y += fFrameSpeed * 2.0f;
				this->m_bBlastShakeDownRight = false;
			}
		}

		this->SetPosition(pos);

		// start counting for the next damage move
		this->m_fCannonDamageMoveCounter = 0.0f;
	}
	else
	{
		this->m_fCannonDamageMoveCounter += fFrametime;
	}
}

void IEnemy::UpdateEnemyBlastShake(float fFrametime)
{
	if(this->m_fBlastDamageMoveCounter >= this->m_fDamageMoveTime)
	{
		// current position
		D3DXVECTOR3 pos = this->GetPosition();

		// enemy's movement speed
		float fFrameSpeed = fFrametime * this->m_fSpeed;

		// random shake direction
		if(	!this->m_bBlastShakeUp && !this->m_bBlastShakeDown && 
			!this->m_bBlastShakeLeft && !this->m_bBlastShakeRight && 
			!this->m_bBlastShakeUpLeft && !this->m_bBlastShakeUpRight && 
			!this->m_bBlastShakeDownLeft && !this->m_bBlastShakeDownRight)
		{
			switch(this->m_pTheApp->RandInt(1,8))
			{
			// shake up-left
			case 1:
				pos.x -= fFrameSpeed * 1.20f;
				pos.y += fFrameSpeed * 1.20f;
				this->m_bBlastShakeUpLeft = true;
				break;

			// shake right
			case 2:
				pos.x += fFrameSpeed * 1.20f;
				this->m_bBlastShakeRight = true;
				break;

			// shake down-right
			case 3:
				pos.x += fFrameSpeed * 1.20f;
				pos.y -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeDownRight = true;
				break;

			// shake up
			case 4:
				pos.y += fFrameSpeed * 1.20f;
				this->m_bBlastShakeUp = true;
				break;

			// shake left
			case 5:
				pos.x -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeLeft = true;
				break;

			// shake up-right
			case 6:
				pos.x += fFrameSpeed * 1.20f;
				pos.y += fFrameSpeed * 1.20f;
				this->m_bBlastShakeUpRight = true;
				break;

			// shake down
			case 7:
				pos.y -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeDown = true;
				break;

			// shake down-left
			case 8:
				pos.x -= fFrameSpeed * 1.20f;
				pos.y -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeDownLeft = true;
				break;
			}
		}
		// shakes to other direction
		else
		{
			if(this->m_bBlastShakeUp)
			{
				pos.y -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeUp = false;
			}
			else if(this->m_bBlastShakeDown)
			{
				pos.y += fFrameSpeed * 1.20f;
				this->m_bBlastShakeDown = false;
			}
			else if(this->m_bBlastShakeLeft)
			{
				pos.x += fFrameSpeed * 1.20f;
				this->m_bBlastShakeLeft = false;
			}
			else if(this->m_bBlastShakeRight)
			{
				pos.x -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeRight = false;
			}
			else if(this->m_bBlastShakeUpLeft)
			{
				pos.x += fFrameSpeed * 1.20f;
				pos.y -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeUpLeft = false;
			}
			else if(this->m_bBlastShakeUpRight)
			{
				pos.x -= fFrameSpeed * 1.20f;
				pos.y -= fFrameSpeed * 1.20f;
				this->m_bBlastShakeUpRight = false;
			}
			else if(this->m_bBlastShakeDownLeft)
			{
				pos.x += fFrameSpeed * 1.20f;
				pos.y += fFrameSpeed * 1.20f;
				this->m_bBlastShakeDownLeft = false;
			}
			else if(this->m_bBlastShakeDownRight)
			{
				pos.x -= fFrameSpeed * 1.20f;
				pos.y += fFrameSpeed * 1.20f;
				this->m_bBlastShakeDownRight = false;
			}
		}

		this->SetPosition(pos);

		// start counting for the next damage move
		this->m_fBlastDamageMoveCounter = 0.0f;
	}
	else
	{
		this->m_fBlastDamageMoveCounter += fFrametime;
	}
}

void IEnemy::RenderEnemyAfterburn(bool bFreeze, bool bPauseTimer)
{
	if(bPauseTimer)
	{
		if(this->m_iPauseAfterburn == 0)
		{
			this->m_iPauseAfterburn = 3;

			const float fPixelMultiplier = 2.5f;

			// enemy's current position
			D3DXVECTOR3 pos = this->GetPosition();

			float fMoveX = pos.x * fPixelMultiplier;
			float fMoveY = pos.y * fPixelMultiplier;

			fMoveY = fMoveY * -1.0f;

			int posX = ( (this->m_fScreenPixelWidth / 2) - 38.0f) + fMoveX;
			int posY = ( (this->m_fScreenPixelHeight / 2) - 38.0f) + fMoveY;

			switch(this->m_eType)
			{
			case eTYPE_DRONE:

				posX += 0;
				posY -= 49;

				(this->m_pSpriteAfterburn + 0)->Draw(posX, posY);

				break;

			case eTYPE_SNIPER:

				posX += 6;
				posY -= 62;

				(this->m_pSpriteAfterburn + 1)->Draw(posX, posY);

				break;

			case eTYPE_ROLLER:

				posX += 0;
				posY += 55;

				(this->m_pSpriteAfterburn + 2)->Draw(posX, posY);

				break;

			case eTYPE_GUARD:

				posX += 0;
				posY += 55;

				(this->m_pSpriteAfterburn + 3)->Draw(posX, posY);

				break;
			}
		}
		else
		{
			if(!bFreeze)
			{
				this->m_iPauseAfterburn--;
			}
		}
	}
	else
	{
		const float fPixelMultiplier = 2.5f;

		// enemy's current position
		D3DXVECTOR3 pos = this->GetPosition();

		float fMoveX = pos.x * fPixelMultiplier;
		float fMoveY = pos.y * fPixelMultiplier;

		fMoveY = fMoveY * -1.0f;

		int posX = ( (this->m_fScreenPixelWidth / 2) - 38.0f) + fMoveX;
		int posY = ( (this->m_fScreenPixelHeight / 2) - 38.0f) + fMoveY;

		switch(this->m_eType)
		{
		case eTYPE_DRONE:

			posX += 0;
			posY -= 49;

			(this->m_pSpriteAfterburn + 0)->Draw(posX, posY);

			break;

		case eTYPE_SNIPER:

			posX += 6;
			posY -= 62;

			(this->m_pSpriteAfterburn + 1)->Draw(posX, posY);

			break;

		case eTYPE_ROLLER:

			posX += 0;
			posY += 55;

			(this->m_pSpriteAfterburn + 2)->Draw(posX, posY);

			break;

		case eTYPE_GUARD:

			posX += 0;
			posY += 55;

			(this->m_pSpriteAfterburn + 3)->Draw(posX, posY);

			break;
		}
	}
}

HRESULT IEnemy::InitWeapons(CTheApp* pTheApp,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							float fBulletWidth,
							float fBulletHeight,
							float fBulletSpeed,
							int iBulletDamage)
{
	return S_OK;
}

HRESULT IEnemy::InitWeapons(CTheApp* pTheApp,
							LPD3DXMESH mesh,
							std::vector<MESHDATA>& meshData,
							float fBulletWidth,
							float fBulletHeight,
							float fBulletSpeed,
							int iBulletDamage)
{
	return S_OK;
}

bool IEnemy::Destroyed(int iDamage)
{
	if(!this->m_bTimedExplosion)
	{
		this->m_iHealth -= iDamage;

		if( this->m_iHealth <= 0 )
		{
			this->m_iHealth = 0;

			// Deactivate other enemies except "boss frame" enemy type (boss chain explosion).
			if(this->m_eType != eTYPE_BOSS_1_FRAME)
			{
				this->m_bActive = false;
			}
			return true;
		}
	}

	return false;
}

void IEnemy::InitReinforcementSend()
{
	this->m_bEnter = false;
	this->m_bAfterburn = false;
	this->m_bSpeedChange = false;
	this->m_bSpeedSlowDown = false;

	this->m_fSpeed = this->m_fSpeedDefault;
	this->m_iHealth = this->m_iHealthMax;

	this->m_eMove = eMOVE_STAY;
	this->m_eMoveOld = eMOVE_STAY;
	this->m_eMoveDamageLevel = eMOVE_DAMAGE_LEVEL_0;

	this->m_eReinforcementAction = eREINFORCEMENT_ACTION_SENT;

	this->StraightenEnemy();
	this->ChangeRotationZ();

	D3DXVECTOR3 pos = this->GetPosition();

	/* set enemy position, scale and speed modifier */

	float fBaseSpeedDivider = 6.5f;

	switch(this->m_eDepth)
	{
	case eENEMY_DEPTH_2:

		this->m_fSpeedDivider = fBaseSpeedDivider;
		this->SetScale(2);

		break;

	case eENEMY_DEPTH_3:

		this->m_fSpeedDivider = fBaseSpeedDivider * 2.0f;
		this->SetScale(3);

		break;

	case eENEMY_DEPTH_4:

		this->m_fSpeedDivider = fBaseSpeedDivider * (2 * 2.0f);
		this->SetScale(4);

		break;

	case eENEMY_DEPTH_5:

		this->m_fSpeedDivider = fBaseSpeedDivider * (3 * 2.0f);
		this->SetScale(5);

		break;
	}

	switch(this->m_eType)
	{
		case eTYPE_DRONE:
			pos.y = this->m_fScreenHeight + 7.0f;
			break;
		case eTYPE_SNIPER:
			pos.y = this->m_fScreenHeight + 10.0f;
			break;
		case eTYPE_ROLLER:
			pos.y = this->m_fScreenHeight + 15.0f;
			break;
		case eTYPE_GUARD:
			pos.y = this->m_fScreenHeight + 20.0f;
			break;
	}

	this->SetPosition(pos);
}

void IEnemy::InitObstacleEnemy(float fSpeed)
{
	this->SetBehaviour(IEnemy::eBEHAVIOUR_OBSTACLE);

	this->m_eMove = eMOVE_DOWN;
	this->GenerateRandomMoveTime();

	// disable enter movement
	this->SetEnter(false);
	// disable afterburn
	this->SetAfterburn(false);
	// disable afterburn sound
	this->SetAfterburnSoundStrike(false);
	// set enemy's speed to same as obstacle speed
	this->m_fSpeed = fSpeed;
}

void IEnemy::InitScores()
{
	switch(m_eType)
	{
	case eTYPE_DRONE:
		this->m_iScoreHit = 1;
		this->m_iScoreDestroyed = 50;
		break;
	case eTYPE_SNIPER:
		this->m_iScoreHit = 2;
		this->m_iScoreDestroyed = 100;
		break;
	case eTYPE_ROLLER:
		this->m_iScoreHit = 3;
		this->m_iScoreDestroyed = 300;
		break;
	case eTYPE_GUARD:
		this->m_iScoreHit = 4;
		this->m_iScoreDestroyed = 500;
		break;
	case eTYPE_BOSS_1_FRAME:
		this->m_iScoreHit = 5;
		this->m_iScoreDestroyed = 5000;
		break;
	case eTYPE_BOSS_1_SCATTER_LEFT:
		this->m_iScoreHit = 2;
		this->m_iScoreDestroyed = 1000;
		break;
	case eTYPE_BOSS_1_SCATTER_RIGHT:
		this->m_iScoreHit = 2;
		this->m_iScoreDestroyed = 1000;
		break;
	}
}

void IEnemy::InitRotationValues()
{
	switch(m_eType)
	{
	case eTYPE_DRONE:
		this->m_fMaxRotation = 0.4f;
		this->m_fRotationSpeed = 1.7f;
		break;
	case eTYPE_SNIPER:
		this->m_fMaxRotation = 0.5f;
		this->m_fRotationSpeed = 1.5f;
		break;
	case eTYPE_ROLLER:
		this->m_fMaxRotation = 0.35f;
		this->m_fRotationSpeed = 0.9f;
		break;
	case eTYPE_GUARD:
		this->m_fMaxRotation = 0.20f;
		this->m_fRotationSpeed = 0.7f;
		break;
	case eTYPE_BOSS_1_FRAME:
		this->m_fMaxRotation = 0.27f;
		this->m_fRotationSpeed = 0.07f;
		break;
	}
}

void IEnemy::ChangeFiringSound()
{
	if( (this->m_eType == eTYPE_BOSS_1_SCATTER_LEFT) || 
		(this->m_eType == eTYPE_BOSS_1_SCATTER_RIGHT) || 
		(this->m_eType == eTYPE_BOSS_1_LASER_LEFT) || 
		(this->m_eType == eTYPE_BOSS_1_LASER_RIGHT))
	{
		switch(this->m_eSoundFiring)
		{
		case eSOUND_FIRING_NORMAL_1:
			this->m_eSoundFiring = eSOUND_FIRING_QUIET_1;
			break;
		case eSOUND_FIRING_QUIET_1:
			this->m_eSoundFiring = eSOUND_FIRING_NORMAL_2;
			break;
		case eSOUND_FIRING_NORMAL_2:
			this->m_eSoundFiring = eSOUND_FIRING_QUIET_2;
			break;
		case eSOUND_FIRING_QUIET_2:
			this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
			break;
		}
	}
	else
	{
		switch(this->m_eSoundFiring)
		{
		case eSOUND_FIRING_NORMAL_1:
			this->m_eSoundFiring = eSOUND_FIRING_QUIET_1;
			break;
		case eSOUND_FIRING_QUIET_1:
			this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
			break;
		}
	}
}

void IEnemy::ChangeHitSound()
{
	switch(this->m_eSoundHit)
	{
	case eSOUND_HIT_NORMAL:
		this->m_eSoundHit = eSOUND_HIT_QUIET;
		break;
	case eSOUND_HIT_QUIET:
		this->m_eSoundHit = eSOUND_HIT_NORMAL;
		break;
	}
}

void IEnemy::SetBlastShake()
{
	this->m_fBlastDamageMoveCounter = 0.0f;
	this->m_fDamageMoveTime = 0.01f;
}

void IEnemy::SetTimedExplosion()
{
	if(	this->m_bFleeMovement || (this->m_eBehaviour == eBEHAVIOUR_STRIKE))
	{
		this->m_bAfterburn = false;
	}

	this->m_iHealth = 1;

	this->m_bTimedExplosion = true;

	this->m_fTimedExplosionCounter = 0.0f;
	this->m_fTimedExplosionTimer = this->m_pTheApp->RandFloat(0.1f, 1.0f);
}

void IEnemy::ResetTimedExplosion()
{
	this->m_fTimedExplosionCounter = 0.0f;
	this->m_fTimedExplosionTimer = 0.0f;
	this->m_bTimedExplosion = false;
}

void IEnemy::ResetFleeMovement()
{
	this->m_fFleeSpeedIncrease = 0.02f;
	this->m_bFleeReady = false;
	this->m_bFleeMovement = false;
	this->m_bFleeSound = true;
}

void IEnemy::GetRandomBonus()
{
}

void IEnemy::ClearBullets(bool bForced)
{
	// clear enemy bullets
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		CWeapon* pBullet = this->m_pBullets.GetCurrent();

		if(bForced)
		{
			this->m_pBullets.PopCurrent();
		}
		else
		{
			if( !pBullet->IsActive() )
			{
				this->m_pBullets.PopCurrent();
			}
			else
			{
				this->m_pBullets.SetNext();
			}
		}
	}
}

void IEnemy::RenderBullets(bool bFreeze, float fFrametime, float playerVelocity)
{
	// render enemy bullets
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			CWeapon* pBullet = this->m_pBullets.GetCurrent();

			if(!bFreeze)
			{
				pBullet->Update(fFrametime, playerVelocity);
			}

			this->m_pBullets.SetFirst();
			while( pBullet != this->m_pBullets.GetCurrent() )
			{
				this->m_pBullets.SetNext();
			}

			this->m_pBullets.GetCurrent()->Render(this->m_pTheApp->GetDevice());

			// draw bullet sprite
			switch( this->m_pBullets.GetCurrent()->GetBulletType() )
			{
			case CWeapon::eBULLET_TYPE_ENEMY_ROLLER:

				this->m_pBullets.GetCurrent()->DrawSpriteBulletRoller();
				break;

			case CWeapon::eBULLET_TYPE_BOSS_1_LASER:

				this->m_pBullets.GetCurrent()->DrawSpriteBulletBoss1Laser();
				break;

			case CWeapon::eBULLET_TYPE_BOSS_1_SCATTER:

				this->m_pBullets.GetCurrent()->DrawSpriteBulletBoss1Scatter();
				break;
			}
		}
		this->m_pBullets.SetNext();
	}
}

bool IEnemy::CollisionBulletVsPlayer(CPlayer* pPlayer)
{
	// Enemy bullets VS Player

	bool bCollision = false;
	bool bTotalDestruction;

	CWeapon* pBullet;
	D3DXVECTOR3* pPos;

	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			pBullet = this->m_pBullets.GetCurrent();
			pPos = pBullet->GetBulletPosition();

			// weapon kills instantly
			if( pBullet->GetDamageType() == CWeapon::TOTAL_DESTRUCTION )
			{
				bTotalDestruction = true;
			}
			else
			{
				bTotalDestruction = false;
			}

			// bounding box collision
			if( this->IsBoxCollision(	pPlayer->GetPosition(),
										pPlayer->GetWidth() / 2.0f,
										pPlayer->GetHeight() / 2.0f,
										pPos[0],
										pBullet->GetWidth(),
										pBullet->GetHeight()) )
			{
				float posOriginalZ = pPos[0].z;

				pPos[0].z = 0.0f;
				pBullet->SetPosition(pPos[0]);

				pPlayer->UpdateCollisionMesh(true);
				pBullet->UpdateCollisionMesh(true);

				// mesh to mesh collision
				if(pPlayer->IsMeshCollision(pBullet->GetCollisionMesh(), false))
				{
					pBullet->DisableBullet(0);

					if(bTotalDestruction)
					{
						pPlayer->SetHealth(0);
					}
					else
					{
						pPlayer->DecreaseHealth(pBullet->GetDamage());
					}

					if( pPlayer->IsAlive() )
					{
						bCollision = true;
					}
				}
				else
				{
					pPos[0].z = posOriginalZ;
					pBullet->SetPosition(pPos[0]);
				}
			}
		}
		this->m_pBullets.SetNext();
	}

	return bCollision;
}

void IEnemy::CollisionBulletVsBorder()
{
	CWeapon* pBullet;
	D3DXVECTOR3* pPos;

	// Enemy bullets VS Border
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		pBullet = this->m_pBullets.GetCurrent();
		pPos = pBullet->GetBulletPosition();

		// top border
		if(	(pPos[0].y > (this->m_fScreenHeight + 15.0f)) && 
			((pBullet->GetDirection() == CWeapon::eDIRECTION_UP) || 
			(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_LEFT) ||
			(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_UP_LEFT) || 
			(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_LEFT_LEFT) || 
			(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_RIGHT) ||
			(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_UP_RIGHT) || 
			(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_RIGHT_RIGHT)))
		{
			pBullet->SetActive(FALSE);
		}
		// bottom border
		else if( pPos[0].y < (-this->m_fScreenHeight - 15.0f) )
		{
			pBullet->SetActive(FALSE);
		}
		
		// left border
		else if( pPos[0].x < (-this->m_fScreenWidth - 15.0f) )
		{
			pBullet->SetActive(FALSE);
		}
		// right border
		else if( pPos[0].x > (this->m_fScreenWidth + 15.0f) )
		{
			pBullet->SetActive(FALSE);
		}

		this->m_pBullets.SetNext();
	}
}

void IEnemy::CollisionEnemyVsPlayer(CPlayer* pPlayer)
{
	// Enemy VS Player

	if(	!pPlayer->IsDestroyed() && 
		!pPlayer->IsUntouchable())
	{
		D3DXVECTOR3 posOriginal;
		D3DXVECTOR3 posTest;
		D3DXVECTOR3 posFrame;

		// bounding box collision
		if(this->IsBoxCollision(pPlayer->GetPosition(),
								pPlayer->GetWidth() / 2.0f,
								pPlayer->GetHeight() / 2.0f,
								this->GetPosition(),
								this->GetWidth(),
								this->GetHeight()))
		{
			bool bInverseMatrix;

			if(	(this->m_eType == eTYPE_BOSS_1_SCATTER_LEFT) || 
				(this->m_eType == eTYPE_BOSS_1_SCATTER_RIGHT) || 
				(this->m_eType == eTYPE_BOSS_1_LASER_LEFT) || 
				(this->m_eType == eTYPE_BOSS_1_LASER_RIGHT))
			{
				bInverseMatrix = true;
			}
			else
			{
				bInverseMatrix = false;
			}

			pPlayer->UpdateCollisionMesh(bInverseMatrix);
			this->UpdateCollisionMesh(bInverseMatrix);

			// mesh to mesh collision
			if(pPlayer->IsMeshCollision(this->GetCollisionMesh(), false))
			{
				pPlayer->SetHealth(0);
			}
		}
	}
}

void IEnemy::CollisionPlayerCannonVsBullets(CPlayer* player)
{
	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float widthB;

	float fBulletLeftSide;
	float fBulletRightSide;

	posA = player->GetPosition();

	// go through enemy bullets
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			posB = this->m_pBullets.GetCurrent()->GetPosition();
			widthB = this->m_pBullets.GetCurrent()->GetWidth();

			fBulletLeftSide = posB.x - (widthB / 2);
			fBulletRightSide = posB.x + (widthB / 2);

			if(( ((posA.x + 2.0f) > fBulletLeftSide ) && 
				  ((posA.x + 2.0f) < fBulletRightSide) ) || 
				( ((posA.x - 2.0f) > fBulletLeftSide ) && 
				  ((posA.x - 2.0f) < fBulletRightSide) ) || 
				( ((posA.x + 2.0f) == fBulletLeftSide) || 
				  ((posA.x + 2.0f) == fBulletRightSide) || 
				  ((posA.x - 2.0f) == fBulletLeftSide) || 
				  ((posA.x - 2.0f) == fBulletRightSide) ))
			{
				if( posA.y < posB.y )
				{
					this->m_pBullets.PopCurrent();
				}
			}
		}
		this->m_pBullets.SetNext();
	}
}

void IEnemy::MoveAvoidLaunch(CQueue<IEnemy*>* pActiveEnemies)
{
	bool bCollisionTop = false;
	bool bCollisionBottom = false;
	bool bCollisionLeft = false;
	bool bCollisionRight = false;

	D3DXVECTOR3 posEnemyOther;
	D3DXVECTOR3 posEnemyThis = this->GetPosition();

	/* check collision against movement borders */

	/*
	// top border
	if( (posEnemyThis.y + (this->m_fEnemyHeight / 2)) > 
		(this->m_fScreenHeight - 2.0f) )
	{
		bCollisionTop = true;
	}
	// bottom border
	else if( (posEnemyThis.y - (this->m_fEnemyHeight / 2)) < 
			 (this->m_fMovementBorderY + 2.0f) )
	{
		bCollisionBottom = true;
	}
	*/

	// left border
	if( (posEnemyThis.x - (this->m_fEnemyHeight / 2)) < 
		(-this->m_fScreenWidth + 2.0f) )
	{
		bCollisionLeft = true;
	}
	// right border
	else if( (posEnemyThis.x + (this->m_fEnemyHeight / 2)) > 
			 (this->m_fScreenWidth - 2.0f))
	{
		bCollisionRight = true;
	}

	/* check collisions with other active enemies */

	pActiveEnemies->SetFirst();
	while(pActiveEnemies->GetCurrent())
	{
		if(	!bCollisionTop || !bCollisionBottom || 
			!bCollisionLeft || !bCollisionRight)
		{
			IEnemy* pOther = pActiveEnemies->GetCurrent();

			if( this != pOther )
			{
				if ( this->IsBoxCollision(	this->GetPosition(),
											this->m_fEnemyWidth + 8.0f,
											this->m_fEnemyHeight + 8.0f,
											pOther->GetPosition(),
											pOther->GetWidth() + 8.0f,
											pOther->GetHeight() + 8.0f) )
				{
					posEnemyOther = pOther->GetPosition();

					if(!bCollisionTop)
					{
						if(posEnemyOther.y > posEnemyThis.y)
						{
							bCollisionTop = true;
						}
					}
					if(!bCollisionBottom)
					{
						if(posEnemyOther.y < posEnemyThis.y)
						{
							bCollisionBottom = true;
						}
					}
					if(!bCollisionLeft)
					{
						if(posEnemyOther.x < posEnemyThis.x)
						{
							bCollisionLeft = true;
						}
					}
					if(!bCollisionRight)
					{
						if(posEnemyOther.x > posEnemyThis.x)
						{
							bCollisionRight = true;
						}
					}
				}
			}
		}
		pActiveEnemies->SetNext();
	}

	if(	bCollisionTop || bCollisionBottom || 
		bCollisionLeft || bCollisionRight)
	{
		MoveAvoidEnemy(	bCollisionTop, bCollisionBottom, 
						bCollisionLeft, bCollisionRight);
	}
}

void IEnemy::MoveAvoidObstacle(	CQueue<IEnemy*>* pActiveEnemies,
								CQueue<CObstacle*>* pObstacles)
{
	bool bCollision = false;

	pActiveEnemies->SetFirst();
	while( pActiveEnemies->GetCurrent() )
	{
		IEnemy* pEnemy = pActiveEnemies->GetCurrent();

		if( pEnemy->IsActive() )
		{
			// compare address (different enemies)
			if( this != pEnemy )
			{
				if ( this->IsBoxCollision(	this->GetPosition(),
											this->m_fEnemyWidth + 8.0f,
											this->m_fEnemyHeight + 8.0f,
											pEnemy->GetPosition(),
											pEnemy->GetWidth() + 8.0f,
											pEnemy->GetHeight() + 8.0f) )
				{
					bCollision = true;
					pActiveEnemies->SetLast();
				}
			}
		}
		pActiveEnemies->SetNext();
	}
	if(!bCollision)
	{
		pObstacles->SetFirst();
		while( pObstacles->GetCurrent() )
		{
			if( pObstacles->GetCurrent()->IsActive() )
			{
				CObstacle* pObstacle = pObstacles->GetCurrent();

				if ( this->IsBoxCollision(	this->GetPosition(),
											this->m_fEnemyWidth + 8.0f,
											this->m_fEnemyHeight + 8.0f,
											pObstacle->GetPosition(),
											pObstacle->GetWidth() + 8.0f,
											pObstacle->GetHeight() + 8.0f) )
				{
					bCollision = true;
					pObstacles->SetLast();
				}
			}
			pObstacles->SetNext();
		}
	}

	if(bCollision)
	{
		this->GenerateRandomMoveTime();
		eMOVE eMove = this->GetMovement();

		if(eMove == eMOVE_DOWN_LEFT)
		{
			this->m_eMove = eMOVE_DOWN_RIGHT;
		}
		else if(eMove == eMOVE_DOWN_RIGHT)
		{
			this->m_eMove = eMOVE_DOWN_LEFT;
		}
	}
}

void IEnemy::MoveAvoidEnemy(bool bCollisionTop, bool bCollisionBottom, 
							bool bCollisionLeft, bool bCollisionRight)
{
	// nowhere to move, wait for a while
	if(	bCollisionTop && bCollisionBottom && 
		bCollisionLeft && bCollisionRight)
	{
		// fleet enemy
		if(	(this->m_eBehaviour == eBEHAVIOUR_REINFORCEMENT) && 
			(this->m_eReinforcementAction == eREINFORCEMENT_ACTION_SENT) )
		{
			this->m_bSpeedSlowDown = true;
		}
		else
		{
			this->m_eMove = eMOVE_STAY;
		}

		this->GenerateRandomMoveTime();
	}
	// enemy can move somewhere
	// randomly move to available direction
	else
	{
		int iDirections;
		int* iRandArray = NULL;

		eMOVE eMoveOld = this->GetMovement();

		switch(this->m_eType)
		{
		case eTYPE_DRONE:

			// movement directions
			iDirections = 8;
			iRandArray = new int[iDirections];

			for (int i = 0; i < iDirections; i++)
			{
				iRandArray[i] = i + 1;
			}

			 // shuffle elements by randomly exchanging each with one other
			for (int j = 0; j < iDirections; j++)
			{
				// random remaining position
				int r = j + ( rand() % (iDirections - j) );

				int temp = iRandArray[j];
				iRandArray[j] = iRandArray[r];
				iRandArray[r] = temp;
			}

			for(int k = 0; k < iDirections; k++)
			{
				switch( iRandArray[k] )
				{
				case 1:

					if(!bCollisionTop)
					{
						this->m_eMove = eMOVE_UP;
						k = iDirections;
					}

					break;

				case 2:

					if(!bCollisionTop && !bCollisionLeft)
					{
						this->m_eMove = eMOVE_UP_LEFT;
						k = iDirections;
					}

					break;

				case 3:

					if(!bCollisionRight)
					{
						this->m_eMove = eMOVE_RIGHT;
						k = iDirections;
					}

					break;

				case 4:

					if(!bCollisionBottom && !bCollisionLeft)
					{
						this->m_eMove = eMOVE_DOWN_LEFT;
						k = iDirections;
					}

					break;

				case 5:

					if(!bCollisionBottom)
					{
						this->m_eMove = eMOVE_DOWN;
						k = iDirections;
					}

					break;

				case 6:

					if(!bCollisionTop && !bCollisionRight)
					{
						this->m_eMove = eMOVE_UP_RIGHT;
						k = iDirections;
					}

					break;

				case 7:

					if(!bCollisionLeft)
					{
						this->m_eMove = eMOVE_LEFT;
						k = iDirections;
					}

					break;

				case 8:

					if(!bCollisionBottom && !bCollisionRight)
					{
						this->m_eMove = eMOVE_DOWN_RIGHT;
						k = iDirections;
					}

					break;
				}
			}

			// new movement direction is the same as the old one
			if(this->m_eMove == eMoveOld)
			{
				// up and down movement blocked
				if(bCollisionTop && bCollisionBottom)
				{
					// both left and right movement free
					if(!bCollisionLeft && !bCollisionRight)
					{
						// choose either one
						switch(this->m_pTheApp->RandInt(1,2))
						{
						case 1:
							this->m_eMove = eMOVE_RIGHT;
							break;

						case 2:
							this->m_eMove = eMOVE_LEFT;
							break;
						}
					}
					// only other one is possibly free
					else
					{
						if(!bCollisionRight)
						{
							this->m_eMove = eMOVE_RIGHT;
						}
						else if(!bCollisionLeft)
						{
							this->m_eMove = eMOVE_LEFT;
						}
					}
				}
				// left and right movement blocked
				else if(bCollisionLeft && bCollisionRight)
				{
					// both up and down movement free
					if(!bCollisionTop && !bCollisionBottom)
					{
						// choose either one
						switch(this->m_pTheApp->RandInt(1,2))
						{
						case 1:
							this->m_eMove = eMOVE_UP;
							break;

						case 2:
							this->m_eMove = eMOVE_DOWN;
							break;
						}
					}
					// only other one is possibly free
					else
					{
						if(!bCollisionTop)
						{
							this->m_eMove = eMOVE_UP;
						}
						else if(!bCollisionBottom)
						{
							this->m_eMove = eMOVE_DOWN;
						}
					}
				}
				// no available movement direction
				else
				{
					this->m_eMove = eMOVE_STAY;
				}
			}

			break;

		case eTYPE_SNIPER:

			// movement directions
			iDirections = 8;
			iRandArray = new int[iDirections];

			for (int i = 0; i < iDirections; i++)
			{
				iRandArray[i] = i + 1;
			}

			 // shuffle elements by randomly exchanging each with one other
			for (int j = 0; j < iDirections; j++)
			{
				// random remaining position
				int r = j + ( rand() % (iDirections - j) );

				int temp = iRandArray[j];
				iRandArray[j] = iRandArray[r];
				iRandArray[r] = temp;
			}

			for(int k = 0; k < iDirections; k++)
			{
				switch( iRandArray[k] )
				{
				case 1:

					if(!bCollisionTop)
					{
						this->m_eMove = eMOVE_UP;
						k = iDirections;
					}

					break;

				case 2:

					if(!bCollisionTop && !bCollisionLeft)
					{
						this->m_eMove = eMOVE_UP_LEFT;
						k = iDirections;
					}

					break;

				case 3:

					if(!bCollisionRight)
					{
						this->m_eMove = eMOVE_RIGHT;
						k = iDirections;
					}

					break;

				case 4:

					if(!bCollisionBottom && !bCollisionLeft)
					{
						this->m_eMove = eMOVE_DOWN_LEFT;
						k = iDirections;
					}

					break;

				case 5:

					if(!bCollisionBottom)
					{
						this->m_eMove = eMOVE_DOWN;
						k = iDirections;
					}

					break;

				case 6:

					if(!bCollisionTop && !bCollisionRight)
					{
						this->m_eMove = eMOVE_UP_RIGHT;
						k = iDirections;
					}

					break;

				case 7:

					if(!bCollisionLeft)
					{
						this->m_eMove = eMOVE_LEFT;
						k = iDirections;
					}

					break;

				case 8:

					if(!bCollisionBottom && !bCollisionRight)
					{
						this->m_eMove = eMOVE_DOWN_RIGHT;
						k = iDirections;
					}

					break;
				}
			}

			// new movement direction is the same as the old one
			if(this->m_eMove == eMoveOld)
			{
				// up and down movement blocked
				if(bCollisionTop && bCollisionBottom)
				{
					// both left and right movement free
					if(!bCollisionLeft && !bCollisionRight)
					{
						// choose either one
						switch(this->m_pTheApp->RandInt(1,2))
						{
						case 1:
							this->m_eMove = eMOVE_RIGHT;
							break;

						case 2:
							this->m_eMove = eMOVE_LEFT;
							break;
						}
					}
					// only other one is possibly free
					else
					{
						if(!bCollisionRight)
						{
							this->m_eMove = eMOVE_RIGHT;
						}
						else if(!bCollisionLeft)
						{
							this->m_eMove = eMOVE_LEFT;
						}
					}
				}
				// left and right movement blocked
				else if(bCollisionLeft && bCollisionRight)
				{
					// both up and down movement free
					if(!bCollisionTop && !bCollisionBottom)
					{
						// choose either one
						switch(this->m_pTheApp->RandInt(1,2))
						{
						case 1:
							this->m_eMove = eMOVE_UP;
							break;

						case 2:
							this->m_eMove = eMOVE_DOWN;
							break;
						}
					}
					// only other one is possibly free
					else
					{
						if(!bCollisionTop)
						{
							this->m_eMove = eMOVE_UP;
						}
						else if(!bCollisionBottom)
						{
							this->m_eMove = eMOVE_DOWN;
						}
					}
				}
				// no available movement direction
				else
				{
					this->m_eMove = eMOVE_STAY;
				}
			}

			break;

		case eTYPE_ROLLER:

			// movement directions
			iDirections = 4;
			iRandArray = new int[iDirections];

			for (int i = 0; i < iDirections; i++)
			{
				iRandArray[i] = i + 1;
			}

			 // shuffle elements by randomly exchanging each with one other
			for (int j = 0; j < iDirections; j++)
			{
				// random remaining position
				int r = j + ( rand() % (iDirections - j) );

				int temp = iRandArray[j];
				iRandArray[j] = iRandArray[r];
				iRandArray[r] = temp;
			}

			for(int k = 0; k < iDirections; k++)
			{
				switch( iRandArray[k] )
				{
				case 1:

					if(!bCollisionTop)
					{
						this->m_eMove = eMOVE_UP;
						k = iDirections;
					}

					break;

				case 2:

					if(!bCollisionRight)
					{
						this->m_eMove = eMOVE_RIGHT;
						k = iDirections;
					}

					break;

				case 3:

					if(!bCollisionBottom)
					{
						this->m_eMove = eMOVE_DOWN;
						k = iDirections;
					}

					break;

				case 4:

					if(!bCollisionLeft)
					{
						this->m_eMove = eMOVE_LEFT;
						k = iDirections;
					}

					break;
				}
			}

			// new movement direction is the same as the old one
			if(this->m_eMove == eMoveOld)
			{
				// up and down movement blocked
				if(bCollisionTop && bCollisionBottom)
				{
					// both left and right movement free
					if(!bCollisionLeft && !bCollisionRight)
					{
						// choose either one
						switch(this->m_pTheApp->RandInt(1,2))
						{
						case 1:
							this->m_eMove = eMOVE_RIGHT;
							break;

						case 2:
							this->m_eMove = eMOVE_LEFT;
							break;
						}
					}
					// only other one is possibly free
					else
					{
						if(!bCollisionRight)
						{
							this->m_eMove = eMOVE_RIGHT;
						}
						else if(!bCollisionLeft)
						{
							this->m_eMove = eMOVE_LEFT;
						}
					}
				}
				// left and right movement blocked
				else if(bCollisionLeft && bCollisionRight)
				{
					// both up and down movement free
					if(!bCollisionTop && !bCollisionBottom)
					{
						// choose either one
						switch(this->m_pTheApp->RandInt(1,2))
						{
						case 1:
							this->m_eMove = eMOVE_UP;
							break;

						case 2:
							this->m_eMove = eMOVE_DOWN;
							break;
						}
					}
					// only other one is possibly free
					else
					{
						if(!bCollisionTop)
						{
							this->m_eMove = eMOVE_UP;
						}
						else if(!bCollisionBottom)
						{
							this->m_eMove = eMOVE_DOWN;
						}
					}
				}
				// no available movement direction
				else
				{
					this->m_eMove = eMOVE_STAY;
				}
			}

			break;
		}

		if(iRandArray)
		{
			delete [] iRandArray;
			iRandArray = NULL;
		}

		this->GenerateRandomMoveTime();
	}
}

bool IEnemy::IsBoxCollision(const D3DXVECTOR3& pos1, float fWidth1, float fHeight1, const D3DXVECTOR3& pos2, float fWidth2, float fHeight2)
{
	// 2 vectors indicating positions
	// of objects A and B

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	// width and height of
	// objects A and B

	float fWidthA;
	float fHeightA;

	float fWidthB;
	float fHeightB;

	bool bSameX = false;

	// object 1 and 2 are on the same X-coordinate 
	if( pos1.x == pos2.x )
	{
		bSameX = true;
	}

	// we set object A to be the one on the left side of object B
	// so object A is always the one more on the left side

	// object A is parameter object 1
	else if( pos1.x < pos2.x )
	{
		posA = pos1;
		fWidthA = fWidth1;
		fHeightA = fHeight1;

		posB = pos2;		
		fWidthB = fWidth2;
		fHeightB = fHeight2;
	}
	// object A is parameter object 2
	else if( pos2.x < pos1.x )
	{
		posA = pos2;
		fWidthA = fWidth2;
		fHeightA = fHeight2;

		posB = pos1;
		fWidthB = fWidth1;
		fHeightB = fHeight1;
	}

	// object 1 and 2 are on the same X-coordinate 
	if(bSameX)
	{
		// object 1 is on top of object 2
		if( pos1.y > pos2.y )
		{
			// if the bottom side of object 1
			// penetrates the top side of object 2
			// then we have definite collision
			if( (pos1.y - (fHeight1 / 2)) < (pos2.y + (fHeight2 / 2)) )
			{
				return true;
			}
		}
		// object 1 is below object 2
		else if( pos1.y < pos2.y )
		{
			// if the top side of object 1
			// penetrates the bottom side of object 2
			// then we have definite collision
			if( (pos1.y + (fHeight1 / 2)) > (pos2.y - (fHeight2 / 2)) )
			{
				return true;
			}
		}
		// object 1 and 2 have the same Y-axis coordinate
		else if( pos1.y == pos2.y )
		{
				return true;
		}
	}

	// right side of object A
	// penetrates the left side of object B
	// we have possible collision
	else if( (posA.x + (fWidthA / 2)) > (posB.x - (fWidthB / 2)) )
	{
		// object A is on top of object B
		if( posA.y > posB.y )
		{
			// if the bottom side of object A
			// penetrates the top side of object B
			// then we have definite collision
			if( (posA.y - (fHeightA / 2)) < (posB.y + (fHeightB / 2)) )
			{
				return true;
			}
		}
		// object A is below object B
		else if( posA.y < posB.y )
		{
			// if the top side of object A
			// penetrates the bottom side of object B
			// then we have definite collision
			if( (posA.y + (fHeightA / 2)) > (posB.y - (fHeightB / 2)) )
			{
				return true;
			}
		}
		// object A and B have the same Y-axis coordinate
		else if( posA.y == posB.y )
		{
				return true;
		}
	}

	return false;
}

bool IEnemy::IsMeshCollision(	I3DObject* pObject1,
								I3DObject* pObject2,
								bool bInverseMatrix)
{
	bool bCollision = false;

	pObject1->UpdateCollisionMesh(bInverseMatrix);
	pObject2->UpdateCollisionMesh(bInverseMatrix);

	if(pObject1->IsMeshCollision(pObject2->GetCollisionMesh(), false))
	{
		bCollision = true;
	}
	
	return bCollision;
}

void IEnemy::GenerateRandomShootTime()
{
	switch ( this->GetType() )
	{
	// small enemies
	case eTYPE_DRONE:
	case eTYPE_SNIPER:
	case eTYPE_ROLLER:
	case eTYPE_GUARD:

		switch ( this->GetBehaviour() )
		{
		case eBEHAVIOUR_LAUNCH:
			this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 0.6f);
			break;

		case eBEHAVIOUR_STRIKE:
			this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 0.6f);
			break;

		case eBEHAVIOUR_OBSTACLE:
			this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 1.5f);
			break;
		}

		break;

	// boss enemies

	case eTYPE_BOSS_1_FRAME:
		this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 4.0f);
		break;

	case eTYPE_BOSS_1_SCATTER_LEFT:
		this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 1.0f);
		break;

	case eTYPE_BOSS_1_SCATTER_RIGHT:
		this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 1.0f);
		break;

	case eTYPE_BOSS_1_CANNON:
		this->m_fRandShootTime = this->m_pTheApp->RandFloat(0.0f, 5.0f);
		break;
	}
}

void IEnemy::GenerateRandomEnterSpeed()
{
	switch ( this->GetType() )
	{
	case eTYPE_DRONE:
		this->m_fSpeedEnter = this->m_fSpeed * (this->m_pTheApp->RandFloat(1.3f, 2.5f));
		break;
	case eTYPE_SNIPER:
		this->m_fSpeedEnter = this->m_fSpeed * (this->m_pTheApp->RandFloat(1.3f, 2.0f));
		break;
	case eTYPE_ROLLER:
		this->m_fSpeedEnter = this->m_fSpeed * (this->m_pTheApp->RandFloat(1.3f, 1.5f));
		break;
	case eTYPE_GUARD:
		this->m_fSpeedEnter = this->m_fSpeed * (this->m_pTheApp->RandFloat(1.3f, 1.5f));
		break;
	}
}

void IEnemy::GenerateRandomMoveTime()
{
	if(this->m_eMove == eMOVE_STAY)
	{
		this->m_fMoveTime = this->m_pTheApp->RandFloat(0.2f, 0.6f);
	}
	else
	{
		switch ( this->GetType() )
		{
		case eTYPE_DRONE:
			this->m_fMoveTime = this->m_pTheApp->RandFloat(0.7f, 3.0f);
			break;
		case eTYPE_SNIPER:
			this->m_fMoveTime = this->m_pTheApp->RandFloat(1.0f, 2.5f);
			break;
		case eTYPE_ROLLER:
			this->m_fMoveTime = this->m_pTheApp->RandFloat(0.5f, 4.0f);
			break;
		case eTYPE_GUARD:
			this->m_fMoveTime = this->m_pTheApp->RandFloat(1.0f, 5.5f);
			break;
		case eTYPE_BOSS_1_FRAME:
			this->m_fMoveTime = 14.0f + this->m_pTheApp->RandFloat(0.0f, 9.0f);
			break;
		}
	}
}

void IEnemy::GenerateRandomFleeTime()
{
	switch( this->GetType() )
	{
	case eTYPE_DRONE:
		this->m_fFleeTime = this->m_pTheApp->RandFloat(2.5f, 7.0f);
		break;

	case eTYPE_SNIPER:
		this->m_fFleeTime = this->m_pTheApp->RandFloat(4.0f, 9.0f);
		break;

	case eTYPE_ROLLER:
		this->m_fFleeTime = this->m_pTheApp->RandFloat(8.0f, 16.0f);
		break;
	}
}

void IEnemy::SetMovementBorders()
{
	this->m_fMovementBorderY = -0.4f * this->m_fScreenHeight;

	// ship enter "end" position (Y value)
	float enterBorderMin = -0.1f * this->m_fScreenHeight;
	float enterBorderMax = 0.5f * this->m_fScreenHeight;
	this->m_fShipEnterEndPosY = this->m_pTheApp->RandFloat(enterBorderMin, enterBorderMax);

	// enter duration
	this->m_fShipEnterMoveDuration = 1.0f;
	this->m_fShipEnterMoveTimer = 0.0f;
}

void IEnemy::InitFiringSound()
{
	switch( this->m_pTheApp->RandInt(1,2) )
	{
	case 1:
		this->m_eSoundFiring = eSOUND_FIRING_NORMAL_1;
		break;
	case 2:
		this->m_eSoundFiring = eSOUND_FIRING_QUIET_1;
		break;
	}
}

void IEnemy::DamageMovement(float fFrametime)
{
	switch(this->m_eMoveDamageLevel)
	{
	case eMOVE_DAMAGE_LEVEL_0:

		if( this->m_iHealth <= (this->m_iHealthMax - (this->m_iHealthMax / 2)) )
		{
			this->m_fDamageMoveCycleTime = 0.2f;
			this->m_fDamageMoveTime = 0.015f;
			
			this->m_eMoveDamageLevel = eMOVE_DAMAGE_LEVEL_1;
		}

		break;

	case eMOVE_DAMAGE_LEVEL_1:

		if( this->m_iHealth <= (this->m_iHealthMax - (this->m_iHealthMax / 1.5f)) )
		{
			if(this->m_eBehaviour == eBEHAVIOUR_STRIKE)
			{
				this->m_fSpeed = this->m_fSpeed / 1.8f;
			}
			else
			{
				this->m_fSpeed -= this->m_fSpeed / 3;
			}
			this->m_fDamageMoveCycleTime = 0.0f;
			
			this->m_eMoveDamageLevel = eMOVE_DAMAGE_LEVEL_2;
		}

		break;
	}

	if(this->m_eMoveDamageLevel != eMOVE_DAMAGE_LEVEL_0)
	{
		D3DXVECTOR3 pos = this->GetPosition();

		// next damage move cycle
		if(this->m_fDamageMoveCycleCounter >= this->m_fDamageMoveCycleTime)
		{
			// enemy's movement speed
			float fFrameSpeed = fFrametime * this->m_fSpeed;

			if(this->m_fBlastDamageMoveCounter >= this->m_fDamageMoveTime)
			{
				switch(this->m_eMoveDamageLevel)
				{
				case eMOVE_DAMAGE_LEVEL_1:

					switch(this->m_eMoveDamageSide)
					{
					case eMOVE_DAMAGE_SIDE_LEFT:

						pos.x -= fFrameSpeed * 0.85f;
						this->m_eMoveDamageSide = eMOVE_DAMAGE_SIDE_RIGHT;

						break;

					case eMOVE_DAMAGE_SIDE_RIGHT:

						pos.x += fFrameSpeed * 0.85f;
						this->m_eMoveDamageSide = eMOVE_DAMAGE_SIDE_LEFT;

						break;
					}

					break;

				case eMOVE_DAMAGE_LEVEL_2:

					switch(this->m_eMoveDamageSide)
					{
					case eMOVE_DAMAGE_SIDE_LEFT:

						pos.x -= fFrameSpeed * 1.20f;
						this->m_eMoveDamageSide = eMOVE_DAMAGE_SIDE_RIGHT;

						break;

					case eMOVE_DAMAGE_SIDE_RIGHT:

						pos.x += fFrameSpeed * 1.20f;
						this->m_eMoveDamageSide = eMOVE_DAMAGE_SIDE_LEFT;

						break;
					}

					break;
				}

				this->SetPosition(pos);
				this->m_iDamageMoves++;

				// start counting for the next damage move
				this->m_fBlastDamageMoveCounter = 0.0f;

				if(this->m_iDamageMoves == 2)
				{
					this->m_iDamageMoves = 0;
					// start counting for the next damage move cycle
					this->m_fDamageMoveCycleCounter = 0.0f;
				}
			}
			else
			{
				this->m_fBlastDamageMoveCounter += fFrametime;
			}
		}
		else
		{
			this->m_fDamageMoveCycleCounter += fFrametime;
		}
	}
}

void IEnemy::Rotate(float fFrametime)
{
	float angleX = this->m_fAngleX;
	float angleY = this->m_fAngleY;
	float angleZ = this->m_fAngleZ;

	// get object's position to temp vector
	D3DXVECTOR3 pos = this->GetPosition();
	// get object's local matrix to temp matrix
	D3DXMATRIX& mObject = this->GetLocalMatrix();

	// rotation matrices
	D3DXMATRIX mRotationY;
	D3DXMATRIX mRotationZ;
	D3DXMatrixIdentity(&mRotationY);
	D3DXMatrixIdentity(&mRotationZ);

	/* Enemy Y-axel Rotation */

	float fRotationSpeedY = this->m_fRotationSpeed * fFrametime;

	// need to rotate left
	if(this->m_bRotateYLeft)
	{
		float fNewAngle = this->m_fAngleY + fRotationSpeedY;

		// default rotation speed is too much
		// enemy will rotate over it's max rotation
		// need to rotate less than default
		if(fNewAngle > this->m_fMaxRotation)
		{
			float fAngleIncrease = this->m_fMaxRotation - this->m_fAngleY;
			this->m_fAngleY += fAngleIncrease;
		}
		// enemy rotates in default speed (fRotationSpeedY)
		else
		{
			this->m_fAngleY += fRotationSpeedY;
		}
	}
	// need to rotate right
	else if(this->m_bRotateYRight)
	{
		float fNewAngle = this->m_fAngleY - fRotationSpeedY;

		// default rotation speed is too much
		// enemy will rotate over it's max rotation
		// need to rotate less than default
		if(fNewAngle < -this->m_fMaxRotation)
		{
			float fAngleIncrease = -this->m_fMaxRotation - this->m_fAngleY;
			this->m_fAngleY += fAngleIncrease;
		}
		// enemy rotates in default speed (fRotationSpeedY)
		else
		{
			this->m_fAngleY += -fRotationSpeedY;
		}
	}
	// straighten enemy
	else if(this->m_bRotateYStraight)
	{
		// enemy is not rotated to straight position
		if( this->m_fAngleY != 0.0f )
		{
			// sideways direction changed in the middle of straightening
			// start to turn-rotate in the correct direction
			if(	(this->m_eMove != this->m_eMoveOld) && 
				(this->m_eMove != eMOVE_STAY) && 
				(this->m_eMove != eMOVE_UP) && 
				(this->m_eMove != eMOVE_DOWN) )
			{
				this->m_bRotateYStraight = false;

				if( (this->m_eMove == eMOVE_LEFT) || 
					(this->m_eMove == eMOVE_UP_LEFT) || 
					(this->m_eMove == eMOVE_DOWN_LEFT) )
				{
					this->m_bRotateYLeft = true;
					this->m_bRotateYRight = false;
					// rotate left
					this->m_fAngleY += fRotationSpeedY;
				}
				else if((this->m_eMove == eMOVE_RIGHT) || 
						(this->m_eMove == eMOVE_UP_RIGHT) || 
						(this->m_eMove == eMOVE_DOWN_RIGHT) )
				{
					this->m_bRotateYLeft = false;
					this->m_bRotateYRight = true;
					// rotate right
					this->m_fAngleY -= fRotationSpeedY;
				}
			}
			// straighten enemy
			else
			{
				// straighten to left side
				if( this->m_fAngleY < 0.0f)
				{
					// default straightening speed is too much
					// enemy will rotate over it's straight position
					// need to rotate less than default
					if( (this->m_fAngleY + fRotationSpeedY) > 0.0f)
					{
						// fAngle IS negative, so we get a positive angle
						// straightens to left side
						this->m_fAngleY += -this->m_fAngleY;
					}
					// enemy straightens in default speed (fRotationSpeedY)
					else
					{
						this->m_fAngleY += fRotationSpeedY;
					}
				}
				// straighten to right side
				else if( this->m_fAngleY > 0.0f)
				{
					// default straightening speed is too much
					// enemy will rotate over it's straight position
					// need to rotate less than default
					if( (this->m_fAngleY - fRotationSpeedY) < 0.0f)
					{
						// fAngle IS positive, so we get a negative angle
						// straightens to right side
						this->m_fAngleY += -this->m_fAngleY;
					}
					// enemy straightens in default speed (fRotationSpeedY)
					else
					{
						this->m_fAngleY += -fRotationSpeedY;
					}
				}
			}
		}
		// enemy is rotated to straight position
		else if( this->m_fAngleY == 0.0f )
		{
			// make sure that enemy is in straight position
			D3DXVECTOR3 vPos = this->GetPosition();
			this->SetDefaultMatrix();
			this->SetPosition(vPos);

			this->m_bRotateYStraight = false;
			this->m_bIsStraightY = true;

			// start rotating to left or right 
			// if moving in that direction
			if( (this->m_eMove == eMOVE_LEFT) || 
				(this->m_eMove == eMOVE_UP_LEFT) || 
				(this->m_eMove == eMOVE_DOWN_LEFT) )
			{
				this->m_bRotateYLeft = true;
				this->m_bRotateYRight = false;
			}
			else if((this->m_eMove == eMOVE_RIGHT) || 
					(this->m_eMove == eMOVE_UP_RIGHT) || 
					(this->m_eMove == eMOVE_DOWN_RIGHT) )
			{
				this->m_bRotateYRight = true;
				this->m_bRotateYLeft = false;
			}
			// backup the info of current movement
			this->m_eMoveOld = this->m_eMove;
		}
	}
	// rotate enemy left
	if( this->m_bRotateYLeft )
	{
		// not reached max rotation angle
		if( this->m_fAngleY < this->m_fMaxRotation)
		{
			// check if left/right movement has changed
			if( this->RotateToStraight() )
			{
				this->m_bRotateYLeft = false;
				// start rotating enemy to straight position
				this->m_bRotateYStraight = true;
				// backup the info of current movement
				this->m_eMoveOld = this->m_eMove;
			}
			else
			{
				if( this->m_bIsStraightY )
				{
					this->m_bIsStraightY = false;
				}
			}
		}
		// reached max rotation angle
		else if( this->m_fAngleY == this->m_fMaxRotation)
		{
			this->m_bRotateYLeft = false;
			// start enemy straightening checking
			this->m_bCheckStraighteningY = true;
			// backup the info of current movement
			this->m_eMoveOld = this->m_eMove;
		}
	}
	// rotate enemy right
	else if( this->m_bRotateYRight )
	{
		// not reached max rotation angle
		if( this->m_fAngleY > -this->m_fMaxRotation)
		{
			// check if left/right movement has changed
			if( this->RotateToStraight() )
			{
				this->m_bRotateYRight = false;
				// start rotating enemy to straight position
				this->m_bRotateYStraight = true;
				// backup the info of current movement
				this->m_eMoveOld = this->m_eMove;
			}
			else
			{
				if( this->m_bIsStraightY )
				{
					this->m_bIsStraightY = false;
				}
			}
		}
		// reached max rotation angle
		else if( this->m_fAngleY == -this->m_fMaxRotation)
		{
			this->m_bRotateYRight = false;
			// start enemy straightening checking
			this->m_bCheckStraighteningY = true;
			// backup the info of current movement
			this->m_eMoveOld = this->m_eMove;
		}
	}
	// enemy has reached max rotation angle  
	// and is not yet started to rotate straight
	if( this->m_bCheckStraighteningY )
	{
		if( this->RotateToStraight() )
		{
			// stop enemy straightening checking
			this->m_bCheckStraighteningY = false;

			// start rotating enemy to straight position
			this->m_bRotateYStraight = true;
		}
	}

	// backup the info of current movement
	if(this->m_eMoveOld != this->m_eMove)
	{
		this->m_eMoveOld = this->m_eMove;
	}

	/* Enemy X-axel Rotation */

	if(this->m_eRotationX != eROTATION_X_NONE)
	{
		//...
	}

	/* Enemy Z-axel Rotation */

	if(this->m_eRotationZ != eROTATION_Z_NONE)
	{
		// enemy's movement speed
		float fFrameSpeed = (fFrametime * this->m_fSpeed) / this->m_fSpeedDivider;

		float fRotationSpeed = 0.0f;
		float fSpeedMultiplier = 0.0f;

		switch(this->m_eType)
		{
		case eTYPE_ROLLER:

			switch(this->m_eRollerAction)
			{
			case eROLLER_ACTION_PASSIVE:
				fSpeedMultiplier = 0.025f;
				break;

			case eROLLER_ACTION_ATTACK:
				fSpeedMultiplier = 0.075f;
				break;
			}

			switch(this->m_eRotationZ)
			{
			case eROTATION_Z_LEFT:
				this->m_fAngleZ -= fFrameSpeed * fSpeedMultiplier;
				break;

			case eROTATION_Z_RIGHT:
				this->m_fAngleZ += fFrameSpeed * fSpeedMultiplier;
				break;
			}

			break;
		}
	}

	if (angleX != this->m_fAngleX) {
		this->SetRotateX(this->m_fAngleX);
	}
	if (angleY != this->m_fAngleY) {
		this->SetRotateY(this->m_fAngleY);
	}
	if (angleZ != this->m_fAngleZ) {
		this->SetRotateZ(this->m_fAngleZ);
	}
}

void IEnemy::CheckMovement()
{
	// check straightening first
	if(this->RotateToStraight())
	{
		this->m_bRotateYStraight = true;
	}

	// enemy is not moving or 
	// is moving up or down
	if(	(this->m_eMove == eMOVE_STAY) || 
		(this->m_eMove == eMOVE_UP) || 
		(this->m_eMove == eMOVE_DOWN) )
	{
		if(this->m_bRotateYLeft)
		{
			this->m_bRotateYLeft = false;
		}
		if(this->m_bRotateYRight)
		{
			this->m_bRotateYRight = false;
		}
		if(!this->m_bIsStraightY)
		{
			if(!this->m_bRotateYStraight)
			{
				this->m_bRotateYStraight = true;
			}
		}
	}
	else
	{
		// enemy is moving leftward
		if((this->m_eMove == eMOVE_LEFT) || 
			(this->m_eMove == eMOVE_UP_LEFT) || 
			(this->m_eMove == eMOVE_DOWN_LEFT) )
		{
			if(this->m_bRotateYRight)
			{
				this->m_bRotateYRight = false;
			}

			// enemy is not rotating to straight position
			if(!this->m_bRotateYStraight)
			{
				if(!this->m_bRotateYLeft)
				{
					this->m_bRotateYLeft = true;
				}
			}
		}
		// enemy is moving rightward
		else if(	(this->m_eMove == eMOVE_RIGHT) || 
					(this->m_eMove == eMOVE_UP_RIGHT) || 
					(this->m_eMove == eMOVE_DOWN_RIGHT) )
		{
			if(this->m_bRotateYLeft)
			{
				this->m_bRotateYLeft = false;
			}
			// enemy is not rotating to straight position
			if(!this->m_bRotateYStraight)
			{
				if(!this->m_bRotateYRight)
				{
					this->m_bRotateYRight = true;
				}
			}
		}
	}
}

bool IEnemy::RotateToStraight()
{
	// enemy was moving leftward
	if(	(this->m_eMoveOld == eMOVE_LEFT) || 
		(this->m_eMoveOld == eMOVE_UP_LEFT) || 
		(this->m_eMoveOld == eMOVE_DOWN_LEFT) )
	{
		// enemy starts to move elsewhere than leftward
		if(	(this->m_eMove == eMOVE_STAY) || 
			(this->m_eMove == eMOVE_UP) || 
			(this->m_eMove == eMOVE_DOWN) || 
			(this->m_eMove == eMOVE_RIGHT) || 
			(this->m_eMove == eMOVE_UP_RIGHT) || 
			(this->m_eMove == eMOVE_DOWN_RIGHT) )
		{
			// backup the info of current movement
			// for straightening rotation to activate correctly
			this->m_eMoveOld = this->m_eMove;
			return true;
		}
	}
	// enemy was moving rightward
	if(	(this->m_eMoveOld == eMOVE_RIGHT) || 
		(this->m_eMoveOld == eMOVE_UP_RIGHT) || 
		(this->m_eMoveOld == eMOVE_DOWN_RIGHT) )
	{
		// enemy starts to move elsewhere than rightward
		if(	(this->m_eMove == eMOVE_STAY) || 
			(this->m_eMove == eMOVE_UP) || 
			(this->m_eMove == eMOVE_DOWN) || 
			(this->m_eMove == eMOVE_LEFT) || 
			(this->m_eMove == eMOVE_UP_LEFT) || 
			(this->m_eMove == eMOVE_DOWN_LEFT) )
		{
			// backup the info of current movement
			// for straightening rotation to activate correctly
			this->m_eMoveOld = this->m_eMove;
			return true;
		}
	}
	return false;
}

void IEnemy::CorrectZAxisPosition()
{
	// fix enemy z-axis position

	if(this->m_eBehaviour != eBEHAVIOUR_REINFORCEMENT)
	{
		D3DXVECTOR3 pos; 
		pos = this->GetPosition();

		if( (this->m_eType == eTYPE_BOSS_1_SCATTER_LEFT) || 
			(this->m_eType == eTYPE_BOSS_1_SCATTER_RIGHT))
		{
			pos.z = -30.0f;
		}
		else if((this->m_eType == eTYPE_BOSS_1_LASER_LEFT) || 
				(this->m_eType == eTYPE_BOSS_1_LASER_RIGHT))
		{
			pos.z = -7.0f;
		}
		else
		{
			pos.z = 0.0f;
		}
		
		this->SetPosition(pos);
	}
}

void IEnemy::StraightenEnemy()
{
	// enemy is not rotated to straight position
	if( this->m_fAngleY != 0.0f )
	{
		this->SetRotateY( -(this->m_fAngleY) );
		this->m_fAngleY = 0.0f;
	}
}

void IEnemy::MoveEnter(float fFrametime, float fPlayerVelocity)
{
	// play afterburn sound
	if (this->m_bEnterSound)
	{
		this->m_bEnterSound = false;

		this->m_pTheApp->GetWave(SOUND_ENEMY_ENTER_AFTERBURN).Play(
			FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
	}

	D3DXVECTOR3 pos = this->GetPosition();

	if (this->m_bSetShipEnterDuration)
	{
		this->m_bSetShipEnterDuration = false;
		this->m_fShipEnterStartPosY = pos.y;

		float enterSpeed = this->m_pGameSettings->m_fEnemyDroneEnterSpeed;
		this->m_fShipEnterMoveDuration = enterSpeed * (this->m_fShipEnterStartPosY - this->m_fShipEnterEndPosY);
	}

	this->m_fShipEnterMoveTimer += fFrametime;
	this->m_fShipEnterMoveTimer = min(this->m_fShipEnterMoveTimer, this->m_fShipEnterMoveDuration);

	float delta = m_fShipEnterMoveTimer / this->m_fShipEnterMoveDuration;

	float currentPosY = LerpUtils::CalculateEasingPosition(
		LerpUtils::eEASING_LOGIC::EaseOutSine, this->m_fShipEnterStartPosY, this->m_fShipEnterEndPosY,
		this->m_fShipEnterMoveTimer, this->m_fShipEnterMoveDuration);

	pos.y = currentPosY;
	this->SetPosition(pos);

	// disable afterburn effect
	if (delta > SHIP_ENTER_AFTERBURN_END_DELTA)
	{
		SetAfterburn(false);
	}

	// finished the "ship enter" movement
	if (this->m_fShipEnterMoveTimer == this->m_fShipEnterMoveDuration)
	{
		this->m_bEnter = false;

		this->m_bEnterSound = true;

		this->m_bRotateYLeft = false;
		this->m_bRotateYRight = false;
		this->m_bRotateYStraight = false;
		this->m_bCheckStraighteningY = false;
		this->m_bIsStraightY = true;

		this->SetMoveState();
		this->GenerateRandomMoveTime();
	}
}

void IEnemy::MoveFlee(float fFrametime, float fPlayerVelocity)
{
	// play afterburn sound
	if (this->m_bFleeSound)
	{
		this->m_bFleeSound = false;

		this->m_pTheApp->GetWave(SOUND_ENEMY_LEAVE_AFTERBURN).Play(
			FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
	}

	D3DXVECTOR3 pos = this->GetPosition();

	float fFrameSpeed = fFrametime * (this->m_fSpeed / 2.0f) + this->m_fFleeSpeedIncrease;
	this->m_fFleeSpeedIncrease += (fFrametime * 2.0f) + (this->m_fFleeSpeedMultiplier / 2.0f);

	pos.y -= fFrameSpeed;
	this->SetPosition(pos);
}

void IEnemy::Move(float fFrametime, float fPlayerVelocity)
{
	// get enemy's position to temp vector
	D3DXVECTOR3 pos = this->GetPosition();

	bool bValidVerticalMovement = false;
	bool bValidHorizontalMovement = false;

	if (this->m_eBehaviour == eBEHAVIOUR_OBSTACLE)
	{
		bValidVerticalMovement = true;
	}

	if (this->m_bFleeMovement || (this->m_eBehaviour == eBEHAVIOUR_STRIKE) || (this->m_eBehaviour == eBEHAVIOUR_BOSS))
	{
		bValidVerticalMovement = true;
		bValidHorizontalMovement = true;
	}

	float fTopMoveBorder = (0.75f * this->m_fScreenHeight) - (this->m_fEnemyHeight / 2.0f);
	float fBottomMoveBorder = this->m_fMovementBorderY + (this->m_fEnemyHeight / 2.0f);

	float fMovementBorder1 = 0.0f;
	float fMovementBorder2 = 0.0f;

	float fFrameSpeed = 0.0f;

	// movement speed (frame speed)
	fFrameSpeed = fFrametime * this->m_fSpeed;

	// change movement
	if( this->m_fMoveTime <= 0.0f )
	{
		this->SetMoveState();
		this->GenerateRandomMoveTime();
	}

	switch( this->m_eMove )
	{
	// move up
	case IEnemy::eMOVE_UP:

		if ((pos.y + fFrameSpeed) < fTopMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if (bValidVerticalMovement)
		{
			pos.y += fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}
		
		break;

	// move down
	case IEnemy::eMOVE_DOWN:

		if ((pos.y - fFrameSpeed) > fBottomMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if (bValidVerticalMovement)
		{
			pos.y -= fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;

	// move left
	case IEnemy::eMOVE_LEFT:

		fMovementBorder1 = -this->m_fScreenWidth + (this->GetWidth() / 1.5f);

		if ((pos.y - fFrameSpeed) > fBottomMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if ((pos.x - fFrameSpeed) > fMovementBorder1)
		{
			bValidHorizontalMovement = true;
		}

		if(bValidVerticalMovement || bValidHorizontalMovement)
		{
			pos.x -= fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;

	// move right
	case IEnemy::eMOVE_RIGHT:

		fMovementBorder1 = this->m_fScreenWidth - (this->GetWidth() / 1.5f);

		if ((pos.y - fFrameSpeed) > fBottomMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if ((pos.x + fFrameSpeed) < fMovementBorder1)
		{
			bValidHorizontalMovement = true;
		}

		if(bValidVerticalMovement || bValidHorizontalMovement)
		{
			pos.x += fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;

	// move up-left
	case IEnemy::eMOVE_UP_LEFT:

		fMovementBorder1 = -this->m_fScreenWidth + (this->GetWidth() / 1.5f);

		if ((pos.y + fFrameSpeed) < fTopMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if ((pos.x - fFrameSpeed) > fMovementBorder1)
		{
			bValidHorizontalMovement = true;
		}

		if(bValidVerticalMovement && bValidHorizontalMovement)
		{
			pos.y += fFrameSpeed;
			pos.x -= fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;

	// move up-right
	case IEnemy::eMOVE_UP_RIGHT:

		fMovementBorder1 = this->m_fScreenWidth - (this->GetWidth() / 1.5f);

		if ((pos.y + fFrameSpeed) < fTopMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if ((pos.x + fFrameSpeed) < fMovementBorder1)
		{
			bValidHorizontalMovement = true;
		}

		if(bValidVerticalMovement && bValidHorizontalMovement)
		{
			pos.y += fFrameSpeed;
			pos.x += fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;

	// move down-left
	case IEnemy::eMOVE_DOWN_LEFT:

		fMovementBorder1 = -this->m_fScreenWidth + (this->GetWidth() / 1.5f);

		if ((pos.y - fFrameSpeed) > fBottomMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if (((pos.x - fFrameSpeed) > fMovementBorder1))
		{
			bValidHorizontalMovement = true;
		}

		if(bValidVerticalMovement && bValidHorizontalMovement)
		{
			pos.y -= fFrameSpeed;
			pos.x -= fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;

	// move down-right
	case IEnemy::eMOVE_DOWN_RIGHT:

		fMovementBorder1 = this->m_fScreenWidth - (this->GetWidth() / 1.5f);

		if ((pos.y - fFrameSpeed) > fBottomMoveBorder)
		{
			bValidVerticalMovement = true;
		}

		if ((pos.x + fFrameSpeed) < fMovementBorder1)
		{
			bValidHorizontalMovement = true;
		}

		if (bValidVerticalMovement && bValidHorizontalMovement)
		{
			pos.y -= fFrameSpeed;
			pos.x += fFrameSpeed;
		}
		else
		{
			this->SetMoveState();
			this->GenerateRandomMoveTime();
		}

		break;
	}

	// player velocity affecting the enemy ships
	if (this->m_eBehaviour == eBEHAVIOUR::eBEHAVIOUR_OBSTACLE)
	{
		float fVelocitySpeed = fFrametime * fPlayerVelocity;
		pos.y -= fVelocitySpeed;
	}

	this->SetPosition(pos);
}

void IEnemy::MoveReinforcement(float fFrametime, float fPlayerVelocity)
{
	// enemy's movement speed
	float fFrameSpeed = fFrametime * this->m_fSpeed;

	// enemy's current position
	D3DXVECTOR3 pos = this->GetPosition();

	if(this->m_bSpeedSlowDown)
	{
		pos.y -= (fFrameSpeed / this->m_fSpeedDivider) * 0.66f;
	}
	else
	{
		pos.y -= fFrameSpeed / this->m_fSpeedDivider;
	}

	this->SetPosition(pos);
}

void IEnemy::MoveReinforcementSpeedChange(float fFrametime, float fPlayerVelocity)
{
	// enemy's movement speed
	this->m_fSpeed = this->m_fSpeed * this->m_fSpeedChangeMultiplier;
	float fFrameSpeed = fFrametime * this->m_fSpeed;

	// enemy's current position
	D3DXVECTOR3 pos = this->GetPosition();

	if(this->m_bSpeedSlowDown)
	{
		pos.y -= (fFrameSpeed / this->m_fSpeedDivider) * 0.66f;
	}
	else
	{
		pos.y -= fFrameSpeed / this->m_fSpeedDivider;
	}

	this->SetPosition(pos);
}

void IEnemy::SetDepth(int depth)
{
	switch (depth)
	{
	case 1:
		SetDepth(eENEMY_DEPTH::eENEMY_DEPTH_1);
		break;
	case 2:
		SetDepth(eENEMY_DEPTH::eENEMY_DEPTH_2);
		break;
	case 3:
		SetDepth(eENEMY_DEPTH::eENEMY_DEPTH_3);
		break;
	case 4:
		SetDepth(eENEMY_DEPTH::eENEMY_DEPTH_4);
		break;
	case 5:
		SetDepth(eENEMY_DEPTH::eENEMY_DEPTH_5);
		break;
	}
}

void IEnemy::SetDepth(eENEMY_DEPTH eDepth)
{
	D3DXVECTOR3 pos = this->GetPosition();
	float depth = this->GetDepthValue(4);

	switch(eDepth)
	{
	case eENEMY_DEPTH_2:
		depth = this->GetDepthValue(6);
		break;

	case eENEMY_DEPTH_3:
		depth = this->GetDepthValue(7);
		break;

	case eENEMY_DEPTH_4:
		depth = this->GetDepthValue(8);
		break;

	case eENEMY_DEPTH_5:
		depth = this->GetDepthValue(9);
		break;
	}

	pos.z = depth;
	this->SetPosition(pos);

	this->m_eDepth = eDepth;
}