#include "Explosion.h"

CExplosion::CExplosion()
{
	this->m_pTheApp = NULL;
	this->m_pSpritesExplosion = NULL;

	this->m_bActive = false;

	this->m_iSpriteIndex = 0;
	this->m_iSpriteCount = 0;

	this->m_iMoveSpeed = 0;

	this->m_fMovePause = 0.0f;
	this->m_fMovePauseMax = 0.0f;

	this->m_fDrawPause = 0.0f;
	this->m_fDrawPauseMax = 0.0f;

	this->m_fScreenWidth = 0.0f;
	this->m_fScreenHeight = 0.0f;

	this->m_iPosStartX = 0;
	this->m_iPosStartY = 0;
	this->m_iPosY = 0;
}

CExplosion::~CExplosion()
{
}

void CExplosion::Create(CTheApp* pTheApp,
						CSprite* pSpritesExplosion,
						eEXPLOSION_TYPE eExplosionType,
						int iSpriteCount,
						float fDrawPause,
						float fScreenWidth,
						float fScreenHeight)
{
	this->m_pTheApp = pTheApp;
	this->m_pSpritesExplosion = pSpritesExplosion;

	this->m_eExplosionType = eExplosionType;
	
	this->m_iSpriteCount = iSpriteCount;

	this->m_fDrawPauseMax = fDrawPause;

	this->m_fScreenWidth = fScreenWidth;
	this->m_fScreenHeight = fScreenHeight;
}

void CExplosion::Init(	int iMoveSpeed,
						float fMovePause,
						D3DXVECTOR3 posStart)
{
	this->m_iPosY = 0;
	this->m_iSpriteIndex = 0;

	this->m_fDrawPause = this->m_fDrawPauseMax;

	this->m_iMoveSpeed = iMoveSpeed;
	this->m_iDefaultSpeed = iMoveSpeed;

	this->m_fMovePause = fMovePause;
	this->m_fMovePauseMax = fMovePause;

	this->InitPosition(posStart);

	this->m_bActive = true;
}

void CExplosion::Update(float fFrametime)
{
	// explosion is active, can be updated
	if(this->m_bActive)
	{
		// update explosion position

		if(this->m_fMovePause <= 0.0f)
		{
			if(this->m_fMovePauseMax > 0.0f)
			{
				while(this->m_fMovePause <= 0.0f)
				{
					this->m_fMovePause += this->m_fMovePauseMax;
					this->m_iPosY += this->m_iMoveSpeed;
				}
			}
			else
			{
				this->m_fMovePause = this->m_fMovePauseMax;
				this->m_iPosY += this->m_iMoveSpeed;
			}
		}
		else
		{
			this->m_fMovePause -= fFrametime;
		}

		// update explosion index

		if(this->m_fDrawPause <= 0.0f)
		{
			while(this->m_fDrawPause <= 0.0f)
			{
				this->m_fDrawPause += this->m_fDrawPauseMax;
				this->m_iSpriteIndex++;

				// counter went over the last index
				if(this->m_iSpriteIndex == this->m_iSpriteCount)
				{
					// deactivate explosion
					this->m_bActive = false;
					return;
				}
			}
		}
		else
		{
			this->m_fDrawPause -= fFrametime;
		}
	}
}

void CExplosion::Render()
{
	// explosion is active, can be rendered
	if(this->m_bActive)
	{
		int posY = this->m_iPosStartY + this->m_iPosY;

		// draw explosion
		(this->m_pSpritesExplosion + m_iSpriteIndex)->Draw(	this->m_iPosStartX, 
															posY);
	}
}

void CExplosion::InitPosition(D3DXVECTOR3 posStart)
{
	this->m_posStart = posStart;

	const float fPixelMultiplier = 2.5f;

	float fMoveX;
	float fMoveY;

	switch(this->m_eExplosionType)
	{
	case eEXPLOSION_TYPE_PLAYER:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = ( (this->m_fScreenWidth / 2) + 292.0f) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = ( (this->m_fScreenHeight / 2) + 175.0f) + fMoveY;

		break;

	case eEXPLOSION_TYPE_DRONE:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = ( (this->m_fScreenWidth / 2) + 249.0f) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = ( (this->m_fScreenHeight / 2) + 176.0f) + fMoveY;

		break;

	case eEXPLOSION_TYPE_SNIPER:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = ( (this->m_fScreenWidth / 2) + 245.0f) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = ( (this->m_fScreenHeight / 2) + 173.0f) + fMoveY;

		break;

	case eEXPLOSION_TYPE_ROLLER:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = ( (this->m_fScreenWidth / 2) + 228.0f) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = ( (this->m_fScreenHeight / 2) + 146.0f) + fMoveY;

		break;

	case eEXPLOSION_TYPE_GUARD:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = ( (this->m_fScreenWidth / 2) + 250.0f) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = ( (this->m_fScreenHeight / 2) + 180.0f) + fMoveY;

		break;

	case eEXPLOSION_TYPE_BOSS_1_BIG:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = (this->m_fScreenWidth / 2) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = (this->m_fScreenHeight / 2) + fMoveY;

		this->m_iPosStartX -= 94;
		this->m_iPosStartY -= 89;

		break;

	case eEXPLOSION_TYPE_BOSS_1_PART:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = (this->m_fScreenWidth / 2) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = (this->m_fScreenHeight / 2) + fMoveY;

		this->m_iPosStartX += 256;
		this->m_iPosStartY += 186;

		break;

	case eEXPLOSION_TYPE_BOSS_1_CHAIN_1:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = (this->m_fScreenWidth / 2) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = (this->m_fScreenHeight / 2) + fMoveY;

		this->m_iPosStartX += 245;
		this->m_iPosStartY += 180;

		// random position

		switch(this->m_pTheApp->RandInt(1,2))
		{
		// move up
		case 1:
			this->m_iPosStartY -= this->m_pTheApp->RandInt(0,95);
			break;

		// move down
		case 2:
			this->m_iPosStartY += this->m_pTheApp->RandInt(0,95);
			break;
		}

		switch(this->m_pTheApp->RandInt(1,2))
		{
		// move left
		case 1:
			this->m_iPosStartX -= this->m_pTheApp->RandInt(0,70);
			break;

		// move right
		case 2:
			this->m_iPosStartX += this->m_pTheApp->RandInt(0,80);
			break;
		}

		break;

	case eEXPLOSION_TYPE_BOSS_1_CHAIN_2:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = (this->m_fScreenWidth / 2) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = (this->m_fScreenHeight / 2) + fMoveY;

		this->m_iPosStartX += 275;
		this->m_iPosStartY += 210;

		// random position

		switch(this->m_pTheApp->RandInt(1,2))
		{
		// move up
		case 1:
			this->m_iPosStartY -= this->m_pTheApp->RandInt(0,115);
			break;

		// move down
		case 2:
			this->m_iPosStartY += this->m_pTheApp->RandInt(0,115);
			break;
		}

		switch(this->m_pTheApp->RandInt(1,2))
		{
		// move left
		case 1:
			this->m_iPosStartX -= this->m_pTheApp->RandInt(0,90);
			break;

		// move right
		case 2:
			this->m_iPosStartX += this->m_pTheApp->RandInt(0,100);
			break;
		}

		break;

	case eEXPLOSION_TYPE_BOSS_1_CHAIN_3:

		// x-position
		fMoveX = this->m_posStart.x * fPixelMultiplier;
		this->m_iPosStartX = (this->m_fScreenWidth / 2) + fMoveX;
		// y-position
		fMoveY = this->m_posStart.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;
		this->m_iPosStartY = (this->m_fScreenHeight / 2) + fMoveY;

		this->m_iPosStartX += 305;
		this->m_iPosStartY += 240;

		// random position

		switch(this->m_pTheApp->RandInt(1,2))
		{
		// move up
		case 1:
			this->m_iPosStartY -= this->m_pTheApp->RandInt(0,135);
			break;

		// move down
		case 2:
			this->m_iPosStartY += this->m_pTheApp->RandInt(0,135);
			break;
		}

		switch(this->m_pTheApp->RandInt(1,2))
		{
		// move left
		case 1:
			this->m_iPosStartX -= this->m_pTheApp->RandInt(0,110);
			break;

		// move right
		case 2:
			this->m_iPosStartX += this->m_pTheApp->RandInt(0,120);
			break;
		}

		break;
	}
}
