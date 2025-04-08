#pragma once

#include "IEnemy.h"

class CEnemyDrone : public IEnemy
{
public:

	CEnemyDrone(eTYPE eType, eBEHAVIOUR eBehaviour);

	virtual ~CEnemyDrone(void);

	virtual bool Shoot();

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	virtual void Move(float fFrametime, float fPlayerVelocity);
	virtual void SetMoveState(void);
};