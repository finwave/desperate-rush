#include "WeaponBoss1Laser.h"

CWeaponBoss1Laser::CWeaponBoss1Laser(void)
{
}

CWeaponBoss1Laser::~CWeaponBoss1Laser(void)
{
}

void CWeaponBoss1Laser::Release()
{
	CWeapon::Release();
}

void CWeaponBoss1Laser::Update(float fFrametime, float fPlayerVelocity)
{
	float fMove = this->m_fSpeed * fFrametime;
	D3DXVECTOR3 pos = this->GetPosition();

	switch(this->m_eDirection)
	{
	case eDIRECTION_DOWN:

		pos.y -= fMove;

		break;

	case eDIRECTION_DOWN_LEFT:

		pos.x -= fMove * 0.6f;
		pos.y -= fMove;

		break;

	case eDIRECTION_DOWN_RIGHT:

		pos.x += fMove * 0.6f;
		pos.y -= fMove;

		break;
	}

	this->SetPosition(pos);

	CWeapon::Update(fFrametime, fPlayerVelocity);
}

bool CWeaponBoss1Laser::BulletActivity(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsActive() == TRUE;
			break;
	}
	return FALSE;
}

bool CWeaponBoss1Laser::BulletVisibility(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsVisible() == TRUE;
			break;
	}
	return FALSE;
}

void CWeaponBoss1Laser::InitPosition()
{
	D3DXVECTOR3 pos = this->GetPosition();

	pos.z = this->GetDepthValue(1);

	switch(this->m_eSide)
	{
	case eSIDE_LEFT:

		switch(this->m_eDirection)
		{
		case eDIRECTION_DOWN:

			switch(this->m_eBulletPlace)
			{
			case eBULLET_PLACE_1:

				pos.y += 11.0f;
				pos.x -= 47.2f;

				break;

			case eBULLET_PLACE_2:

				pos.y += 10.0f;
				pos.x -= 54.8f;

				break;

			case eBULLET_PLACE_3:

				pos.y += 11.5f;
				pos.x -= 62.2f;

				break;

			case eBULLET_PLACE_4:

				pos.y += 11.8f;
				pos.x -= 69.7f;

				break;
			}

			break;

		case eDIRECTION_DOWN_LEFT:

			switch(this->m_eBulletPlace)
			{
			case eBULLET_PLACE_1:

				pos.y += 25.0f;
				pos.x -= 51.5f;

				break;

			case eBULLET_PLACE_2:

				pos.y += 29.2f;
				pos.x -= 58.0f;

				break;

			case eBULLET_PLACE_3:

				pos.y += 33.4f;
				pos.x -= 64.5f;

				break;

			case eBULLET_PLACE_4:

				pos.y += 38.0f;
				pos.x -= 69.5f;

				break;
			}

			break;
		}

		break;

	case eSIDE_RIGHT:

		switch(this->m_eDirection)
		{
		case eDIRECTION_DOWN:

			switch(this->m_eBulletPlace)
			{
			case eBULLET_PLACE_1:

				pos.y += 11.0f;
				pos.x += 47.2f;

				break;

			case eBULLET_PLACE_2:

				pos.y += 10.0f;
				pos.x += 54.8f;

				break;

			case eBULLET_PLACE_3:

				pos.y += 11.5f;
				pos.x += 62.2f;

				break;

			case eBULLET_PLACE_4:

				pos.y += 11.8f;
				pos.x += 69.7f;

				break;
			}

			break;

		case eDIRECTION_DOWN_RIGHT:

			switch(this->m_eBulletPlace)
			{
			case eBULLET_PLACE_1:

				pos.y += 25.0f;
				pos.x += 51.5f;

				break;

			case eBULLET_PLACE_2:

				pos.y += 29.2f;
				pos.x += 58.0f;

				break;

			case eBULLET_PLACE_3:

				pos.y += 33.4f;
				pos.x += 64.5f;

				break;

			case eBULLET_PLACE_4:

				pos.y += 38.0f;
				pos.x += 69.5f;

				break;
			}

			break;
		}

		break;
	}

	this->SetPosition(pos);
}

void CWeaponBoss1Laser::InitRotation()
{
	D3DXMATRIX mRotationX;
	D3DXMATRIX mRotationZ;

	// rotate 90 degrees by x axis
	D3DXMatrixRotationX(&mRotationX, -(D3DX_PI / 2));

	switch(this->m_eDirection)
	{
	case eDIRECTION_DOWN:

		D3DXMatrixMultiply(	&this->GetLocalMatrix(),
							&mRotationX,
							&this->GetLocalMatrix());

		break;

	case eDIRECTION_DOWN_LEFT:

		D3DXMatrixRotationZ(&mRotationZ, -D3DX_PI / 5);

		D3DXMatrixMultiply(	&this->GetLocalMatrix(),
							&mRotationX,
							&mRotationZ);
							
		break;

	case eDIRECTION_DOWN_RIGHT:

		D3DXMatrixRotationZ(&mRotationZ, D3DX_PI / 5);

		D3DXMatrixMultiply(	&this->GetLocalMatrix(),
							&mRotationX,
							&mRotationZ);

		break;
	}
}
