#include "WeaponEnemyRoller.h"

CWeaponEnemyRoller::CWeaponEnemyRoller(void)
{
}

CWeaponEnemyRoller::~CWeaponEnemyRoller(void)
{
}

void CWeaponEnemyRoller::Release()
{
	CWeapon::Release();
}

void CWeaponEnemyRoller::Update(float fFrametime, float fPlayerVelocity)
{
	float fMove = this->m_fSpeed * fFrametime;
	D3DXVECTOR3 pos = this->GetPosition();

	switch(this->m_eDirection)
	{
	case eDIRECTION_UP:

		pos.y += fMove * 2;

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

bool CWeaponEnemyRoller::BulletActivity(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsActive() == TRUE;
			break;
	}
	return FALSE;
}

bool CWeaponEnemyRoller::BulletVisibility(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsVisible() == TRUE;
			break;
	}
	return FALSE;
}

void CWeaponEnemyRoller::InitPosition()
{
	D3DXVECTOR3 pos = this->GetPosition();
	pos.z = -40.0f;

	float fAddition = 15.0f;

	switch(this->m_eDirection)
	{
	case eDIRECTION_UP:

		pos.y += 10.0f + fAddition;

		break;

	case eDIRECTION_DOWN:

		pos.y -= 10.0f + fAddition;

		break;

	case eDIRECTION_LEFT:

		pos.x -= 10.0f + fAddition;

		break;

	case eDIRECTION_RIGHT:

		pos.x += 10.0f + fAddition;

		break;

	case eDIRECTION_UP_LEFT:

		pos.x -= 9.0f + fAddition;
		pos.y += 9.0f + fAddition;

		break;

	case eDIRECTION_UP_UP_LEFT:

		pos.x -= 8.0f + fAddition;
		pos.y += 11.0f + fAddition;

		break;

	case eDIRECTION_UP_LEFT_LEFT:

		pos.x -= 11.0f + fAddition;
		pos.y += 8.0f + fAddition;

		break;

	case eDIRECTION_UP_RIGHT:

		pos.x += 9.0f + fAddition;
		pos.y += 9.0f + fAddition;

		break;

	case eDIRECTION_UP_UP_RIGHT:

		pos.x += 8.0f + fAddition;
		pos.y += 11.0f + fAddition;

		break;

	case eDIRECTION_UP_RIGHT_RIGHT:

		pos.x += 11.0f + fAddition;
		pos.y += 8.0f + fAddition;

		break;

	case eDIRECTION_DOWN_LEFT:

		pos.x -= 9.0f + fAddition;
		pos.y -= 9.0f + fAddition;

		break;

	case eDIRECTION_DOWN_DOWN_LEFT:

		pos.x -= 8.0f + fAddition;
		pos.y -= 11.0f + fAddition;

		break;

	case eDIRECTION_DOWN_LEFT_LEFT:

		pos.x -= 11.0f + fAddition;
		pos.y -= 8.0f + fAddition;

		break;

	case eDIRECTION_DOWN_RIGHT:

		pos.x += 9.0f + fAddition;
		pos.y -= 9.0f + fAddition;

		break;

	case eDIRECTION_DOWN_DOWN_RIGHT:

		pos.x += 8.0f + fAddition;
		pos.y -= 11.0f + fAddition;

		break;

	case eDIRECTION_DOWN_RIGHT_RIGHT:

		pos.x += 11.0f + fAddition;
		pos.y -= 8.0f + fAddition;

		break;
	}

	this->SetPosition(pos);
}