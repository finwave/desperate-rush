#pragma once

#include "Weapon.h"

class CWeaponEnemySniper : public CWeapon
{
public:
	CWeaponEnemySniper(void);
	virtual ~CWeaponEnemySniper(void);

	virtual void Update(float fFrametime, float fPlayerVelocity);
	virtual void Release();

	virtual void DisableBullet(int iBullet);
	virtual bool BulletActivity(int iBullet);
	virtual bool BulletVisibility(int iBullet);

	virtual void SetMatrix(C3DObject* pShip);
	virtual void InitPosition();

private:
	LPDIRECT3DDEVICE9	m_pDevice;
};