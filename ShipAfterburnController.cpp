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

		if (m_eShipType == eSHIP_TYPE::Player)
		{
			fMoveY = fMoveY * -1.0f;

			posX = ((SCREEN_WIDTH / 2) - 38.0f) + fMoveX;
			posY = ((SCREEN_HEIGHT / 2) - 38.0f) + fMoveY;

			posY += 66;
		}

		this->m_pSpriteAfterburn->Draw(posX, posY);
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