#include "WeaponEnemySniper.h"

CWeaponEnemySniper::CWeaponEnemySniper(void)
{
}

CWeaponEnemySniper::~CWeaponEnemySniper(void)
{
}

void CWeaponEnemySniper::Release()
{
	CWeapon::Release();
}

void CWeaponEnemySniper::Update(float fFrametime, float fPlayerVelocity)
{
	D3DXVECTOR3 pos;

	CWeapon::Update(fFrametime, fPlayerVelocity);

	float fMove = this->m_fSpeed * fFrametime;
	this->m_fMove += fMove;
}

void CWeaponEnemySniper::DisableBullet(int iBullet)
{
	switch(iBullet)
	{
		case 0:
			this->SetActive(FALSE);
			this->SetVisible(FALSE);
			break;
	}
}

bool CWeaponEnemySniper::BulletActivity(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsActive() == TRUE;
			break;
	}
	return FALSE;
}

bool CWeaponEnemySniper::BulletVisibility(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsVisible() == TRUE;
			break;
	}
	return FALSE;
}

void CWeaponEnemySniper::SetMatrix(C3DObject* pShip)
{
	// rotations

	D3DXMATRIX mRotationX;

	D3DXMatrixRotationX(&mRotationX, -D3DX_PI / 2);

	D3DXMatrixMultiply(	&this->GetLocalMatrix(),
						&mRotationX,
						&this->GetLocalMatrix());

	// position
	this->SetPosition( pShip->GetPosition() );
}

void CWeaponEnemySniper::InitPosition()
{
	D3DXVECTOR3 pos;

	pos = this->GetPosition();
	pos.y -= 20.0f;
	this->SetPosition(pos);
}
