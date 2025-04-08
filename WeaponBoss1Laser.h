#pragma once

#include "Weapon.h"

class CWeaponBoss1Laser : public CWeapon
{
public:

	CWeaponBoss1Laser(void);
	virtual ~CWeaponBoss1Laser(void);

	virtual void Update(float fFrametime, float fPlayerVelocity);
	virtual void Release();

	virtual bool BulletActivity(int iBullet);
	virtual bool BulletVisibility(int iBullet);

	virtual void InitPosition();

	void InitRotation();

private:

	LPDIRECT3DDEVICE9	m_pDevice;
};