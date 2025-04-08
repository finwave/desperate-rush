#pragma once

#include "Weapon.h"

class CWeaponBoss1Scatter : public CWeapon
{
public:

	CWeaponBoss1Scatter(void);
	virtual ~CWeaponBoss1Scatter(void);

	virtual void Update(float fFrametime, float fPlayerVelocity);
	virtual void Release();

	virtual bool BulletActivity(int iBullet);
	virtual bool BulletVisibility(int iBullet);

	virtual void InitPosition();
};