#include "IApplication.h"
#include "GameSettings.h"
#include "C3DObject.h"
#include "Sprite.h"
#include "ShipAfterburnController.h"

CShipAfterburnController::CShipAfterburnController(void)
{
	this->m_pSpriteAfterburn = NULL;
	this->m_pShipObject = NULL;

	this->m_fPlayerAfterburnFlickerTimer = CGameSettings::SHIP_AFTERBURN_FLICKER_SHOW_DURATION;
	this->m_iPlayerAfterburnFlickerMode = 0;
}

CShipAfterburnController::~CShipAfterburnController(void)
{
}

void CShipAfterburnController::Init(C3DObject* pShipObject, CSprite* pSpriteAfterburn, eSHIP_TYPE eShipType)
{
	this->m_pShipObject = pShipObject;
	this->m_pSpriteAfterburn = pSpriteAfterburn;
	this->m_eShipType = eShipType;
}

void CShipAfterburnController::Render(float fFrametime)
{
	if (this->m_iPlayerAfterburnFlickerMode == 0)
	{
		int posX = 0;
		int posY = 0;

		const float fPixelMultiplier = 2.5f;

		// ship object position
		D3DXVECTOR3 pos = this->m_pShipObject->GetPosition();

		float fMoveX = pos.x * fPixelMultiplier;
		float fMoveY = pos.y * fPixelMultiplier;

		fMoveY = fMoveY * -1.0f;

		posX = ((SCREEN_WIDTH / 2) - 38.0f) + fMoveX;
		posY = ((SCREEN_HEIGHT / 2) - 38.0f) + fMoveY;

		switch (m_eShipType)
		{
		case eSHIP_TYPE::Player:
			posY += 66;
			this->m_pSpriteAfterburn->Draw(posX, posY);
			break;
		case eSHIP_TYPE::Drone:
			posY -= 49;
			(this->m_pSpriteAfterburn + 0)->Draw(posX, posY);
			break;
		case eSHIP_TYPE::Sniper:
			posX += 6;
			posY -= 62;
			(this->m_pSpriteAfterburn + 1)->Draw(posX, posY);
			break;
		case eSHIP_TYPE::Roller:
			posY += 55;
			(this->m_pSpriteAfterburn + 2)->Draw(posX, posY);
			break;
		case eSHIP_TYPE::Guard:
			posY += 55;
			(this->m_pSpriteAfterburn + 3)->Draw(posX, posY);
			break;
		}
	}

	this->m_fPlayerAfterburnFlickerTimer -= fFrametime;

	if (this->m_fPlayerAfterburnFlickerTimer <= 0)
	{
		this->m_fPlayerAfterburnFlickerTimer = CGameSettings::SHIP_AFTERBURN_FLICKER_HIDE_DURATION;
		this->m_iPlayerAfterburnFlickerMode++;

		if (this->m_iPlayerAfterburnFlickerMode > 1)
		{
			this->m_fPlayerAfterburnFlickerTimer = CGameSettings::SHIP_AFTERBURN_FLICKER_SHOW_DURATION;
			this->m_iPlayerAfterburnFlickerMode = 0;
		}
	}
}