#include "WeaponEnemyDrone.h"

CWeaponEnemyDrone::CWeaponEnemyDrone(void)
{
}

CWeaponEnemyDrone::~CWeaponEnemyDrone(void)
{
}

void CWeaponEnemyDrone::Release()
{
	CWeapon::Release();
}

void CWeaponEnemyDrone::Update(float fFrametime, float fPlayerVelocity)
{
	CWeapon::Update(fFrametime, fPlayerVelocity);

	float fMove = this->m_fSpeed * fFrametime;
	this->m_fMove += fMove;
}

void CWeaponEnemyDrone::DisableBullet(int iBullet)
{
	switch(iBullet)
	{
		case 0:
			this->SetActive(FALSE);
			this->SetVisible(FALSE);
			break;
	}
}

bool CWeaponEnemyDrone::BulletActivity(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsActive() == TRUE;
			break;
	}
	return FALSE;
}

bool CWeaponEnemyDrone::BulletVisibility(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsVisible() == TRUE;
			break;
	}
	return FALSE;
}

void CWeaponEnemyDrone::SetMatrix(C3DObject* pShip)
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

void CWeaponEnemyDrone::InitPosition()
{
	D3DXVECTOR3 pos;

	pos = this->GetPosition();
	pos.y -= 14.5f;
	this->SetPosition(pos);
}
