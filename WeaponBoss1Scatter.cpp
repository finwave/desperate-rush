#include "WeaponBoss1Scatter.h"

CWeaponBoss1Scatter::CWeaponBoss1Scatter(void)
{
}

CWeaponBoss1Scatter::~CWeaponBoss1Scatter(void)
{
}

void CWeaponBoss1Scatter::Release()
{
	CWeapon::Release();
}

void CWeaponBoss1Scatter::Update(float fFrametime, float fPlayerVelocity)
{
	float fMove = this->m_fSpeed * fFrametime;
	D3DXVECTOR3 pos = this->GetPosition();

	switch(this->m_eDirection)
	{
	case eDIRECTION_UP:

		pos.y += fMove;

		break;

	case eDIRECTION_DOWN:

		pos.y -= fMove;

		break;

	case eDIRECTION_LEFT:

		pos.x -= fMove;

		break;

	case eDIRECTION_RIGHT:

		pos.x += fMove;

		break;

	case eDIRECTION_UP_LEFT:

		pos.x -= fMove;
		pos.y += fMove;

		break;

	case eDIRECTION_UP_UP_LEFT:

		pos.x -= fMove / 1.5f;
		pos.y += fMove * 1.5f;

		break;

	case eDIRECTION_UP_LEFT_LEFT:

		pos.x -= fMove * 1.5f;
		pos.y += fMove / 1.5f;

		break;

	case eDIRECTION_UP_RIGHT:

		pos.x += fMove;
		pos.y += fMove;

		break;

	case eDIRECTION_UP_UP_RIGHT:

		pos.x += fMove / 1.5f;
		pos.y += fMove * 1.5f;

		break;

	case eDIRECTION_UP_RIGHT_RIGHT:

		pos.x += fMove * 1.5f;
		pos.y += fMove / 1.5f;

		break;

	case eDIRECTION_DOWN_LEFT:

		pos.x -= fMove;
		pos.y -= fMove;

		break;

	case eDIRECTION_DOWN_DOWN_LEFT:

		pos.x -= fMove / 1.5f;
		pos.y -= fMove * 1.5f;

		break;

	case eDIRECTION_DOWN_LEFT_LEFT:

		pos.x -= fMove * 1.5f;
		pos.y -= fMove / 1.5f;

		break;

	case eDIRECTION_DOWN_RIGHT:

		pos.x += fMove;
		pos.y -= fMove;

		break;

	case eDIRECTION_DOWN_DOWN_RIGHT:

		pos.x += fMove / 1.5f;
		pos.y -= fMove * 1.5f;

		break;

	case eDIRECTION_DOWN_RIGHT_RIGHT:

		pos.x += fMove * 1.5f;
		pos.y -= fMove / 1.5f;

		break;
	}

	this->SetPosition(pos);

	CWeapon::Update(fFrametime, fPlayerVelocity);
}

bool CWeaponBoss1Scatter::BulletActivity(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsActive() == TRUE;
			break;
	}
	return FALSE;
}

bool CWeaponBoss1Scatter::BulletVisibility(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsVisible() == TRUE;
			break;
	}
	return FALSE;
}

void CWeaponBoss1Scatter::InitPosition()
{
	D3DXVECTOR3 pos = this->GetPosition();
	pos.z = this->GetDepthValue(1);

	switch(this->m_eDirection)
	{
	case eDIRECTION_UP:

		pos.y += 6.0f;

		break;

	case eDIRECTION_DOWN:

		pos.y -= 6.0f;

		break;

	case eDIRECTION_LEFT:

		pos.x -= 6.0f;

		break;

	case eDIRECTION_RIGHT:

		pos.x += 6.0f;

		break;

	case eDIRECTION_UP_LEFT:

		pos.x -= 5.0f;
		pos.y += 5.0f;

		break;

	case eDIRECTION_UP_UP_LEFT:

		pos.x -= 4.0f;
		pos.y += 7.0f;

		break;

	case eDIRECTION_UP_LEFT_LEFT:

		pos.x -= 7.0f;
		pos.y += 4.0f;

		break;

	case eDIRECTION_UP_RIGHT:

		pos.x += 5.0f;
		pos.y += 5.0f;

		break;

	case eDIRECTION_UP_UP_RIGHT:

		pos.x += 4.0f;
		pos.y += 7.0f;

		break;

	case eDIRECTION_UP_RIGHT_RIGHT:

		pos.x += 7.0f;
		pos.y += 4.0f;

		break;

	case eDIRECTION_DOWN_LEFT:

		pos.x -= 5.0f;
		pos.y -= 5.0f;

		break;

	case eDIRECTION_DOWN_DOWN_LEFT:

		pos.x -= 4.0f;
		pos.y -= 7.0f;

		break;

	case eDIRECTION_DOWN_LEFT_LEFT:

		pos.x -= 7.0f;
		pos.y -= 4.0f;

		break;

	case eDIRECTION_DOWN_RIGHT:

		pos.x += 5.0f;
		pos.y -= 5.0f;

		break;

	case eDIRECTION_DOWN_DOWN_RIGHT:

		pos.x += 4.0f;
		pos.y -= 7.0f;

		break;

	case eDIRECTION_DOWN_RIGHT_RIGHT:

		pos.x += 7.0f;
		pos.y -= 4.0f;

		break;
	}

	this->SetPosition(pos);
}
