#include "../TheApp.h"
#include "../C3DObject.h"
#include "../Sprite.h"
#include "../GameSettings.h"
#include "PlayerBlastController.h"

CPlayerBlastController::CPlayerBlastController(void)
{
	this->m_pTheApp = NULL;
	this->m_pPlayerObject = NULL;
	this->m_pSpriteBlast = NULL;

	this->m_eBeamDirections = NULL;
	this->m_eBlastLight = eBLAST_LIGHT::eBLAST_LIGHT_HIGH;

	this->m_fBlastBeamTimer = 0.0f;
	this->m_iBlastAmount = 0;

	this->m_fBlastActiveTimer = 0.0f;
	this->m_bBlastActive = false;
}

CPlayerBlastController::~CPlayerBlastController(void)
{
	Release();
}

void CPlayerBlastController::Init(CTheApp* pTheApp, C3DObject* pPlayerObject, CSprite* pSpriteBlast)
{
	this->m_pTheApp = pTheApp;
	this->m_pPlayerObject = pPlayerObject;
	this->m_pSpriteBlast = pSpriteBlast;
	this->m_eBeamDirections = new eBEAM_DIRECTION[CGameSettings::PLAYER_BLAST_BEAM_COUNT];

	for (int i = 0; i < CGameSettings::PLAYER_BLAST_BEAM_COUNT; i++)
	{
		this->m_eBeamDirections[i] = eBEAM_DIRECTION::Invalid;
	}

	this->m_iBlastAmount = CGameSettings::PLAYER_BLAST_AMOUNT;
}

void CPlayerBlastController::Release(void)
{
	if (this->m_eBeamDirections != NULL)
	{
		delete[] this->m_eBeamDirections;
		this->m_eBeamDirections = NULL;
	}
}

void CPlayerBlastController::Activate()
{
	this->m_fBlastActiveTimer = CGameSettings::PLAYER_BLAST_ACTIVE_DURATION;
	this->m_fBlastBeamTimer = CGameSettings::PLAYER_BLAST_BEAM_DURATION;
	this->m_bBlastActive = true;
}

void CPlayerBlastController::Update(float fFrametime)
{
	if (!this->m_bBlastActive)
	{
		return;
	}

	this->m_fBlastActiveTimer -= fFrametime;

	if (this->m_fBlastActiveTimer <= 0)
	{
		this->m_bBlastActive = false;
		return;
	}

	this->m_fBlastBeamTimer -= fFrametime;

	if (this->m_fBlastBeamTimer <= 0)
	{
		this->m_fBlastBeamTimer = CGameSettings::PLAYER_BLAST_BEAM_DURATION;

		switch (this->m_eBlastLight)
		{
		case eBLAST_LIGHT::eBLAST_LIGHT_LOW:
			this->m_eBlastLight = eBLAST_LIGHT::eBLAST_LIGHT_HIGH;
			break;

		case eBLAST_LIGHT::eBLAST_LIGHT_HIGH:
			this->m_eBlastLight = eBLAST_LIGHT::eBLAST_LIGHT_LOW;
			break;
		}

		for (int i = 0; i < CGameSettings::PLAYER_BLAST_BEAM_COUNT; i++)
		{
			this->m_eBeamDirections[i] = eBEAM_DIRECTION::Invalid;
		}

		int iDirectionTryCounter = 0;

		int firstSpriteIndex = (int)eBEAM_DIRECTION::UpRight;
		int lastSpriteIndex = (int)eBEAM_DIRECTION::Left;

		for (int i = 0; i < CGameSettings::PLAYER_BLAST_BEAM_COUNT;)
		{
			if (iDirectionTryCounter >= DIRECTION_TRYOUT_MAX)
			{
				break;
			}

			int iDirection = this->m_pTheApp->RandInt(firstSpriteIndex, lastSpriteIndex);
			eBEAM_DIRECTION eDirection = (eBEAM_DIRECTION)iDirection;

			if (ReserveBeamDirection(eDirection))
			{
				i++;
			}
			else
			{
				iDirectionTryCounter++;
			}
		}
	}
}

void CPlayerBlastController::Render()
{
	if (!this->m_bBlastActive)
	{
		return;
	}

	const float fPixelMultiplier = 2.5f;
	D3DXVECTOR3 pos = m_pPlayerObject->GetPosition();

	// x-position

	float fMoveX = pos.x * fPixelMultiplier;
	int iPosOriginalX = ((SCREEN_WIDTH / 2) - 12.0f) + fMoveX;

	// y-position

	float fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	int iPosOriginalY = ((SCREEN_HEIGHT / 2) - 12.0f) + fMoveY;

	// draw blast beams

	for (int i = 0; i < CGameSettings::PLAYER_BLAST_BEAM_COUNT; i++)
	{
		eBEAM_DIRECTION beamDirection = this->m_eBeamDirections[i];

		if (beamDirection == eBEAM_DIRECTION::Invalid)
		{
			continue;
		}

		int iPosX = iPosOriginalX;
		int iPosY = iPosOriginalY;

		switch (beamDirection)
		{
		case eBEAM_DIRECTION::Up:
			iPosX -= 162;
			iPosY -= 1215;
			break;

		case eBEAM_DIRECTION::Down:
			iPosX -= 162;
			iPosY += 25;
			break;

		case eBEAM_DIRECTION::Left:
			iPosX -= 1215;
			iPosY -= 162;
			break;

		case eBEAM_DIRECTION::Right:
			iPosX += 25;
			iPosY -= 162;
			break;

		case eBEAM_DIRECTION::UpLeft:
			iPosX -= 980;
			iPosY -= 980;
			break;

		case eBEAM_DIRECTION::UpRight:
			iPosX -= 90;
			iPosY -= 980;
			break;

		case eBEAM_DIRECTION::DownLeft:
			iPosX -= 980;
			iPosY -= 90;
			break;

		case eBEAM_DIRECTION::DownRight:
			iPosX -= 90;
			iPosY -= 90;
			break;
		}

		int spriteIndex = (int)beamDirection;
		this->m_pSpriteBlast[spriteIndex].Draw(iPosX, iPosY);
	}
}

bool CPlayerBlastController::ReserveBeamDirection(eBEAM_DIRECTION eDirection)
{
	for (int i = 0; i < CGameSettings::PLAYER_BLAST_BEAM_COUNT; i++)
	{
		if (this->m_eBeamDirections[i] == eDirection)
		{
			return false;
		}
	}

	for (int i = 0; i < CGameSettings::PLAYER_BLAST_BEAM_COUNT; i++)
	{
		if (this->m_eBeamDirections[i] == eBEAM_DIRECTION::Invalid)
		{
			this->m_eBeamDirections[i] = eDirection;
			return true;
		}
	}

	return false;
}