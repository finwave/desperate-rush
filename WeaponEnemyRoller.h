#pragma once

#include "Weapon.h"

class CWeaponEnemyRoller : public CWeapon
{
public:

	CWeaponEnemyRoller(void);
	virtual ~CWeaponEnemyRoller(void);

	virtual void Update(float fFrametime, float fPlayerVelocity);
	virtual void Release();

	virtual bool BulletActivity(int iBullet);
	virtual bool BulletVisibility(int iBullet);

	virtual void InitPosition();
};