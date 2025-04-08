#include "EnemyBoss1Cannon.h"

CEnemyBoss1Cannon::CEnemyBoss1Cannon(	eTYPE eType,
										eBEHAVIOUR eBehaviour)
{
	this->m_eType = eType;
	this->m_eBehaviour = eBehaviour;

	this->m_pSpriteCannonCharge = NULL;
	this->m_pSpriteCannonShoot = NULL;

	this->m_eAction = eACTION_WAIT;

	this->m_iCannonDamage = 0;

	this->GenerateRandomShootTime();
}

CEnemyBoss1Cannon::~CEnemyBoss1Cannon(void)
{
}

HRESULT CEnemyBoss1Cannon::Create(	CTheApp* pTheApp,
									CGameSettings* pGameSettings,
									LPD3DXMESH mesh,
									std::vector<D3DMATERIAL9*> materials,
									std::vector<LPDIRECT3DTEXTURE9> textures,
									int iVolumeSoundEffect)
{
	HRESULT hres;

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

	this->Scale();
	this->ResetPosition();

	// sound effect volume
	int iVolume = pTheApp->GetConfig().GetVolumeSoundEffect();

	if (iVolume == 0)
	{
		this->m_iVolumeSoundEffect = -10000;
	}
	else
	{
		float fVolume = pGameSettings->m_fVolumeBossCannon * (float)iVolume;
		float fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumeSoundEffect = (int)fExactVolume;
	}

	return S_OK;
}

void CEnemyBoss1Cannon::Init(	CTheApp* pTheApp,
								CGameSettings* pGameSettings,
								CSprite* pSpriteAfterburn,
								int iVolumeSoundEffect)
{
	this->m_bBoss = true;
	this->m_bEnter = true;

	this->m_fEnemyWidth = 0.0f;
	this->m_fEnemyHeight = 0.0f;

	this->m_iHealth = 0;
	this->m_iHealthMax = this->m_iHealth;

	this->m_fSpeed = pGameSettings->m_fEnemyBoss1CannonSpeed;
	this->m_fSpeedDefault = this->m_fSpeed;

	this->m_fShootTime = pGameSettings->m_fEnemyBoss1CannonShootTime;
	this->m_iCannonDamage = pGameSettings->m_iEnemyBoss1CannonDamage;

	this->m_fShootCounter = this->m_fShootTime + 5.0f;

	IEnemy::Init(pTheApp, pGameSettings, pSpriteAfterburn, iVolumeSoundEffect);
}

void CEnemyBoss1Cannon::Release()
{
	CEnemyBoss::Release();
}

void CEnemyBoss1Cannon::UpdateShip(IEnemy* pBossFrame,
	bool bShootPossible,
	float fFrametime)
{
	if (!this->m_bEnter)
	{
		switch (this->m_eAction)
		{
		case eACTION_WAIT:

			if (bShootPossible)
			{
				if (pBossFrame->IsActive())
				{
					if (this->Shoot())
					{
						this->m_eAction = eACTION_CHARGE;

						// reset shoot counter
						this->m_fShootCounter = 0.0f;
						// get new random shoot time
						this->GenerateRandomShootTime();

						this->SetShootCount(false);

						// play sound effect
						this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_CANNON_CHARGE).Play(
							FALSE, 0, this->m_iVolumeSoundEffect);
					}
				}
			}

			break;

		case eACTION_CHARGE:

			D3DXVECTOR3 posFrame = pBossFrame->GetPosition();

			posFrame.y -= 86.0f;
			this->SetPosition(posFrame);

			break;
		}
	}

	IEnemy::Update(fFrametime, 0.0f);
}

void CEnemyBoss1Cannon::Render(IEnemy* pBossFrame,
	float fFrametime,
	bool bPause)
{
	if (!this->m_bEnter)
	{
		D3DXVECTOR3 posFrame = pBossFrame->GetPosition();

		switch (this->m_eAction)
		{
		case eACTION_CHARGE:

			if (pBossFrame->IsActive())
			{
				if (!this->ChargeCannon(posFrame, fFrametime, bPause))
				{
					this->m_eAction = eACTION_BEAM;
					// play sound effect
					this->m_pTheApp->GetWave(SOUND_SHOOT_BOSS_1_CANNON_SHOOT).Play(
						FALSE, 0, this->m_iVolumeSoundEffect);
				}
			}

			break;

		case eACTION_BEAM:

			if (!this->ShootCannon(posFrame, fFrametime, bPause))
			{
				this->m_eAction = eACTION_WAIT;
			}

			break;
		}
	}
}

void CEnemyBoss1Cannon::InitWeapons(CSprite *pSpriteCannonCharge,
									CSprite *pSpriteCannonBeam)
{
	this->m_pSpriteCannonCharge = pSpriteCannonCharge;
	this->m_pSpriteCannonShoot = pSpriteCannonBeam;
}

bool CEnemyBoss1Cannon::ChargeCannon(	D3DXVECTOR3 posFrame,
										float fFrametime,
										bool bPause)
{
	const float fPixelMultiplier = 2.5f;

	static float fCounter = 0.0f;
	static float fSpriteTime = 0.03f;
	static int iIndex = 0;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	D3DXVECTOR3 posCharge = posFrame;

	posCharge.y -= 50.0f;
	posCharge.y -= iIndex * 1.0f;

	// x-position

	fMoveX = posCharge.x * fPixelMultiplier;
	iPosX = ( (this->m_fScreenPixelWidth / 2) - 12.0f) + fMoveX;

	// y-position

	fMoveY = posCharge.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosY = ( (this->m_fScreenPixelHeight / 2) - 12.0f) + fMoveY;

	// fine-tune position
	iPosX -= 35;
	iPosY += 7;

	// draw cannon charge
	this->m_pSpriteCannonCharge[iIndex].Draw(iPosX, iPosY);

	if(!bPause)
	{
		if( iIndex == (ENEMYBOSS1CANNON_CHARGE_MAX - 1) )
		{
			iIndex = 0;
			return false;
		}
		else
		{
			if(fCounter >= fSpriteTime)
			{
				fCounter = 0.0f;
				iIndex++;
			}
			else
			{
				fCounter += fFrametime;
			}
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool CEnemyBoss1Cannon::ShootCannon(D3DXVECTOR3 posFrame,
									float fFrametime,
									bool bPause)
{
	const float fPixelMultiplier = 2.5f;

	static bool bStart = true;
	static int iIndex = 0;
	static float fSpriteCounter = 0.0f;
	static float fSpriteTime = 0.03f;
	static float fPosY = 0.0f;
	static D3DXVECTOR3 posCurrent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float fFrameSpeed = fFrametime * this->m_fSpeed;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	D3DXVECTOR3 posStart = posFrame;

	if(bStart)
	{
		bStart = false;
		posStart.y -= 86.0f;
		this->SetPosition(posStart);

		posCurrent = posStart;
		fPosY = posCurrent.y;
	}

	if( fPosY < -(this->m_fScreenHeight + 30.0f) )
	{
		bStart = true;
		iIndex = 0;
		fSpriteCounter = 0.0f;

		this->ResetPosition();
		this->SetShootCount(true);

		return false;
	}
	else
	{
		if(!bPause)
		{
			fPosY -= fFrameSpeed;
		}
		posCurrent.y = fPosY;

		this->SetPosition(posCurrent);

		// draw sprite //

		// x-position

		fMoveX = posCurrent.x * fPixelMultiplier;
		iPosX = ( (this->m_fScreenPixelWidth / 2) - 12.0f) + fMoveX;

		// y-position

		fMoveY = posCurrent.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;

		iPosY = ( (this->m_fScreenPixelHeight / 2) - 12.0f) + fMoveY;

		// fine-tune position
		iPosX -= 36;
		iPosY -= 38;

		// draw cannon shoot
		this->m_pSpriteCannonShoot[iIndex].Draw(iPosX, iPosY);

		if(fSpriteCounter >= fSpriteTime)
		{
			fSpriteCounter = 0.0f;
			
			if(!bPause)
			{
				iIndex++;
			}

			if(iIndex == 2)
			{
				iIndex = 0;
			}
		}
		else
		{
			fSpriteCounter += fFrametime;
		}

		return true;
	}
}

void CEnemyBoss1Cannon::Scale()
{
	this->SetScaleX(1.1f);
	this->SetScaleY(1.1f);
	this->SetScaleZ(1.1f);
}

void CEnemyBoss1Cannon::ResetPosition()
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, this->m_fScreenHeight + 50.0f, this->GetDepthValue(1));
	this->SetPosition(pos);
}

void CEnemyBoss1Cannon::MoveEnter(float fFrametime, float fPlayerVelocity)
{
}