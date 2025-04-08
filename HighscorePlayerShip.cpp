#include "LerpUtils.h"
#include "HighscorePlayerShip.h"

CHighscorePlayerShip::CHighscorePlayerShip()
{
	this->m_fShipPosY = 0.0f;
	this->m_fShipMoveTimer = 0.0f;
	this->m_fShipEnterStartPosX = 0.0f;
	this->m_fShipEnterEndPosX = 0.0f;
	this->m_fShipLeaveEndPosX = 0.0f;

	this->m_eActionMode = eACTION_MODE_NONE;
}

CHighscorePlayerShip::~CHighscorePlayerShip()
{
}

void CHighscorePlayerShip::Init()
{
	SetActionMode(eACTION_MODE_ENTER);

	Scale();
	ChangeDirection();
}

void CHighscorePlayerShip::Update(float fFrametime)
{
	this->Rotate(fFrametime);

	D3DXVECTOR3 pos = this->GetPosition();

	switch (this->m_eActionMode)
	{
	case eACTION_MODE_ENTER:
	{
		this->m_fShipMoveTimer += fFrametime;
		this->m_fShipMoveTimer = min(this->m_fShipMoveTimer, SHIP_ENTER_DURATION);

		float currentPosX = LerpUtils::CalculateEasingPosition(
			LerpUtils::eEASING_LOGIC::EaseOutBack, this->m_fShipEnterStartPosX, this->m_fShipEnterEndPosX,
			this->m_fShipMoveTimer, SHIP_ENTER_DURATION);

		pos.x = currentPosX;
		this->SetPosition(pos);

		if (this->m_fShipMoveTimer == SHIP_ENTER_DURATION)
		{
			this->m_eActionMode = eACTION_MODE_RESPOND;
		}
	}
	break;

	case eACTION_MODE_RESPOND:

		pos = this->GetPosition();
		pos.y = m_fShipPosY;
		this->SetPosition(pos);

		break;

	case eACTION_MODE_LEAVE:
	{
		this->m_fShipMoveTimer += fFrametime;
		this->m_fShipMoveTimer = min(this->m_fShipMoveTimer, SHIP_LEAVE_DURATION);

		float currentPosX = LerpUtils::CalculateEasingPosition(
			LerpUtils::eEASING_LOGIC::EaseInQuad, this->m_fShipEnterEndPosX, this->m_fShipLeaveEndPosX,
			this->m_fShipMoveTimer, SHIP_LEAVE_DURATION);

		pos.x = currentPosX;
		this->SetPosition(pos);

		if (this->m_fShipMoveTimer == SHIP_LEAVE_DURATION)
		{
			this->m_eActionMode = eACTION_MODE_EXIT;
		}
	}
	break;
	}

	// update object
	C3DObject::Update(fFrametime);
}

void CHighscorePlayerShip::RotateRight()
{
	this->SetRotateX(-(D3DX_PI / 3.75f));
	this->SetRotateY(-D3DX_PI / 2.0f);
	this->SetRotateZ(0);
}

void CHighscorePlayerShip::ChangeVertical()
{
	D3DXVECTOR3 pos = this->GetPosition();
	pos.y = this->m_fShipPosY;
	this->SetPosition(pos);
}

void CHighscorePlayerShip::InitPosition()
{
	D3DXVECTOR3 pos = this->GetPosition();
	pos.x = this->m_fShipEnterStartPosX;

	this->SetPosition(pos);
	this->RotateRight();
}

bool CHighscorePlayerShip::IsAfterburnEnabled()
{
	switch (m_eActionMode)
	{
	case eACTION_MODE_ENTER:
	{
		float delta = m_fShipMoveTimer / SHIP_ENTER_DURATION;
		return (delta <= SHIP_ENTER_AFTERBURN_END_DELTA);
	}
	break;

	case eACTION_MODE_LEAVE:
		return true;
	}

	return false;
}

void CHighscorePlayerShip::SetActionMode(eACTION_MODE eActionMode)
{
	switch (eActionMode)
	{
	case eACTION_MODE_ENTER:
		this->m_fShipEnterStartPosX = -this->m_fScreenWidth - 20.0f;
		break;
	case eACTION_MODE_LEAVE:
		this->m_fShipLeaveEndPosX = this->m_fScreenWidth + 20.0f;
		// play the afterburn sound effect when leaving
		this->m_pTheApp->GetWave(SOUND_PLAYER_LEAVE_AFTERBURN).Play(FALSE, 0);
		break;
	}

	this->m_eActionMode = eActionMode;
	this->m_fShipMoveTimer = 0.0f;
}

D3DMATERIAL9* CHighscorePlayerShip::InitMaterial(D3DMATERIAL9* material)
{
	// specular lighting

	material->Specular.r = 0.6f;
	material->Specular.g = 0.6f;
	material->Specular.b = 0.6f;
	material->Specular.a = 1.0f;
	material->Power = 4.0f;

	return material;
}